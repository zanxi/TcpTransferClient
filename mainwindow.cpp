#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

#include <iostream>


//#include "Debug/logger.h"
//#include "dataanimals.h"
#include "dialog_viewphoto.h"
#include "extendqtablewidget.h"

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);

    // *************************************************************************


    ui->groupBox->setStyleSheet("QGroupBox {"
                                "background-color: white;"
                                "}"
                                "QGroupBox::title {"
                                "color: white;"
                                "background-color:"+DataSystems::Instance().settings___color_header+";"
                                                                                    "padding: 4 20000 4 10;"
                                                                                    "}");
    ui->groupBox_2->setStyleSheet("QGroupBox {"
                                  "background-color: white;"
                                  "}"
                                  "QGroupBox::title {"
                                  "color: white;"
                                  "background-color:"+DataSystems::Instance().settings___color_header+";"
                                                                                      "padding: 4 20000 4 10;"
                                                                                      "}");

   // *************************************************************************

    DataSystems::Instance().clear();
    // ************************************************************************

    add_action = new QAction(tr("Add cell"), this);
    add_action->setIcon(QIcon(":/images/resources/app.ico"));
    Delete_action = new QAction(tr("Delete cell"), this);
    Delete_action->setIcon(QIcon(":/images/resources/app.ico"));

    connect(add_action , SIGNAL(triggered()), SLOT(Addshow()));
    connect(Delete_action , SIGNAL(triggered()), SLOT(show()));

    tableWidget = new ExtendQTableWidget(this);

    ui->verticalLayout_5->addWidget(tableWidget);

    GetData();
    //connect(tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(on_tableWidget_cellEntered(int,int)));
    //connect(tableWidget, SIGNAL(cellEntered(int,int)), tableWidget, SLOT(on_tableWidget_cellEntered2(int,int)));
    connect(tableWidget, SIGNAL(cellEntered(int,int)), this, SLOT(on_tableWidget_cellEntered2(int,int)));
    //connect(tableWidget, SIGNAL(mouseReleaseEvent(QMouseEvent)),SLOT(mouseReleaseEvent(QMouseEvent)));



    // ****************************************************************************************

    tcpClient = new QTcpSocket(this);
    sendTimes = 0;
    //tcpClient = NULL ;
    localFile= NULL;
    fileName = "";  //имя файла
    dspIP = "127.0.0.1";
    dstPort = 8000;
    sendSpeed = 100;

    // ****************************************************************************************

    tcpClientMsg = new QTcpSocket(this);
    dstPortMsg = 7777;

    OutputLog("IP server: " +dspIP+"| port: "+QString::number(dstPort)+"| sendSpeed: "+QString::number(sendSpeed)+"| sendTimes: "+QString::number(sendTimes));

    ui->lineEdit_sendSpeed->setText(QString::number(sendSpeed));
    ui->lineEdit_dstPort->setText(QString::number(dstPort));

    connect(tcpClient, SIGNAL(connected()), this, SLOT(send()));  //При успешном соединении начинается передача файлов
    connect(tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(goOnSend(qint64)));







    //connect(tcpClientMsg, SIGNAL(connected()), this, SLOT(sendMsg()));  //При успешном соединении начинается передача файлов


}

void MainWindow::Addshow()
{
    logger::WriteMsg("Add action");
    if(DataSystems::Instance().robot_paramfile1==nullptr)return;
    Dialog_ViewPhoto dvf(DataSystems::Instance().robot_paramfile1);
    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }
}


MainWindow::~MainWindow()
{
    delete localFile;
    delete tcpClient;
    delete tcpClientMsg;
    delete ui;
}

void MainWindow::mouseReleaseEvent (QMouseEvent * event )
{
    QMessageBox* msgBox;
    if(event->button() == Qt::RightButton)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);
        menu->addAction(add_action);
        menu->addAction(Delete_action);
        menu->exec(mouseEvent->globalPos());
        //msgBox->setInformativeText("u pressed right button");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter) {
        qDebug() << ("keyPressEvent: Enter received");
    }
    else if (keyEvent->key() == Qt::Key_A)
    {
        qDebug() << ("keyPressEvent: A received");
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Enter) {
        qDebug() << ("keyReleaseEvent: Enter received");
    }
    else if (keyEvent->key() == Qt::Key_A)
    {
        qDebug() << ("keyReleaseEvent: A received");
    }
    else if (keyEvent->key() == Qt::Key_Escape)
    {
        qDebug() << ("keyReleaseEvent: Escape received");
        QMessageBox::information(this,"Спасибо","Вы вышли из сетевого клиента");
        QApplication::closeAllWindows();
        QApplication::quit();
    }
}


