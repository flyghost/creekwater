#include "frameserial.h"
#include "myhelper.h"


FrameSerial::FrameSerial(Ui_FrameMain *m_ui)
{
    ui = m_ui;
    //ui->setupUi(this);
    this->initForm();
    this->initConfig();


//    package = new Package_ANO_422;


//    package->moveToThread(&thread);

//    thread.start();

//    qDebug()<<"     serial thread ID:"<<QThread::currentThreadId()<<'\n';


//    connect(this, SIGNAL(serial_recv_char(quint8)),package, SLOT(DataPreProcessing(quint8)));

//    connect(&thread, &QThread::finished, package, &QObject::deleteLater);

}


void FrameSerial::initForm()
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

    //发送数据
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(sendData()));
//    connect(ui->cboxSend, SIGNAL(returnPressed()),ui->btnSend,SIGNAL(clicked()),Qt::UniqueConnection);  //回车发送
    ui->btnSend->setShortcut(Qt::Key_Return);//将字母区回车键与发送按钮绑定在一起
    connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(on_btnOpen_clicked()));//打开串口按钮
    connect(ui->btnSendCount, SIGNAL(clicked()), this, SLOT(on_btnSendCount_clicked()));//发送清零
    connect(ui->btnReceiveCount, SIGNAL(clicked()), this, SLOT(on_btnReceiveCount_clicked()));//接收清零
    connect(ui->btnStopShow, SIGNAL(clicked()), this, SLOT(on_btnStopShow_clicked()));//停止显示
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(on_btnClear_clicked()));//清空数据

    changeEnable(false);//可以修改下拉菜单

//    if(m_timer == nullptr)
//    {
//         m_timer = new QTimer();
//    }
   serial_update_timer = new QTimer(this);
   serial_update_timer->setSingleShot(false);//设置定时器是否为单次触发。默认为 false 多次触发
   serial_update_timer->start(500);//启动或重启定时器, 并设置定时器时间：毫秒
   connect(serial_update_timer, SIGNAL(timeout()), this, SLOT(comUpdate())); //定时器触发信号槽


}

void FrameSerial::initConfig()
{
    //读取配置
    //ComConfig::ReadConfig();


    /*
    * 串口号配置
    */
    //添加com1~com20
    //QStringList comList;

    //获取可用串口，添加到下拉菜单
    comUpdate();
    // 以下为qextserialenumerator提供，unix下不支持
    // enumerator = new QextSerialEnumerator();
    // enumerator->setUpNotifications();

    // connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)),this, SLOT(comUpdate()));  //发现有串口
    // connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), this, SLOT(comUpdate()));     //发现没有串口了

    QStringList sendEndFlagList;
    sendEndFlagList << "\\CR\\LF" << "\\CR" << "\\LF" << "NONE";
    ui->cboxSendEndFlag->addItems(sendEndFlagList);

    /*
    * 波特率配置
    */
    //添加波特率
    QStringList baudList;
    baudList <<"115200" << "128000" << "256000";
    //添加到下拉菜单
    ui->cboxBaudRate->addItems(baudList);

    /*
    * 数据位配置
    */
    //添加数据位
    QStringList dataBitsList;
    dataBitsList << "8" << "6" << "7" << "5";
    ui->cboxDataBit->addItems(dataBitsList);

    /*
    * 校验位配置
    */
    QStringList parityList;
    parityList << "无" << "奇" << "偶";
    #ifdef Q_OS_WIN
    parityList << "标志";
    #endif
    parityList << "空格";

    ui->cboxParity->addItems(parityList);

    /*
    * 停止位配置
    */
    QStringList stopBitsList;
    stopBitsList << "1";
    #ifdef Q_OS_WIN
    stopBitsList << "1.5";
    #endif
    stopBitsList << "2";

    ui->cboxStopBit->addItems(stopBitsList);

}



void FrameSerial::changeEnable(bool b)
{
    ui->cboxBaudRate->setEnabled(!b);
    ui->cboxDataBit->setEnabled(!b);
    ui->cboxParity->setEnabled(!b);
    ui->cboxPortName->setEnabled(!b);
    ui->cboxStopBit->setEnabled(!b);
    ui->btnSend->setEnabled(b);
}

void FrameSerial::append(quint8 type, QString msg)
{
    if (!isShow) {
        return;
    }

    if (currentCount >= maxCount) {
        ui->txtMain->clear();
        currentCount = 0;
    }

    QString str;

    if (type == 0) {
        str = ">> 串口发送 : ";
        ui->txtMain->setTextColor(QColor("green"));
    } else if (type == 1) {
        str = "<< 串口接收 : ";
        ui->txtMain->setTextColor(QColor("dodgerblue"));
    }

    ui->txtMain->append(QString("时间[%1] %2 %3").arg(TIMEMS).arg(str).arg(msg));
    currentCount++;
}

void FrameSerial::readData()
{
    if (com->bytesAvailable() <= 0) {
        return;
    }

    QByteArray data = com->readAll();
    int dataLen = data.length();

    if (dataLen <= 0) {
        return;
    }

//    for(int i = 0; i < dataLen; i++)
//    {
//        serial_recv_char(static_cast<quint8>(data.at(i)));
//    }


    if (isShow) {
        QString buffer;

//        if (ui->ckHexReceive->isChecked()) {
//            buffer = myHelper::byteArrayToHexStr(data);
//        } else {
//            buffer = myHelper::byteArrayToAsciiStr(data);
//        }
        buffer= data;

        append(1, buffer);
        receiveCount = receiveCount + data.size();
        ui->btnReceiveCount->setText(QString("接收 : %1 字节").arg(receiveCount));
    }
}

