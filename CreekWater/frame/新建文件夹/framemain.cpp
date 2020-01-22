#include "framemain.h"
#include "ui_framemain.h"
#include <QDebug>

#include "iconhelper.h"

FrameMain::FrameMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameMain)
{
    ui->setupUi(this);



//    this->initForm();
//    this->initLeftMain();
//    this->initLeftConfig();
//    this->initLeftTest();
//    this->config_bottom_button_init();//底部按钮初始化
//    //this->check_device_init();//查询USBHID初始化

//    bridge = new Bridge(ui);
//    comFrame = new frmComTool(ui);
//    maininterface = new MainInterface(ui,bridge);
//    settinginterface = new SettingInterface(ui,bridge);

}



FrameMain::~FrameMain()
{
    delete ui;
}


//顶部导航栏初始化
void FrameMain::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf06d), 50);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));//设置最小化按钮图标
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));

    //ui->widgetMenu->setVisible(false);
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");
    ui->labTitle->setText("  CreekWater Community  ");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());

    ui->stackedWidget->setStyleSheet("QLabel{font:8pt;}");
    //ui->testStackedWidget->setStyleSheet("QLabel{font:3pt;}");



    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach(QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    ui->btnMain->click();

    ui->widgetLeftMain->setProperty("flag", "left");
    ui->widgetLeftConfig->setProperty("flag", "left");
    ui->pageMain->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));
    ui->pageSetting->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(20));
    ui->pageTest->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(20));

}
//主界面左列按钮ttf初始化
void FrameMain::initLeftMain()
{
    pixCharMain << 0xf030 << 0xf03e << 0xf247;
    btnsMain << ui->tbtnMain1 << ui->tbtnMain2 << ui->tbtnMain3;

    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        btnsMain.at(i)->setCheckable(true);
        btnsMain.at(i)->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        connect(btnsMain.at(i), SIGNAL(clicked(bool)), this, SLOT(leftMainClick()));
    }

    IconHelper::Instance()->setStyle(ui->widgetLeftMain, btnsMain, pixCharMain, 15, 35, 25, "left", 4);

    ui->tbtnMain1->click();
}
//设置界面按钮ttf初始化
void FrameMain::initLeftConfig()
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
//测试界面左列按钮ttf初始化
void FrameMain::initLeftTest()
{
    pixCharTest << 0xf031 << 0xf036 << 0xf249 << 0xf055 << 0xf05a << 0xf249;
    btnsTest << ui->tbtnTest1 << ui->tbtnTest2 << ui->tbtnTest3 << ui->tbtnTest4 << ui->tbtnTest5 << ui->tbtnTest6;

    int count = btnsTest.count();
    for (int i = 0; i < count; i++) {
        btnsTest.at(i)->setCheckable(true);
        btnsTest.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(btnsTest.at(i), SIGNAL(clicked(bool)), this, SLOT(leftTestClick()));
    }

    IconHelper::Instance()->setStyle(ui->widgetLeftTest, btnsTest, pixCharTest, 10, 20, 15, "left", 5);

    ui->tbtnTest1->click();
}
//窗体底部栏窗口初始化
void FrameMain::config_bottom_button_init()
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
//USBHID查找设备窗口初始化
//void FrameMain::check_device_init()
//{


//    ui->buttonDevice->setButtonEnable(0,true);
//    ui->buttonDevice->setButtonEnable(2,true);

//    connect(ui->buttonDevice, SIGNAL(CustomButtonClicked(int)), this, SLOT(check_deviceClick(int)));

//    /*
//    * 串口号配置
//    */
//    //添加com1~com20
//    QStringList comList;
//    for (int i = 1; i <= 20; i++) {
//        comList << QString("COM%1").arg(i);
//    }
//    //添加到下拉菜单
//    //comList << "ttyUSB0" << "ttyS0" << "ttyS1" << "ttyS2" << "ttyS3" << "ttyS4";
//    ui->comport->addItems(comList);


