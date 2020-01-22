#include "framestate.h"

#include <QDebug>

#include "iconhelper.h"
#include "package_ano_422.h"


#include "waveform.h"

FrameState::FrameState(Ui_FrameMain *mui, Bridge *m_bridge)
{
    ui = mui;
    this->bridge = m_bridge;
    waveform = new WaveForm();

    initLeftMain();

    mainPlane_init();

    /*
    **定时器实时更新UI界面
    */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    timer->start(50);

    //解析成功信号绑定
    connect(package_ano_422,
            SIGNAL(signalnew1(float , float , float , float , quint8 , quint8 )),
            this,
            SLOT(slotnew1(float , float , float , float , quint8 , quint8 )));
    connect(package_ano_422,
            SIGNAL(signalnew2(qint16 , qint16 , qint16 , qint16 , qint16 , qint16, qint16 , qint16 , qint16 )),
            this,
            SLOT(slotnew2(qint16 , qint16 , qint16 , qint16 , qint16 , qint16, qint16 , qint16 , qint16 )));
    connect(package_ano_422,
            SIGNAL(signalnew3(qint16 , qint16 , qint16 , qint16 , qint16 , qint16, qint16 , qint16 , qint16, qint16)),
            this,
            SLOT(slotnew3(qint16 , qint16 , qint16 , qint16 , qint16 , qint16, qint16 , qint16 , qint16, qint16 )));
    connect(package_ano_422,
            SIGNAL(signalnew5(float , float )),
            this,
            SLOT(slotnew5(float, float)));
    connect(package_ano_422,
            SIGNAL(signalnew6(quint16 , quint16 , quint16 , quint16 , quint16 , quint16, quint16 , quint16)),
            this,
            SLOT(slotnew6(quint16 , quint16 , quint16 , quint16 , quint16 , quint16, quint16 , quint16)));
    connect(package_ano_422,
            SIGNAL(signalnew7(float , float )),
            this,
            SLOT(slotnew7(float, float)));
}

//主界面左列按钮ttf初始化
void FrameState::initLeftMain()
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
void FrameState::leftMainClick()
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


//界面颜色设置，遥控器进度条设置
void FrameState::mainPlane_init()
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

    //电机输出
    ui->stateMotor1->setTextName("M1");
    ui->stateMotor2->setTextName("M2");
    ui->stateMotor3->setTextName("M3");
    ui->stateMotor4->setTextName("M4");
    ui->stateMotor5->setTextName("M5");
    ui->stateMotor6->setTextName("M6");
    ui->stateMotor7->setTextName("M7");
    ui->stateMotor8->setTextName("M8");

    ui->stateMotor1->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor2->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor3->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor4->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor5->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor6->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor7->setUsedColor(QColor(71, 203, 94));
    ui->stateMotor8->setUsedColor(QColor(71, 203, 94));

}


//界面定时更新
void FrameState::uiUpdate()
{
    waveform->updateData(this->plane_ROL);

    //电机输出
    ui->stateMotor1->setValue(static_cast<int>(this->plane_PWM_MOTO1));
    ui->stateMotor2->setValue(static_cast<int>(this->plane_PWM_MOTO2));
    ui->stateMotor3->setValue(static_cast<int>(this->plane_PWM_MOTO3));
    ui->stateMotor4->setValue(static_cast<int>(this->plane_PWM_MOTO4));
    ui->stateMotor5->setValue(static_cast<int>(this->plane_PWM_MOTO5));
    ui->stateMotor6->setValue(static_cast<int>(this->plane_PWM_MOTO6));
    ui->stateMotor7->setValue(static_cast<int>(this->plane_PWM_MOTO7));
    ui->stateMotor8->setValue(static_cast<int>(this->plane_PWM_MOTO8));

    //罗盘
    ui->widget_plane->setDegValue(static_cast<int>(this->plane_ROL));
    ui->widget_plane->setRollValue(static_cast<int>(this->plane_PIT));
    ui->widget_plane->setYawValue(static_cast<int>(this->plane_YAW));

    /*
    **左下角更新
    */
    ui->rolLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ROL)));
    ui->pitLabel->setText(tr("%1").arg(static_cast<double>(this->plane_PIT)));
    ui->yawLabel->setText(tr("%1").arg(static_cast<double>(this->plane_YAW)));

    ui->heightLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ALT_USE)));


    switch(this->plane_ARMED)
    {
        case 0:ui->lockLabel->setText("锁定");break;
        case 1:ui->lockLabel->setText("解锁");break;
        default:break;
    }

    switch(this->plane_FLY_MODEL)
    {
        case 1:ui->flymodeLabel->setText("姿态");break;
        case 2:ui->flymodeLabel->setText("定高");break;
        case 3:ui->flymodeLabel->setText("定点");break;
        default:break;
    }

    //传感器
    ui->accxValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ACC_X)));
    ui->accyValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ACC_Y)));
    ui->acczValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ACC_Z)));
    ui->gyrxValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_GYRO_X)));
    ui->gyryValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_GYRO_Y)));
    ui->gyrzValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_GYRO_Z)));
    ui->magxValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_MAG_X)));
    ui->magyValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_MAG_Y)));
    ui->magzValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_MAG_Z)));

    //板载气压计，附加高度
    ui->altValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ALT_BRA)));
    ui->altAdditionValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_ALT_ADDITION)));

    //电压电流
    ui->voltageValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_Votage)));
    ui->currentValueLabel->setText(tr("%1").arg(static_cast<double>(this->plane_Current)));

    //遥控器
    ui->widget_remote_thr->setValue(static_cast<qint16>(this->remote_THR));
    ui->widget_remote_yaw->setValue(static_cast<int>(this->remote_YAW));
    ui->widget_remote_rol->setValue(static_cast<int>(this->remote_ROL));
    ui->widget_remote_pit->setValue(static_cast<int>(this->remote_PIT));
    ui->widget_remote_aux1->setValue(static_cast<int>(this->remote_AUX1));
    ui->widget_remote_aux2->setValue(static_cast<int>(this->remote_AUX2));
    ui->widget_remote_aux3->setValue(static_cast<int>(this->remote_AUX3));
    ui->widget_remote_aux4->setValue(static_cast<int>(this->remote_AUX4));
    ui->widget_remote_aux5->setValue(static_cast<int>(this->remote_AUX5));
    ui->widget_remote_aux6->setValue(static_cast<int>(this->remote_AUX6));
}