void MainWindow::PhotoView_Dialog()
{
    //OutputLog(QString::number(row));

    //DataSystems::Instance().savePath = QApplication::applicationDirPath();

    QString fileNamePicture = DataSystems::Instance().robot_paramfilephoto1; //ui->comboBox->currentText();
    OutputLog(fileNamePicture);

    //fileNamePicture = "https://demotivatorium.ru/sstorage/3/2014/09/13001529222202/demotivatorium_ru_a_chto_eto_vi_tut_delaete_a_58272.jpg";
    Dialog_ViewPhoto dvf(fileNamePicture, this);

    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }

}


void MainWindow::on_tableWidget_cellEntered2(int row, int column)
{
    if(column !=0 && column!=1)return;
    OutputLog(QString::number(row) + "|" + QString::number(column));
    QString id = "";
    QTableWidgetItem *item = tableWidget->item(row,4);
    if (NULL != item) {
        id = item->text();
        DataSystems::Instance().robot_id = id;
        OutputLog(id);
        GetDataImage(id);
        if(DataSystems::Instance().robot_paramfile1==nullptr)
        {
            OutputLog(QString("Empty photo") + "|" + QString::number(row) + "|" + QString::number(column));
            return;
        }

        PhotoView_Dialog();
    }
    return;


    if(column !=0 && column!=1)return;
    QTimer::singleShot(100, this, SLOT(PhotoView_Dialog()));

    return;

    OutputLog(QString::number(row));

    if(tableWidget->selectionModel()->isRowSelected(row, QModelIndex()))
        return;
    tableWidget->clearSelection();
    tableWidget->selectRow(row);

    if(column !=0 && column!=1)return;

    QString fileNamePicture = ""; //ui->comboBox->currentText();
    Dialog_ViewPhoto dvf(fileNamePicture, this);

    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }

    //tableWidget->item(row,0)->setBackground(Qt::green);
    //tableWidget->item(row,1)->setBackground(Qt::green);
    //tableWidget->item(row,2)->setBackground(Qt::green);
}



void MainWindow::on_pushButton_sendfile_clicked()
{
    if(sendTimes == 0)  //Только первая его отправка происходит, когда соединение генерирует сигнал подключения.
    {
        tcpClient->connectToHost(QHostAddress(dspIP), dstPort);
        if (!tcpClient->waitForConnected(5000))  // Если соединение установлено успешно, введите if{}
        {
            //ui->lineEdit_sendStatus->setText(tr("Не удалось установить соединение. Подтвердите IP-адрес хоста назначения и номер порта."));
            QMessageBox::critical(this, tr("Соединение не удалось:") ,tr("Пожалуйста, подтвердите IP-адрес хоста назначения и номер порта, и сервер начал прослушивание!"), QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel | QMessageBox::Escape , 0 );
            return;
        }
        else{
            sendTimes = 1;
        }
    }
    else
    {
        qDebug()<<"on_pushButton_sendfile_clicked(); send();";
        send();  //При первой отправке сигнал подключения отправляется ConnectToHost для вызова send.После второго раза вам нужно вызвать send.
    }
    ui->lineEdit_sendStatus->setText(tr("Отправка файла %1").arg(fileName));

}


void MainWindow::OutputLog(QString msgLog)
{
    logger::WriteLog(msgLog);
    logger::WriteMsg(msgLog.toStdString());
    ui->textEdit->setText(DataSystems::Instance().log);
}


