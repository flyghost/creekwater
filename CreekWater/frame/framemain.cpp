#include "framemain.h"

#include "ui_framemain.h"
#include <QDebug>

#include "iconhelper.h"

FrameMain::FrameMain(Ui_FrameMain *mui, Bridge *m_bridge)
{
    ui = mui;
    this->bridge = m_bridge;

    initLeftMain();

    mainPlane_init();

    /*
    **定时器实时更新UI界面
    */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    timer->start(50);
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



void FrameMain::mainPlane_init()
{
    /*
    **飞机姿态
    */
    ui->flymodeLabel->setStyleSheet("QLabel{font:18pt;color:#aa5500}");
    ui->lockLabel->setStyleSheet("QLabel{font:18pt;color:#3134ff}");
    ui->gpsLabel->setStyleSheet("QLabel{font:18pt;color:#aaaa00}");

    ui->heightLabel->setStyleSheet("QLabel{font:18pt;color:#00aa7f}");
    ui->horizontalspeedLabel->setStyleSheet("QLabel{font:18pt;color:#00ff7f}");
    ui->verticalspeedLabel->setStyleSheet("QLabel{font:18pt;color:#00ffff}");

    ui->rolLabel->setStyleSheet("QLabel{font:18pt;color:#ff557f}");
    ui->pitLabel->setStyleSheet("QLabel{font:18pt;color:#ff00ff}");
    ui->yawLabel->setStyleSheet("QLabel{font:18pt;color:#ffaaff}");

    /*
    **遥控器值
    */


    ui->widget_remote_thr->setRange(1000, 2000);
    ui->widget_remote_thr->setBarText("THR\r\n");

    ui->widget_remote_yaw->setRange(1000, 2000);
    ui->widget_remote_yaw->setBarText("YAW\r\n");

    ui->widget_remote_rol->setRange(1000, 2000);
    ui->widget_remote_rol->setBarText("ROL\r\n");

    ui->widget_remote_pit->setRange(1000, 2000);
    ui->widget_remote_pit->setBarText("PIT\r\n");

    ui->widget_remote_aux1->setRange(1000, 2000);
    ui->widget_remote_aux1->setBarText("AUX1\r\n");

    ui->widget_remote_aux2->setRange(1000, 2000);
    ui->widget_remote_aux2->setBarText("AUX2\r\n");

    ui->widget_remote_aux3->setRange(1000, 2000);
    ui->widget_remote_aux3->setBarText("AUX3\r\n");

    ui->widget_remote_aux4->setRange(1000, 2000);
    ui->widget_remote_aux4->setBarText("AUX4\r\n");

    ui->widget_remote_aux5->setRange(1000, 2000);
    ui->widget_remote_aux5->setBarText("AUX5\r\n");

    ui->widget_remote_aux6->setRange(1000, 2000);
    ui->widget_remote_aux6->setBarText("AUX6\r\n");




}



void FrameMain::uiUpdate()
{
    //罗盘
    ui->widget_plane->setDegValue(static_cast<int>(bridge->get_plane_roll()));
    ui->widget_plane->setRollValue(static_cast<int>(bridge->get_plane_pitch()));
    ui->widget_plane->setYawValue(static_cast<int>(bridge->get_plane_yaw()));

    /*
    **左下角更新
    */
    ui->rolLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_roll())));
    ui->pitLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_pitch())));
    ui->yawLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_yaw())));

    //传感器
    ui->accxValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_accx())));
    ui->accyValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_accy())));
    ui->acczValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_accz())));
    ui->gyrxValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_gyrox())));
    ui->gyryValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_gyroy())));
    ui->gyrzValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_gyroz())));
    ui->magxValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_magx())));
    ui->magyValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_magy())));
    ui->magzValueLabel->setText(tr("%1").arg(static_cast<double>(bridge->get_plane_magz())));

    //遥控器
    ui->widget_remote_thr->setValue(static_cast<qint16>(bridge->get_remote_thr()));
    ui->widget_remote_yaw->setValue(static_cast<int>(bridge->get_remote_yaw()));
    ui->widget_remote_rol->setValue(static_cast<int>(bridge->get_remote_rol()));
    ui->widget_remote_pit->setValue(static_cast<int>(bridge->get_remote_pit()));
    ui->widget_remote_aux1->setValue(static_cast<int>(bridge->get_remote_aux1()));
    ui->widget_remote_aux2->setValue(static_cast<int>(bridge->get_remote_aux2()));
    ui->widget_remote_aux3->setValue(static_cast<int>(bridge->get_remote_aux3()));
    ui->widget_remote_aux4->setValue(static_cast<int>(bridge->get_remote_aux4()));
    ui->widget_remote_aux5->setValue(static_cast<int>(bridge->get_remote_aux5()));
    ui->widget_remote_aux6->setValue(static_cast<int>(bridge->get_remote_aux6()));
}
