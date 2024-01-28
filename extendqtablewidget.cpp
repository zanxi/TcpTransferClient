#include "extendqtablewidget.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>

#include "dialog_viewphoto.h"
#include "dataanimals.h"
#include "Debug/logger.h"

ExtendQTableWidget::ExtendQTableWidget(QWidget *parent):
    QTableWidget(parent)
{

    this->setColumnCount(7);

    this->setHorizontalHeaderItem(0, new QTableWidgetItem("pic1"));
    this->setHorizontalHeaderItem(1, new QTableWidgetItem("pic2"));
    this->setHorizontalHeaderItem(2, new QTableWidgetItem("param1"));
    this->setHorizontalHeaderItem(3, new QTableWidgetItem("param2"));
    this->setHorizontalHeaderItem(4, new QTableWidgetItem("id"));
    this->setHorizontalHeaderItem(5, new QTableWidgetItem("param3"));
    this->setHorizontalHeaderItem(6, new QTableWidgetItem("param4"));

    /*
    groupBox_3 = new QGroupBox(centralwidget);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    verticalLayout_3 = new QVBoxLayout(groupBox_3);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    tableWidget = new QTableWidget(groupBox_3);
    if (tableWidget->columnCount() < 5)
        tableWidget->setColumnCount(5);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
    QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
    QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
    QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
    tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

    verticalLayout_3->addWidget(tableWidget);
    verticalLayout_4->addWidget(groupBox_3);
    /**/

    add_action = new QAction(tr("Add cell"), this);
    add_action->setIcon(QIcon(":/images/resources/app.ico"));
    Delete_action = new QAction(tr("Delete cell"), this);
    Delete_action->setIcon(QIcon(":/images/resources/app.ico"));

    connect(add_action , SIGNAL(triggered()), SLOT(show()));
    connect(Delete_action , SIGNAL(triggered()), SLOT(show()));

    //connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(on_tableWidget_cellEntered2(int,int)));
}

void ExtendQTableWidget::on_tableWidget_cellEntered2(int row, int column)
{
    logger::WriteMsg(QString("void ExtendQTableWidget::on_tableWidget_cellEntered2("+QString::number(row) + "," + QString::number(column)+")").toStdString());
    if(column !=0 && column!=1)return;
    //OutputLog(QString::number(row) + "|" + QString::number(column));
    QString id = "";
    QTableWidgetItem *item = this->item(row,4);
    if (NULL != item) {
        id = item->text();
        DataSystems::Instance().robot_id = id;
        //OutputLog(id);
        //GetDataImage(id);
        if(DataSystems::Instance().robot_paramfile1==nullptr)
        {
            //OutputLog(QString("Empty photo") + "|" + QString::number(row) + "|" + QString::number(column));
            return;
        }

        //PhotoView_Dialog();
    }
    return;
}

void ExtendQTableWidget::show()
{
    logger::WriteMsg("Add action");
    Dialog_ViewPhoto dvf(DataSystems::Instance().robot_paramfile1);
    if(!(dvf.exec()==QDialog::Accepted))
    {
        //QMessageBox::information(this,"Спасибо","Сухостойность");
    }
}

void ExtendQTableWidget::mousePressEvent(QMouseEvent *event) {
    //if(event->button( ) == Qt::LeftButton);
        //cout << "Left Button Clicked." << endl;

    return;

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
    if(event->button() == Qt::LeftButton)
    {

    }
}