void MainWindow::on_pushButton_openfile_clicked()
{
    ui->lineEdit_sendStatus->setText(tr("Открытие файла..."));
    ui->sendProgressBar->setValue(0);  //Отправлено не в первый раз

    loadSize = 0;
    byteToWrite = 0;
    totalSize = 0;
    outBlock.clear();

    fileName = QFileDialog::getOpenFileName(this);
    localFile = new QFile(fileName);
    localFile->open(QFile::ReadOnly);

    logger::WriteLog("File transfer: [" + fileName + "]");
    ui->textEdit->setText(DataSystems::Instance().log);

    //std::cout<<"wenjiandaxiao:"<<localFile->size()<<std::endl;
    ui->lineEdit_sendStatus->setText(tr("Файл открыт --- %1").arg(fileName));

    float s = localFile->size()/1024.0;
    OutputLog(QString("Файл готов к откправке: ")+" | fileName: " + fileName+ " ||| " + QString("Размер файла: ")+"  " + QString::number(s)+" Kb"+" = " + QString::number(s/1000.0)+" Mb");

    ui->sendStatusLabel->setText(QString("Файл готов к откправке: ")+" | fileName: " + fileName+ " ||| " + QString("Размер файла: ")+"  " + QString::number(s)+" Kb"+" = " + QString::number(s/1000.0)+" Mb");

}

void MainWindow::sendMsg()
{
    //return;
    DataSystems::Instance().y++;

    QDataStream out(&outBlockMsg, QIODevice::WriteOnly);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    QString msg = "Message data:"+QString::fromStdString(logger::CreateLogName2());

    QDateTime dt1 = QDateTime::currentDateTime();

    //"Robot_No text,"
    double v1 = 0*((DataSystems::Instance().y<80)?(10+(rand()%5)/7.0):(
                         (DataSystems::Instance().y<120)?(20+(rand()%6)/7.0):(
                             (DataSystems::Instance().y<200)?(15+(rand()%4)/7.0):(12+(rand()%4)/7.0))));
    double v2 = 0*((DataSystems::Instance().y<80)?(70+(rand()%8)/7.0):(
                         (DataSystems::Instance().y<120)?(60+(rand()%3)/7.0):(
                             (DataSystems::Instance().y<200)?(65+(rand()%3)/7.0):(68+(rand()%5)/7.0))));
    double v3 = (DataSystems::Instance().y<80)?(70+sin(DataSystems::Instance().y)):(
                    (DataSystems::Instance().y<120)?(60+sin(DataSystems::Instance().y)):(65+2*sin(DataSystems::Instance().y)));

    QString values =
        "Robot_No;"+QString("Robo")+QString::number((rand()%10000))+"|"
                                                                            "coord_teat_lf;"+QString::number(v1)+"|"
                                //"coord_teat_lr;"+QString::number(41.5+(rand()%3)/7.0)+"|"
                                "coord_teat_lr;"+QString::number(v2)+"|"
                                "coord_teat_rf;"+QString::number(v3)+"|"
                                "coord_teat_rr;"+QString::number(40+(rand()%5)/7.0);
    //"param1;"+FiletoText;
    // +"|paramtime2;"+dt1.toString("yyyy-MM-dd hh:mm:ss");


    //OutputLog("Mesage sent to server: " + msg);
    //OutputLog("Mesage sent to server: " + values);

    QString valRand = QString::number(rand()%10000);
    OutputLog("Mesage sent to server: " + values+ " | " + valRand);

    out<<values<<valRand;

    //return;


    //out<<msg;

    //totalSize += outBlock.size();  //Общий размер — это размер файла плюс размер имени файла и другой информации.
    //byteToWrite += outBlock.size();

    //out.device()->seek(0);  //Вернитесь к начальной точке потока байтов и запишите предыдущий qint64, который представляет собой общий размер, имя файла и другие размеры информации.
    //out<<totalSize<<qint64(outBlock.size());
    //Общий размер (размер всего пакета) — размер заголовка (два qint64 и одно имя файла)

    tcpClientMsg->connectToHost(QHostAddress(dspIP), dstPortMsg);
    if (!tcpClientMsg->waitForConnected(5000))  // Если соединение установлено успешно, введите if{}
    {
        //ui->lineEdit_sendStatus->setText(tr("Не удалось установить соединение. Подтвердите IP-адрес хоста назначения и номер порта."));
        QMessageBox::critical(this, tr("Соединение не удалось:") ,tr("Пожалуйста, подтвердите IP-адрес хоста назначения и номер порта, и сервер начал прослушивание!"), QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel | QMessageBox::Escape , 0 );
        return;
    }
    tcpClientMsg->write(outBlockMsg);  //Отправить прочитанный файл в сокет

    //SendR(dspIP, dstPortMsg,values);

    tcpClientMsg->flush();
    tcpClientMsg->close();

}