void FrameSerial::sendData()
{
    QString str;
    if(ui->cboxSendEndFlag->currentText() == "NONE")
    {
        str = ui->cboxSend->currentText();
    }
    else
    {
        str = ui->cboxSend->currentText() + ui->cboxSendEndFlag->currentText();// 发送添加换行符
    }

    if (str.isEmpty()) {
        ui->cboxSend->setFocus();
        return;
    }

    sendData(str);

    ui->cboxSend->setEditText("");

}

void FrameSerial::sendData(QString data)
{
    if (com == nullptr || !com->isOpen()) {
        return;
    }

    QByteArray buffer;

    if (ui->ckHexSend->isChecked()) {
        buffer = myHelper::hexStrToByteArray(data);
    } else {
        buffer = myHelper::asciiStrToByteArray(data);
    }

    com->write(buffer);
    append(0, data);

    sendCount = sendCount + buffer.size();
    ui->btnSendCount->setText(QString("发送 : %1 字节").arg(sendCount));
}


void FrameSerial::on_btnOpen_clicked()
{
    if (ui->btnOpen->text() == "打开串口")
    {
//        com = new QextSerialPort(ui->cboxPortName->currentText(), QextSerialPort::Polling);
        com = new QextSerialPort(ui->cboxPortName->currentText(), QextSerialPort::EventDriven);
        comOk = com->open(QIODevice::ReadWrite);

        if (comOk)
        {
            //清空缓冲区
            com->flush();
            //设置波特率
            com->setBaudRate(static_cast<BaudRateType>(ui->cboxBaudRate->currentText().toInt()));
            //设置数据位
            com->setDataBits(static_cast<DataBitsType>(ui->cboxDataBit->currentText().toInt()));
            //设置校验位
            com->setParity(static_cast<ParityType>(ui->cboxParity->currentIndex()));
            //设置停止位
            com->setStopBits(static_cast<StopBitsType>(ui->cboxStopBit->currentIndex()));
            com->setFlowControl(FLOW_OFF);
            com->setTimeout(10);

            connect(com, SIGNAL(readyRead()), this, SLOT(readData()));

            changeEnable(true);
            ui->btnOpen->setText("关闭串口");
            com_name = ui->cboxPortName->currentText();
        }
    }
    else
    {
        com->close();
        changeEnable(false);
        ui->btnOpen->setText("打开串口");
        on_btnClear_clicked();
        comOk = false;
        com_name = nullptr;
    }
}

void FrameSerial::on_btnSendCount_clicked()
{
    sendCount = 0;
    ui->btnSendCount->setText("发送 : 0 字节");
}

void FrameSerial::on_btnReceiveCount_clicked()
{
    receiveCount = 0;
    ui->btnReceiveCount->setText("接收 : 0 字节");
}

void FrameSerial::on_btnStopShow_clicked()
{
    if (ui->btnStopShow->text() == "停止显示") {
        isShow = false;
        ui->btnStopShow->setText("开始显示");
    } else {
        isShow = true;
        ui->btnStopShow->setText("停止显示");
    }
}

void FrameSerial::readSendData()
{
    QString fileName = QString("%1/%2").arg(AppPath).arg("send.txt");
    QFile file(fileName);

    if (!file.exists()) {
        return;
    }

    ui->cboxSend->clear();
    file.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;

    do {
        line = in.readLine();

        if (line != "") {
            ui->cboxSend->addItem(line);
        }
    } while (!line.isNull());

    file.close();
}

void FrameSerial::readDeviceData()
{
    QString fileName = QString("%1/%2").arg(AppPath).arg("device.txt");
    QFile file(fileName);

    if (!file.exists()) {
        return;
    }

    file.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;

    do {
        line = in.readLine();

        if (line != "") {
            QStringList list = line.split(";");
            QString key = list.at(0);
            QString value;

            for (int i = 1; i < list.count(); i++) {
                value += QString("%1;").arg(list.at(i));
            }

            //去掉末尾分号
            value = value.mid(0, value.length() - 1);

//			keys.append(key);
//			values.append(value);
        }
    } while (!line.isNull());

    file.close();
}


void FrameSerial::on_btnClear_clicked()
{
    ui->txtMain->clear();
    currentCount = 0;
}

void FrameSerial::comUpdate()              //刷新串口号
{
    ui->cboxPortName->blockSignals(true);        //阻塞信号
    com_list.clear();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
    {
        if(!info.portName.contains("USB",Qt::CaseSensitive))
        {
            continue;
        }
        else
        {
            com_list.append(info.portName);
        }
    }

    // 串口打开但是未检测到该串口
    if(comOk && !com_list.contains(com_name))
    {
        on_btnOpen_clicked(); // 关闭串口
    }

    // 串口未打开，更新串口
    if(!comOk)
    {
        ui->cboxPortName->clear();
        ui->cboxPortName->addItems(com_list);
    }

    ui->cboxPortName->blockSignals(false);       //关闭阻塞
}


















