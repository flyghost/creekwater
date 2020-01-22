#ifndef FRAMESERIAL_H
#define FRAMESERIAL_H



#include <QWidget>
#include <QTimer>
#include "qextserialport.h"
#include "qextserialenumerator.h"
//#include <QThread>

class QextSerialPort;
//class QTcpSocket;

#include "ui_framemain.h"

//#include "package_ano_422.h"

//#include "qextserialport.h"
//#include "qextserialenumerator.h"

class FrameSerial : public QWidget
{
    Q_OBJECT
//QThread thread;Package_ANO_422 *package;
public:
    FrameSerial(Ui_FrameMain *m_ui) ;


private:
    Ui_FrameMain *ui;

    bool comOk;                 //串口是否打开
    QextSerialPort *com;        //串口通信对象

    int maxCount;               //最大显示行数
    int currentCount;           //当前显示行数
    int sendCount;              //发送数据计数
    int receiveCount;           //接收数据计数
    bool isShow;                //是否显示数据
    QTimer *m_timer;    //com find timer
    QextSerialEnumerator *enumerator;    //在线串口统计类

//    QextSerialEnumerator *enumerator;    //在线串口统计类

private slots:
    void initForm();                //初始化窗体数据
    void initConfig();              //初始化配置文件
    //void saveConfig();              //保存配置文件
    void readData();                //读取串口数据
    void sendData();                //发送串口数据
    void sendData(QString data);    //发送串口数据带参数
    //void saveData();                //保存串口数据

    void readSendData();            //读取发送配置文件数据
    void readDeviceData();          //读取设备转发文件数据

    void changeEnable(bool b);      //改变状态
    void append(quint8 type, QString msg);
    void m_timer_timeout();
    void onPortAddedOrRemoved();        //刷新串口号

//    void onPortAddedOrRemoved();        //刷新串口号

private slots:
    void on_btnOpen_clicked();
    void on_btnStopShow_clicked();
    void on_btnSendCount_clicked();
    void on_btnReceiveCount_clicked();
    void on_btnClear_clicked();

//signals:
//    void serial_recv_char(quint8 data);//收到则发送信号，解包线程进行解析

};















#endif // FRAMEBOTTOM_H