void MainWindow::tabwidget_insert_add_column(QTableWidget *tab, const QString &value,  int numRow, int numColumn)
{
    QString const DateTimeFormat = "yyyy-MM-ddTHH:mm:ss.zzzZ";
    //if(nameColumnX.contains("pic")||nameColumnX.contains("param"))
    {
        //QString time = QString::fromStdString(logger::time()); //a.toString();

        QTableWidgetItem *item = new QTableWidgetItem(value);
        item->setTextAlignment(Qt::AlignHCenter);
        tab->setItem( numRow, numColumn,  item);

        //OutputLog(QString::number(numRow) + "|" + QString::number(numColumn) + "|" + time);

    }
}


void MainWindow::GetDataImage(QString id)
{

    //tableWidget->row()

    //tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Параметры робота"));
    for(int i=0;i<tableWidget->columnCount();i++)tableWidget->setColumnWidth(i, 250);

    tableWidget->update();

    QString str = "vz";

    QScopedPointer<DataBase> db_func(new DataBase());
    if(db_func->StatusOpen())
    {
        QString sql =  QString("SELECT * FROM public.dataentry_robot WHERE id =  '" + id +"';").toLower();
        QSqlQuery* query = db_func->sql_exec2(sql);
        if(query->size()<1)return;

        int i=0;
        while(query->next())
        {
            QString val_out="";
            {
                QVariant val = query->value("paramfile1");
                DataSystems::Instance().robot_paramfile1 = (!val.isNull())?val.toByteArray():nullptr;
                if(DataSystems::Instance().robot_paramfile1!=nullptr)
                {
                    OutputLog("Empty photo");
                    DataSystems::Instance().robot_paramfilephoto1 = DataSystems::Instance().savePath+"/" + QString::fromStdString(logger::CreateLogName2())+ "_" + fileName+".jpg";
                    QFileInfo file(DataSystems::Instance().robot_paramfilephoto1);
                    if(file.exists()){
                        QMessageBox::critical(this, tr("Пожалуйста, обрати внимание:") ,tr("В текущем пути уже есть файл с таким именем, пожалуйста, выберите новый путь, чтобы сохранить файл!"), QMessageBox::Ok | QMessageBox::Default , QMessageBox::Cancel | QMessageBox::Escape , 0 );
                    }else{
                        newFile = new QFile(DataSystems::Instance().robot_paramfilephoto1);
                        newFile->open(QFile::WriteOnly);
                        newFile->write(DataSystems::Instance().robot_paramfile1);
                        newFile->flush();
                        newFile->close();
                    //            fileExits = true;
                }
                }
            }
            {
                QVariant val = query->value("param1");
                DataSystems::Instance().robot_param1 = (!val.isNull())?val.toString():" ";
            }
            {
                QVariant val = query->value("paramtime1");
                DataSystems::Instance().robot_paramtime1 = (!val.isNull())?val.toString():" ";
            }
            {
                //QVariant val = query->value("id");
                //val_out+=QString("id") + " = "  +((!val.isNull())?val.toString():" ");
            }
            i++;
            //break;
        }
    }
    else{
        OutputLog("No connection db <<<VIM>>>");
    }
    /**/

}


