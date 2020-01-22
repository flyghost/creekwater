#include "frameconnect.h"

#include "ui_framemain.h"
#include <QDebug>

#include "iconhelper.h"

FrameConnect::FrameConnect(Ui_FrameMain *mui, Bridge *m_bridge)
{
    ui = mui;
    this->bridge = m_bridge;
    initLeftConfig();
    check_device_init();
    initButtonGroup();

}

//设置界面按钮ttf初始化
void FrameConnect::initLeftConfig()
{
    pixCharConfig << 0xf031 << 0xf036 << 0xf249  ;
    btnsConfig << ui->tbtnConfig1 << ui->tbtnConfig2 << ui->tbtnConfig3 ;

    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        btnsConfig.at(i)->setCheckable(true);
        btnsConfig.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(btnsConfig.at(i), SIGNAL(clicked(bool)), this, SLOT(leftConfigClick()));
    }

    IconHelper::Instance()->setStyle(ui->widgetLeftConfig, btnsConfig, pixCharConfig, 10, 20, 15, "left", 5);
    //IconHelper::Instance()->setStyle(ui->mainSearchButton, btnsConfig, pixCharConfig, 15, 25, 15, "left", 4);
    ui->tbtnConfig1->click();
}
//设置界面按钮响应事件
void FrameConnect::leftConfigClick()
{
    QToolButton *b = static_cast<QToolButton *>(sender());
    QString name = b->text();

    int count = btnsConfig.count();
    for (int i = 0; i < count; i++) {
        if (btnsConfig.at(i) == b) {
            btnsConfig.at(i)->setChecked(true);
            btnsConfig.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsConfig.at(i), false)));
        }
        else {
            btnsConfig.at(i)->setChecked(false);
            btnsConfig.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsConfig.at(i), true)));
        }
    }
    if (name == "HID模式") {
        ui->settinStackedWidget->setCurrentIndex(0);
    }
    else if (name == "串口模式") {
        ui->settinStackedWidget->setCurrentIndex(1);
    }
    else if (name == "WIFI模式") {
        ui->settinStackedWidget->setCurrentIndex(2);
    }

    //ui->lab2->setText(name);
}
//查找HID设备按钮初始化，圆盘按钮初始化
void FrameConnect::check_device_init()
{


//    ui->buttonDevice->setButtonEnable(0,true);
//    ui->buttonDevice->setButtonEnable(2,true);

//    connect(ui->buttonDevice, SIGNAL(CustomButtonClicked(int)), this, SLOT(check_deviceClick(int)));

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
    ui->systemSettingComName->addItems(comList);
    ui->systemSettingComBond->setText("115200");

}
//菜单栏，选择连接方式
void FrameConnect::initButtonGroup()
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
void FrameConnect::check_deviceClick(int buttonId)
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

//选择连接方式槽函数
void FrameConnect::on_seleckConnect_clicked(QAbstractButton *btn)
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



