#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QFile>
#include <string>
#include <QTableWidget>
#include <QMouseEvent>
#include <QAction>


#include "Debug/logger.h"
#include "dataanimals.h"
#include "extendqtablewidget.h";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void OutputLog(QString msgLog);
    void SendR(QString ip, int port, QString values);
    void GetData();
    void GetDataImage(QString id);
    void tabwidget_insert_add_column(QTableWidget *tab, const QString &nameColumnX,  int numRow, int numColumn);
    void PhotoView_Dialog();

    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);

    virtual void mouseReleaseEvent (QMouseEvent * event );

private slots:
    //void on_tableWidget_cellEntered(int row, int column);
    void on_tableWidget_cellEntered2(int row, int column);
    void on_pushButton_sendfile_clicked();

    void on_pushButton_openfile_clicked();
    void send();  //Отправить информацию заголовка файла
    void sendMsg();  //Отправить сообщение
    void goOnSend(qint64);  //Отправить содержимое файла

    void on_lineEdit_dstIP_returnPressed();

    void on_lineEdit_sendSpeed_returnPressed();

//    void on_lineEdit_dstPort_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_dstPort_returnPressed();

    void on_pushButton_send_message_clicked();
    void Addshow();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient ;
    QFile *localFile;
    QString fileName;  //имя файла
    QFile *newFile;

    QByteArray outBlock;  //Передавать партиями
    qint64 loadSize;  //Размер данных, отправляемых каждый раз
    qint64 byteToWrite;  //Оставшийся размер данных
    qint64 totalSize;  //общий размер файла
    QString dspIP;
    int dstPort;

    int sendTimes;  //Используется для обозначения того, отправляется ли он в первый раз.После первого раза срабатывает сигнал подключения, а последующие вызываются вручную.
    int sendSpeed;

    int dstPortMsg;
    QTcpSocket *tcpClientMsg;
    QByteArray outBlockMsg;  //Передавать партиями

    QAction *add_action;
    QAction *Delete_action;
    ExtendQTableWidget *tableWidget;

};
#endif // MAINWINDOW_H