void MainWindow::GetData()
{

    //tableWidget->row()

    //tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Параметры робота"));
    for(int i=0;i<tableWidget->columnCount();i++)tableWidget->setColumnWidth(i, 250);

    tableWidget->update();

    QString str = "vz";

        QScopedPointer<DataBase> db_func(new DataBase());
        //QSqlDatabase db2=QSqlDatabase::database(DataSystems::Instance().conn_name);
        if(db_func->StatusOpen())
        {
            //QString tab = "dataentry_robot";
            //QString sql =  QString("SELECT * FROM public."+tab+" WHERE coord_teat_lf LIKE '%"+str+"%' OR  ORDER BY id;").toLower();
            //QString sql =  QString("SELECT * FROM public.dataentry_robot WHERE param1 =  '" + str +"';").toLower();
            QString sql =  QString("SELECT * FROM public.dataentry_robot WHERE id>0;").toLower();
            QSqlQuery* query = db_func->sql_exec2(sql);
            if(query->size()<1)return;

            int i=0;
            while(query->next())
            {
                tableWidget->insertRow( tableWidget->rowCount() );

                QString val_out="";

                QVariant val;
                //val = query->value("robot_no"); DataSystems::Instance().robot_robot_no =  (!val.isNull())?val.toString():" ";
                //val = query->value("coord_teat_lf"); DataSystems::Instance().robot_coord_teat_lf =  (!val.isNull())?val.toString():" ";
                //val = query->value("coord_teat_lr"); DataSystems::Instance().robot_coord_teat_lr =  (!val.isNull())?val.toString():" ";
                //val = query->value("coord_teat_rf"); DataSystems::Instance().robot_coord_teat_rf =  (!val.isNull())?val.toString():" ";
                //val = query->value("coord_teat_rr"); DataSystems::Instance().robot_coord_teat_rr =  (!val.isNull())?val.toString():" ";
                {
                   QVariant val = query->value("paramfile1");
                   val_out +=  QString("size photo: ") + QString::number(val.toByteArray().size()) + "\n";
                   DataSystems::Instance().robot_paramfile1 = val.toByteArray();
                   //val_out +=  QString("size photo: ") + QString::number(DataSystems::Instance().robot_paramfile1.size()) + "\n";
                   //QByteArray binDataArray = query->value(query->record() .indexOf("bin_data")).toByteArray();
                }

                {
                   QVariant val = query->value("param1"); tabwidget_insert_add_column(tableWidget, ((!val.isNull())?val.toString():" "), i, 2); val_out+=QString("param1")+" = "+((!val.isNull())?val.toString():" ") + "; ";
                }
                {
                   QVariant val = query->value("param2"); tabwidget_insert_add_column(tableWidget, ((!val.isNull())?val.toString():" "), i, 3); val_out+=QString("paramtime1") + " = " + ((!val.isNull())?val.toString():" ") + "; ";
                }
                {
                   QVariant val = query->value("id"); tabwidget_insert_add_column(tableWidget, ((!val.isNull())?QString::number(val.toInt()):" "), i, 4); val_out+=QString("id") + " = "  +((!val.isNull())?val.toString():" ");
                }
                {
                   QVariant val = query->value("param3"); tabwidget_insert_add_column(tableWidget, ((!val.isNull())?val.toString():" "), i, 5); val_out+=QString("param2")+" = "+((!val.isNull())?val.toString():" ") + "; ";
                }
                {
                   QVariant val = query->value("param4"); tabwidget_insert_add_column(tableWidget, ((!val.isNull())?val.toString():" "), i, 5); val_out+=QString("param3")+" = "+((!val.isNull())?val.toString():" ") + "; ";
                }

                OutputLog(val_out);
                //val = query->value("param2"); DataSystems::Instance().robot_param2 =  (!val.isNull())?val.toString():" ";

                //QString time = QString::fromStdString(logger::time()); //a.toString();
                //QTableWidgetItem *item = new QTableWidgetItem(time);
                //item->setTextAlignment(Qt::AlignHCenter);
                //tableWidget->setItem( i, 2,  new QTableWidgetItem(time));

                //tabwidget_insert_add_column(tableWidget,"pic1", i, 0);
                //tabwidget_insert_add_column(tableWidget,"pic2", i, 1);

                //tabwidget_insert_add_column(tableWidget,"paramtime1", i, 3);
                i++;

                //break;
            }
        }
        else{
            OutputLog("No connection db <<<VIM>>>");
        }
        /**/

}

void MainWindow::SendR(QString ip, int port, QString values)
{
    QByteArray data = values.toUtf8();
    QTcpSocket *socket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
    socket->connectToHost(ip, port);
    if( socket->waitForConnected() ) {
        logger::WriteLog("Server access!!!!!!!!!!!!" + QString("\n"));
        logger::WriteLog("("+QString::number(DataSystems::Instance().y)+") values robot: "+ values + QString("\n"));
        ui->textEdit->setText(DataSystems::Instance().log);
        socket->write( data );
    }
    else
    {
        //mTimer->stop();
        //ui->pushButton_start->setEnabled(true);
        //ui->pushButton_stop->setEnabled(false);
        //DataSystems::Instance().log+="("+QString::number(DataSystems::Instance().y)+") Server access denied" + QString("\n");
        //ui->textEdit->setText(DataSystems::Instance().log);

    }

    socket->flush();
    socket->close();

    //if(DataSystems::Instance().log.size()>700)DataSystems::Instance().log = "";

}


