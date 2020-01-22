//设置界面
//传入ui界面



#include <QDebug>
#include "settinginterface.h"




SettingInterface::SettingInterface(Ui::FrameMain *m_ui, Bridge *m_bridge)
{
    ui = m_ui;
    this->bridge = m_bridge;

    check_device_init();

    initButtonGroup();

}

void SettingInterface::check_device_init()
{


    ui->buttonDevice->setButtonEnable(0,true);
    ui->buttonDevice->setButtonEnable(2,true);

    connect(ui->buttonDevice, SIGNAL(CustomButtonClicked(int)), this, SLOT(check_deviceClick(int)));

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
    ui->comport->addItems(comList);


}
//菜单栏，选择连接方式
void SettingInterface::initButtonGroup()
{
    QStringList list;
    list << "HID模式" << "串口模式" << "TCP模式";

    for (int i = 0; i < 3; i++) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(list.at(i));
        //btn->setMinimumHeight(30);
        //btn->setFixedSize(130, 60);
        ui->settingButtonGroup->addButton(static_cast<QAbstractButton *>(btn), i);
    }

    ui->settingButtonGroup->setBaseColor(QColor(40, 45, 48), true);
    ui->settingButtonGroup->setTextNormalColor(QColor(255, 255, 255));
    ui->settingButtonGroup->setLinePosition(ButtonGroup::LinePosition_Top);

    ui->settingButtonGroup->addFinsh();

    //ui->settingButtonGroup->setFixedHeight(33);
    ui->settingButtonGroup->setFixedWidth(200);

    connect(ui->settingButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(on_seleckConnect_clicked(QAbstractButton *)));

}
//HID搜索圆盘
void SettingInterface::check_deviceClick(int buttonId)
{

    if(buttonId == 4)//搜索
    {
        bridge->set_communication_hard(bridge->__USBHID);//设置为USBHID
        bridge->open_communication_hard(bridge->__USBHID);//打开连接

    }
    else
    {
        qDebug() << buttonId ;
    }


}

void SettingInterface::on_seleckConnect_clicked(QAbstractButton *btn)
{
    //qDebug() << buttonId ;


    QToolButton *b = static_cast<QToolButton *>(btn);
    connect_mode = b->text();

    if (connect_mode == "HID模式") {
        ui->checkStackWidget->setCurrentIndex(0);
    }
    else if (connect_mode == "串口模式") {
        ui->checkStackWidget->setCurrentIndex(1);
    }
    else if (connect_mode == "TCP模式") {
        ui->checkStackWidget->setCurrentIndex(2);
    }



}


