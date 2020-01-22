#ifndef FRAMEBOTTOM_H
#define FRAMEBOTTOM_H


#include "clock.h"
#include <QThread>
#include "package_ano_422.h"
class QextSerialPort;

#include "ui_framemain.h"

extern QextSerialPort *com;        //串口通信对象

class FrameBottom : public QWidget
{
    Q_OBJECT
    QThread *thread;
//    Package_ANO_422 *package;
public:
    explicit FrameBottom(Ui_FrameMain *mui);

private:
    Ui_FrameMain *ui;
    Clock *clock;

    QList<int> pixCharBottom;        //按钮图片组
    QList<QToolButton *> btnsBottom; //按钮组

    bool comOk;                 //串口是否打开
//    QextSerialPort *com;        //串口通信对象

    int maxCount;               //最大显示行数
    int currentCount;           //当前显示行数
    int sendCount;              //发送数据计数
    int receiveCount;           //接收数据计数
    bool isShow;                //是否显示数据

private:
    void config_bottom_button_init();//初始化按钮
    void config_serial_init();//初始化串口下拉菜单和波特率输入菜单
    void signalInit();//初始化信号槽
    void changeEnable(bool b);      //改变状态

private slots:
    void readData();                //读取串口数据

private slots:
    void on_btnOpen_clicked();    //连接按钮
    void on_btnClear_clicked();   //清零按钮
signals:
    void serial_recv_char(quint8 data);//收到则发送信号，解包线程进行解析
    //void serial_recv_char2(quint8 *data_buf, quint8 num);//收到则发送信号，解包线程进行解析
};





#endif // FRAMEBOTTOM_H