void MainWindow::send()  //Отправить информацию заголовка файла
{

    byteToWrite = localFile->size();  //размер оставшихся данных
    totalSize = localFile->size();

    loadSize = sendSpeed*1024;  //Размер данных, отправляемых каждый раз, в КБ

    QDataStream out(&outBlock, QIODevice::WriteOnly);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    out<<qint64(0)<<qint64(0)<<currentFileName;

    totalSize += outBlock.size();  //Общий размер — это размер файла плюс размер имени файла и другой информации.
    byteToWrite += outBlock.size();

    out.device()->seek(0);  //Вернитесь к начальной точке потока байтов и запишите предыдущий qint64, который представляет собой общий размер, имя файла и другие размеры информации.
    out<<totalSize<<qint64(outBlock.size());
    //Общий размер (размер всего пакета) — размер заголовка (два qint64 и одно имя файла)
    tcpClient->write(outBlock);  //Отправить прочитанный файл в сокет
    //Затем срабатывает сигнал bytesWritten, а затем срабатывает goOnSend, чтобы официально начать отправку содержимого файла!

    //qDebug()<<"send"<<"| totalSize: "<<totalSize<<"| byteToWrite: "<<byteToWrite;
    logger::WriteLog(fileName);
    logger::WriteLog(QString("send")+"| totalSize: "+QString::number(totalSize)+"| byteToWrite: "+QString::number(byteToWrite));
    ui->textEdit->setText(DataSystems::Instance().log);

    //ui->progressLabel->show();
    ui->sendProgressBar->setMaximum(totalSize);
    ui->sendProgressBar->setValue(totalSize - byteToWrite);
    if(ui->sendProgressBar->value()>=totalSize - byteToWrite+1)
    {
        float s = localFile->size()/1024.0;
        OutputLog(QString("Файл отправлен: ")+" | fileName: " + fileName+ " ||| " + QString("Размер файла: ")+"  " + QString::number(s)+" Kb"+" = " + QString::number(s/1000.0)+" Mb");
    }
}

void MainWindow::goOnSend(qint64 numBytes)  //Начать отправку содержимого файла
{
    //qDebug()<<"send"<<"| totalSize: "<<totalSize<<"| byteToWrite: "<<byteToWrite;
    logger::WriteLog(QString("send")+"| totalSize: "+QString::number(totalSize)+"| byteToWrite: "+QString::number(byteToWrite));
    ui->textEdit->setText(DataSystems::Instance().log);

    byteToWrite -= numBytes;  //Оставшийся размер данных
    outBlock = localFile->read(qMin(byteToWrite, loadSize));
    tcpClient->write(outBlock);

    ui->sendProgressBar->setMaximum(totalSize);
    ui->sendProgressBar->setValue(totalSize - byteToWrite);

    if(byteToWrite == 0)  //Отправил
        ui->lineEdit_sendStatus->setText(tr("%1 Отправил!").arg(fileName));

        float s = localFile->size()/1024.0;
        OutputLog(QString("Файл отправлен: ")+" | fileName: " + fileName+ " ||| " + QString("Размер файла: ")+"  " + QString::number(s)+" Kb"+" = " + QString::number(s/1000.0)+" Mb");
}

void MainWindow::on_lineEdit_dstIP_returnPressed()
{
    dspIP = ui->lineEdit_dstIP->text();
    //std::cout<<dspIP.toStdString()<<std::endl;
}

void MainWindow::on_lineEdit_sendSpeed_returnPressed()
{
    sendSpeed = ui->lineEdit_sendSpeed->text().toInt();
}

//void MainWindow::on_lineEdit_dstPort_cursorPositionChanged(int arg1, int arg2)
//{
//    dstPort = ui->lineEdit_dstPort->text().toInt();
//}

void MainWindow::on_lineEdit_dstPort_returnPressed()
{
    dstPort = ui->lineEdit_dstPort->text().toInt();
}

void MainWindow::on_pushButton_send_message_clicked()
{
    sendMsg();
}

