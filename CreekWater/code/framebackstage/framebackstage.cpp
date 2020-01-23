#include "framebackstage.h"
#include "iconhelper.h"
#include "frameserial.h"

FrameBackstage::FrameBackstage(Ui_FrameMain *m_ui)
{
    ui = m_ui;

    initLeftButton();

    FrameSerial *serial;
    serial = new FrameSerial(ui);
}


//左列按钮ttf初始化
void FrameBackstage::initLeftButton()
{
    pixCharList << 0xf030 << 0xf03e << 0xf247 << 0xf030 << 0xf03e << 0xf247;
    btnList << ui->backstageLeftBtnSerial << ui->backstageLeftBtnTeminal
             << ui->backstageLeftBtnTcpServer << ui->backstageLeftBtnTcpClient
             << ui->backstageLeftBtnUdp << ui->backstageLeftBtnUsbhid;

    int count = btnList.count();
    for (int i = 0; i < count; i++) {
        btnList.at(i)->setCheckable(true);
        btnList.at(i)->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(btnList.at(i), SIGNAL(clicked(bool)), this, SLOT(leftBtnListClick()));
    }

    IconHelper::Instance()->setStyle(ui->backstageLeftWidget, btnList, pixCharList, 15, 35, 25, "left", 4);

    ui->backstageLeftBtnSerial->click();
}

//主界面按钮响应事件
void FrameBackstage::leftBtnListClick()
{
    QToolButton *b = static_cast<QToolButton *>(sender());
    QString name = b->text();

    int count = btnList.count();
    for (int i = 0; i < count; i++) {
        if (btnList.at(i) == b) {//如果点击该按钮
            btnList.at(i)->setChecked(true);
            btnList.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnList.at(i), false)));//Icon变亮
        }
        else {
            btnList.at(i)->setChecked(false);
            btnList.at(i)->setIcon(QIcon(IconHelper::Instance()->getPixmap(btnList.at(i), true)));//Icon变暗
        }
    }

    if (name == "Serial") {
        ui->backstageStackedWidget->setCurrentIndex(0);
    }
    else if (name == "Terminal") {
        ui->backstageStackedWidget->setCurrentIndex(TERMINAL);
    }
    else if (name == "TCP Server") {
        ui->backstageStackedWidget->setCurrentIndex(TCPSERVER);
    }
    else if (name == "TCP Client") {
        ui->backstageStackedWidget->setCurrentIndex(TCPCLIENT);
    }
    else if (name == "UDP") {
        ui->backstageStackedWidget->setCurrentIndex(UDP);
    }
    else if (name == "USB-HID") {
        ui->backstageStackedWidget->setCurrentIndex(USBHID);
    }

}
