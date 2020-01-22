//主界面设置



#include "maininterface.h"

#include <QTimer>



MainInterface::MainInterface(Ui::FrameMain *m_ui, Bridge *m_bridge)
{
    ui = m_ui;
    this->bridge = m_bridge;

    mainPlane_init();

    /*
    **定时器实时更新UI界面
    */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    timer->start(50);

}

void MainInterface::mainPlane_init()
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



void MainInterface::uiUpdate()
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