void FrameState::slotnew1(float plane_ROL, float plane_PIT, float plane_YAW,
             float plane_ALT_USE, quint8 plane_FLY_MODEL, quint8 plane_ARMED)
{
    this->plane_ROL = plane_ROL;
    this->plane_PIT = plane_PIT;
    this->plane_YAW = plane_YAW;
    this->plane_ALT_USE = plane_ALT_USE;
    this->plane_FLY_MODEL = plane_FLY_MODEL;
    this->plane_ARMED = plane_ARMED;
}
void FrameState::slotnew2(qint16 plane_ACC_X, qint16 plane_ACC_Y, qint16 plane_ACC_Z,
                qint16 plane_GYRO_X, qint16 plane_GYRO_Y, qint16 plane_GYRO_Z,
                qint16 plane_MAG_X, qint16 plane_MAG_Y, qint16 plane_MAG_Z)
{
    this->plane_ACC_X = plane_ACC_X;
    this->plane_ACC_Y = plane_ACC_Y;
    this->plane_ACC_Z = plane_ACC_Z;
    this->plane_GYRO_X = plane_GYRO_X;
    this->plane_GYRO_Y = plane_GYRO_Y;
    this->plane_GYRO_Z = plane_GYRO_Z;
    this->plane_MAG_X = plane_MAG_X;
    this->plane_MAG_Y = plane_MAG_Y;
    this->plane_MAG_Z = plane_MAG_Z;
}
void FrameState::slotnew3(qint16 remote_THR, qint16 remote_YAW, qint16 remote_ROL, qint16 remote_PIT,
                qint16 remote_AUX1,
                qint16 remote_AUX2,
                qint16 remote_AUX3,
                qint16 remote_AUX4,
                qint16 remote_AUX5,
                qint16 remote_AUX6)
{
    this->remote_THR = remote_THR;
    this->remote_YAW = remote_YAW;
    this->remote_ROL = remote_ROL;
    this->remote_PIT = remote_PIT;
    this->remote_AUX1 = remote_AUX1;
    this->remote_AUX2 = remote_AUX2;
    this->remote_AUX3 = remote_AUX3;
    this->remote_AUX4 = remote_AUX4;
    this->remote_AUX5 = remote_AUX5;
    this->remote_AUX6 = remote_AUX6;
}

void FrameState::slotnew5(float plane_Votage, float plane_Current)
{
    this->plane_Votage = plane_Votage;
    this->plane_Current = plane_Current;
}
void FrameState::slotnew6(quint16 plane_PWM_MOTO1, quint16 plane_PWM_MOTO2,
                quint16 plane_PWM_MOTO3, quint16 plane_PWM_MOTO4,
                quint16 plane_PWM_MOTO5, quint16 plane_PWM_MOTO6,
                quint16 plane_PWM_MOTO7, quint16 plane_PWM_MOTO8)
{
    this->plane_PWM_MOTO1 = plane_PWM_MOTO1;
    this->plane_PWM_MOTO2 = plane_PWM_MOTO2;
    this->plane_PWM_MOTO3 = plane_PWM_MOTO3;
    this->plane_PWM_MOTO4 = plane_PWM_MOTO4;
    this->plane_PWM_MOTO5 = plane_PWM_MOTO5;
    this->plane_PWM_MOTO6 = plane_PWM_MOTO6;
    this->plane_PWM_MOTO7 = plane_PWM_MOTO7;
    this->plane_PWM_MOTO8 = plane_PWM_MOTO8;
}
void FrameState::slotnew7(float plane_ALT_BRA, float plane_ALT_ADDITION)
{
    this->plane_ALT_BRA = plane_ALT_BRA;
    this->plane_ALT_ADDITION = plane_ALT_ADDITION;
}











