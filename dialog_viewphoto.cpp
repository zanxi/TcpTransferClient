#include "dialog_viewphoto.h"
#include "ui_dialog_viewphoto.h"

#include <QThread>
#include <QTimer>
#include <QLayoutItem>

#include "utils/imageview.h"
#include "Debug/logger.h"
#include "dataanimals.h"

Dialog_ViewPhoto::Dialog_ViewPhoto(QString fileNamePicture, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ViewPhoto)
{
    ui->setupUi(this);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);

    PhotoView(fileNamePicture);

    mTimer=new QTimer(this);
    connect(mTimer, SIGNAL(timeout()),this, SLOT(CloseDialog()));
    mTimer->start(3000);

    //this->close();
}

Dialog_ViewPhoto::Dialog_ViewPhoto(QByteArray ba, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ViewPhoto)
{
    ui->setupUi(this);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setPalette(pal);

    PhotoView(ba);

    mTimer=new QTimer(this);
    connect(mTimer, SIGNAL(timeout()),this, SLOT(CloseDialog()));
    mTimer->start(3000);

    //this->close();
}


Dialog_ViewPhoto::~Dialog_ViewPhoto()
{
    delete ui;
}

void Dialog_ViewPhoto::CloseDialog()
{
    this->close();
}

void Dialog_ViewPhoto::PhotoView(QByteArray ba)
{
    ImageView *imageView = new ImageView(this);
    imageView->setDisplayStyle(imageView->STYLE::contain);
    imageView->setLoadingPixmap(QPixmap(ba));


    if(ui->verticalLayout->count()<1)
    {
        //form_dataentry_dataentry___transfer *tf = new form_dataentry_dataentry___transfer(this);
        //OutputLog(QString("Error"));
        ui->verticalLayout->addWidget(imageView);
        return;
    }

    QLayoutItem *child = ui->verticalLayout->takeAt(0);
    //while ((child = ui->verticalLayout_2->takeAt(0)) != 0)
    if(!child) {return;}
    QWidget* w = child->widget();
    delete child;
    if(!w) {return;}
    ui->verticalLayout->removeWidget(w);
    delete w;

    //form_dataentry_dataentry___transfer *tf = new form_dataentry_dataentry___transfer(this);
    ui->verticalLayout->addWidget(imageView);


}

void Dialog_ViewPhoto::PhotoView(QString fileNamePicture)
{

    QString info = "Photo: " + DataSystems::Instance().robot_paramfilephoto1 + "\n" +
                   "Photo size: " + QString::number((DataSystems::Instance().robot_paramfile1!=nullptr)?DataSystems::Instance().robot_paramfile1.size():0) + "\n" +
                   "id: " + DataSystems::Instance().robot_id + "\n" +
                   "param1: " + DataSystems::Instance().robot_param2 + "\n" +
                   "paramtime1: " + DataSystems::Instance().robot_paramtime1 + "\n";
    //QString info = DataSystems::Instance().robot_paramfilephoto1;

    logger::WriteMsg(info.toStdString());

    ui->textEdit->setText(info);


    if(fileNamePicture.toLower().contains("http")||
        fileNamePicture.toLower().contains("jpg")||
        fileNamePicture.toLower().contains("gif")||
        fileNamePicture.toLower().contains("png"))
    {

        ImageView *imageView = new ImageView(this);
        imageView->setDisplayStyle(imageView->STYLE::contain);//
        //imageView->setLoadingPixmap(QPixmap(fileNamePicture));
        if(fileNamePicture.contains("http"))imageView->setUrl(fileNamePicture);
        else imageView->setLoadingPixmap(QPixmap(fileNamePicture));


        if(ui->verticalLayout->count()<1)
        {
            //form_dataentry_dataentry___transfer *tf = new form_dataentry_dataentry___transfer(this);
            //OutputLog(QString("Error"));
            ui->verticalLayout->addWidget(imageView);
            return;
        }

        QLayoutItem *child = ui->verticalLayout->takeAt(0);
        //while ((child = ui->verticalLayout_2->takeAt(0)) != 0)
        if(!child) {return;}
        QWidget* w = child->widget();
        delete child;
        if(!w) {return;}
        ui->verticalLayout->removeWidget(w);
        delete w;

        //form_dataentry_dataentry___transfer *tf = new form_dataentry_dataentry___transfer(this);
        ui->verticalLayout->addWidget(imageView);

    }
}

