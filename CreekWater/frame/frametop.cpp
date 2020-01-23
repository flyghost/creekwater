#include "frametop.h"
#include "framebottom.h"
#include "framestate.h"
#include "frameconnect.h"
#include "frameserial.h"
#include "frameplanesetting.h"
#include "framebackstage.h"


#include "ui_framemain.h"
#include <QDebug>

#include "iconhelper.h"



FrameTop::FrameTop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameMain)
{
    ui->setupUi(this);
    this->initForm();

    bridge = new Bridge(ui);

    FrameBottom *bottom;
    bottom = new FrameBottom(ui);

    FrameState *state;
    state = new FrameState(ui,bridge);

    FrameConnect *connect;
    connect = new FrameConnect(ui,bridge);

    FrameBackstage *backstage;
    backstage = new FrameBackstage(ui);

    FramePlaneSetting *planesetting;
    planesetting = new FramePlaneSetting(ui);
}


FrameTop::~FrameTop()
{
    delete ui;
}


//顶部导航栏初始化
void FrameTop::initForm()
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




//顶部导航栏按钮响应事件
void FrameTop::buttonClick()
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


//最小化按钮
void FrameTop::on_btnMenu_Min_clicked()
{
    showMinimized();
}
//最大化按钮
void FrameTop::on_btnMenu_Max_clicked()
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
void FrameTop::on_btnMenu_Close_clicked()
{
    close();
}

