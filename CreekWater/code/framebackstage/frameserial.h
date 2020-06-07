#ifndef FRAMESERIAL_H
#define FRAMESERIAL_H



#include <QWidget>
#include <QTimer>
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "serialdownload.h"
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
    SerialDownload *serialdownload;

    bool comOk;                 //串口是否打开
    QextSerialPort *com;        //串口通信对象

    int maxCount;               //最大显示行数
    int currentCount;           //当前显示行数
    int sendCount;              //发送数据计数
    int receiveCount;           //接收数据计数
    bool isShow;                //是否显示数据
    QTimer *serial_update_timer;// 定时检测插入的串口
    QString com_name;           // 打开的串口名字
    QStringList com_list;        // 当前检测到的所有串口
    
    // QextSerialEnumerator *enumerator;    //在线串口统计类

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
    void comUpdate();        //刷新串口号

private slots:
    void on_btnOpen_clicked();
    void on_btnStopShow_clicked();
    void on_btnSendCount_clicked();
    void on_btnReceiveCount_clicked();
    void on_btnClear_clicked();

//signals:
//    void serial_recv_char(quint8 data);//收到则发送信号，解包线程进行解析








// # this is frame struct support by uboot
// # ,-----+------+-----+----------+------------+- - - -+-------------,
// # | SOF | TYPE | LEN | SUB_TYPE | HEAD_CKSUM | DATA  | DATA_CKSUM  |
// # |  1  |   1  |  4  |    1     |      4     | ...   |     4       | <- size (bytes)
// # '-----+------+-----+----------+------------+- - - -+-------------'
private:
     quint32 TRS_STUB_BLOCK = 1024;
     quint32 TRS_CMD_BLOCK = 4096;
    ButtonEdit *buttonEdit1;
    ButtonEdit *buttonEdit2;
    ButtonEdit *buttonEdit3;
    ButtonEdit *buttonEdit4;

    void FrameSerialdowninit(void);
    void buttonEditInit();

    quint8 retries;
    QByteArray STUB_CODE;

    void write(QByteArray bytes);
    QByteArray read(qint64 length);
    quint32 crc32(quint32 crc, const void *buf, size_t size);
    bool command(quint8 cmd_type, quint8 cmd_subtype=0, quint8 data_content[]=nullptr, quint32 data_length=0);
    QString get_path();
    bool sync_bootrom();    // Perform a connection to bootrom in uart boot mode
    bool load_stub();

private slots:
    void downloadButtonClicked();
    void path_lineEdit1_Clicked();
    void path_lineEdit2_Clicked();
    void path_lineEdit3_Clicked();
    void path_lineEdit4_Clicked();

private:
    QString TRS_ALLINONE = "oneb";

private:
    qint32 str_to_hex(QString str);
    bool bin_handle_unpack(QString path,
                           qint32 *type,
                           qint32 *bin_addr,
                           qint32 *image_length,
                           QByteArray *image);
    bool bin_handle_read(QString path,
                         QString addr,
                         qint32 *type,
                         qint32 *bin_addr,
                         qint32 *image_length,
                         QByteArray *image);

};















#endif // FRAMEBOTTOM_H
