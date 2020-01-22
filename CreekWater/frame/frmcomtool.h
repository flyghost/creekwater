#ifndef FRMCOMTOOL_H
#define FRMCOMTOOL_H

#include <QWidget>

class QextSerialPort;
class QTcpSocket;

#include "ui_framemain.h"

class frmComTool : public QWidget
{
	Q_OBJECT

public:
    frmComTool(Ui::FrameMain *m_ui) ;
    //~frmComTool();

private:
    Ui::FrameMain *ui;

    bool comOk;                 //串口是否打开
    QextSerialPort *com;        //串口通信对象

	int maxCount;               //最大显示行数
	int currentCount;           //当前显示行数
	int sendCount;              //发送数据计数
	int receiveCount;           //接收数据计数
	bool isShow;                //是否显示数据


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

private slots:
	void on_btnOpen_clicked();
	void on_btnStopShow_clicked();
	void on_btnSendCount_clicked();
	void on_btnReceiveCount_clicked();
    void on_btnClear_clicked();



};

#endif // FRMCOMTOOL_H
