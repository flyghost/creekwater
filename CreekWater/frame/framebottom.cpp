#include "framebottom.h"

#include "ui_framemain.h"
#include <QDebug>

#include "iconhelper.h"
#include "qextserialport.h"

QextSerialPort *com;        //串口通信对象

FrameBottom::FrameBottom(Ui_FrameMain *mui)
{
    ui = mui;

    clock = new Clock(ui->widget_clock);//时钟

    config_bottom_button_init();
    config_serial_init();
    signalInit();
    config_serial_init();//初始化下拉菜单

    //绑定解包槽函数
    connect(this, SIGNAL(serial_recv_char(quint8)),package_ano_422, SLOT(DataPreProcessing(quint8)));
    //connect(this, SIGNAL(serial_recv_char2(quint8 *, quint8)),package, SLOT(DataPreProcessing(quint8 *, quint8)));


}

//初始化按钮
void FrameBottom::config_bottom_button_init()
{
    //ui->widget_bottom->setProperty("form", "title");
    ui->widget_bottom->setProperty("nav", "top");

    pixCharBottom <<  0xf014 <<  0xf011 ;
    btnsBottom << ui->mainClearButton<< ui->mainConnectButton ;

    int count = btnsBottom.count();
    for (int i = 0; i < count; i++) {
        btnsBottom.at(i)->setCheckable(true);
        btnsBottom.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //connect(btnsBottom.at(i), SIGNAL(clicked(bool)), this, SLOT(mainButtonGroupClicked()));
    }
    IconHelper::Instance()->setStyle(ui->widget_bottom, btnsBottom, pixCharBottom, 15, 25, 15, "left", 4);
                                     //"#444444","#444444","#444444","#000000","#000000");
    //第一个
    //第二个：面板颜色
    //第三个：鼠标经过按钮的颜色
    //第四个：字体颜色
    //第五个鼠标经过按钮字体颜色


}
//信号槽初始化
void FrameBottom::signalInit()
{
    //this->setWindowTitle("串口调试助手");

    comOk = false;
    com = nullptr;
    maxCount = 500;
    currentCount = 0;
    //sleepTime = 10;
    receiveCount = 0;
    sendCount = 0;
    isShow = true;


    connect(ui->mainConnectButton, SIGNAL(clicked()), this, SLOT(on_btnOpen_clicked()));//打开串口按钮
    connect(ui->mainClearButton, SIGNAL(clicked()), this, SLOT(on_btnClear_clicked()));//清空数据

    changeEnable(false);//可以修改下拉菜单


}
//是否可以改变状态
void FrameBottom::changeEnable(bool b)
{
    ui->bottomPortName->setEnabled(!b);
    ui->bottomPortBond->setEnabled(!b);
}
//初始化下拉菜单
void FrameBottom::config_serial_init()
{
    /*
    * 串口号配置
    */
    //添加com1~com20
    QStringList comList;
    for (int i = 1; i <= 20; i++) {
        comList << QString("COM%1").arg(i);
    }
    //添加到下拉菜单
    //comList << "ttyUSB0" << "ttyS0" << "ttyS1" << "ttyS2" << "ttyS3" << "ttyS4";
    ui->bottomPortName->addItems(comList);

    /*
    * 波特率配置
    */
    //添加波特率
    QStringList baudList;
    baudList << "115200" << "128000" << "256000";
    //添加到下拉菜单
    ui->bottomPortBond->addItems(baudList);

}


void FrameBottom::on_btnOpen_clicked()
{
    if (ui->mainConnectButton->text() == "连接")
    {
        com = new QextSerialPort(ui->bottomPortName->currentText(), QextSerialPort::EventDriven);
        comOk = com->open(QIODevice::ReadWrite);

        if (comOk)
        {
            //清空缓冲区
            com->flush();
            //设置波特率
            com->setBaudRate(static_cast<BaudRateType>(ui->bottomPortBond->currentText().toInt()));
            //设置数据位  8位
            com->setDataBits(DATA_8);
            //设置校验位  无
            com->setParity(PAR_NONE);
            //设置停止位  1位
            com->setStopBits(STOP_1);
            com->setFlowControl(FLOW_OFF);
            com->setTimeout(10);

            connect(com, SIGNAL(readyRead()), this, SLOT(readData()));

            changeEnable(true);
            ui->mainConnectButton->setText("断开");
        }
    } else {
        com->close();
        changeEnable(false);
        ui->mainConnectButton->setText("连接");
        //on_btnClear_clicked();
        comOk = false;
    }
}

void FrameBottom::readData()
{
    if (com->bytesAvailable() <= 0) {
        return;
    }

    QByteArray data = com->readAll();

    int dataLen = data.length();

    if (dataLen <= 0) {
        return;
    }

    for(int i = 0; i < dataLen; i++)
    {
        serial_recv_char(static_cast<quint8>(data.at(i)));
    }
    currentCount += dataLen;
    ui->bottom_recvcount_label->setText(QString::number(currentCount,10));
}

void FrameBottom::on_btnClear_clicked()
{
    currentCount = 0;
    ui->bottom_recvcount_label->setText("0");
    ui->bottom_sendcount_label->setText("0");
}