//}

//void FrameMain::check_deviceClick(int buttonId)
//{

//    if(buttonId == 4)//搜索
//    {
//        bridge->set_communication_hard(bridge->__USBHID);//设置为USBHID
//        bridge->open_communication_hard(bridge->__USBHID);//打开连接

//    }
//    else
//    {
//        qDebug() << buttonId ;
//    }


//}



//顶部导航栏按钮响应事件
void FrameMain::buttonClick()
{
    QToolButton *b = static_cast<QToolButton *>(sender());
    QString name = b->text();

    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach(QToolButton *btn, tbtns) {
        if (btn == b) {
            btn->setChecked(true);
        }
        else {
            btn->setChecked(false);
        }
    }
    if (name == "主界面") {
        ui->stackedWidget->setCurrentIndex(MAIN);
    }
    else if (name == "系统设置") {
        ui->stackedWidget->setCurrentIndex(SETTING);
    }
    else if (name == "设备查询") {
        ui->stackedWidget->setCurrentIndex(DATA);
    }
    else if (name == "调试帮助") {
        ui->stackedWidget->setCurrentIndex(HELP);


    }
    else if (name == "测试后台") {
        ui->stackedWidget->setCurrentIndex(TEST);
    }
    else if (name == "用户退出") {
        exit(0);
    }
}
//主界面按钮响应事件
void FrameMain::leftMainClick()
{
    QToolButton *b = static_cast<QToolButton *>(sender());
    QString name = b->text();

    int count = btnsMain.count();
    for (int i = 0; i < count; i++) {
        if (btnsMain.at(i) == b) {//如果点击该按钮
            btnsMain.at(i)->setChecked(true);
            btnsMain.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsMain.at(i), false)));//Icon变亮
        }
        else {
            btnsMain.at(i)->setChecked(false);
            btnsMain.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsMain.at(i), true)));//Icon变暗
        }
    }

    if (name == "飞控状态") {
        ui->mainStackedWidget->setCurrentIndex(0);
    }
    else if (name == "姿态波形") {
        ui->mainStackedWidget->setCurrentIndex(MAP);
    }
    else if (name == "Map") {
        ui->mainStackedWidget->setCurrentIndex(DEVICE);
    }

}
//设置界面按钮响应事件
void FrameMain::leftConfigClick()
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
//测试界面按钮响应事件
void FrameMain::leftTestClick()
{
    QToolButton *b = static_cast<QToolButton *>(sender());
    QString name = b->text();

    int count = btnsTest.count();
    for (int i = 0; i < count; i++) {
        if (btnsTest.at(i) == b) {
            btnsTest.at(i)->setChecked(true);
            btnsTest.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsTest.at(i), false)));
        }
        else {
            btnsTest.at(i)->setChecked(false);
            btnsTest.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnsTest.at(i), true)));
        }
    }

    if (name == "Serial") {
        ui->testStackedWidget->setCurrentIndex(SERIAL);
    }
    else if (name == "TCP Server") {
        ui->testStackedWidget->setCurrentIndex(TCPSERVER);
    }
    else if (name == "TCP Client") {
        ui->testStackedWidget->setCurrentIndex(TCPCLIENT);
    }
    else if (name == "UDP") {
        ui->testStackedWidget->setCurrentIndex(UDP);
    }
    else if (name == "USB-HID") {
        ui->testStackedWidget->setCurrentIndex(DEVICESETTING);
    }
    else if (name == "其他设置") {
        ui->testStackedWidget->setCurrentIndex(OTHERS);
    }
}


//最小化按钮
void FrameMain::on_btnMenu_Min_clicked()
{
    showMinimized();
}
//最大化按钮
void FrameMain::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    }
    else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        //this->setGeometry(qApp->QGuiApplication::screens());
    }

    this->setProperty("canMove", max);
    max = !max;
}
//退出按钮
void FrameMain::on_btnMenu_Close_clicked()
{
    close();
}


