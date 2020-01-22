#ifndef FRAMESTATE_H
#define FRAMESTATE_H




#include "bridge.h"
#include "frmcomtool.h"
#include "maininterface.h"
#include "settinginterface.h"


#include <QWidget>

class FrameState : public QWidget
{
    Q_OBJECT

public:
    explicit FrameState(Ui_FrameMain *mui, Bridge *m_bridge);

private:
    Ui_FrameMain *ui;
    Bridge *bridge;

    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;
private:

    enum {
        VIDEO = 0,
        MAP, DEVICE
    };

private:
    void initLeftMain();
    void mainPlane_init();


private slots:
    void leftMainClick();//左列按钮槽
    void uiUpdate();//界面更新定时器
    void slotnew1(float plane_ROL, float plane_PIT, float plane_YAW,
                  float plane_ALT_USE, quint8 plane_FLY_MODEL, quint8 plane_ARMED);
    void slotnew2(qint16 plane_ACC_X, qint16 plane_ACC_Y, qint16 plane_ACC_Z,
                    qint16 plane_GYRO_X, qint16 plane_GYRO_Y, qint16 plane_GYRO_Z,
                    qint16 plane_MAG_X, qint16 plane_MAG_Y, qint16 plane_MAG_Z);
    void slotnew3(qint16 remote_THR, qint16 remote_YAW, qint16 remote_ROL, qint16 remote_PIT,
                    qint16 remote_AUX1,
                    qint16 remote_AUX2,
                    qint16 remote_AUX3,
                    qint16 remote_AUX4,
                    qint16 remote_AUX5,
                    qint16 remote_AUX6);
    void slotnew5(float plane_Votage, float plane_Current);
    void slotnew6(quint16 plane_PWM_MOTO1, quint16 plane_PWM_MOTO2,
                    quint16 plane_PWM_MOTO3, quint16 plane_PWM_MOTO4,
                    quint16 plane_PWM_MOTO5, quint16 plane_PWM_MOTO6,
                    quint16 plane_PWM_MOTO7, quint16 plane_PWM_MOTO8);
    void slotnew7(float plane_ALT_BRA, float plane_ALT_ADDITION);




private:
    float plane_ROL = 0;//俯仰角*100
    float plane_PIT = 0;//*100
    float plane_YAW = 0;//*100
    float plane_ALT_USE = 0 ;//高度cm
    quint8 plane_FLY_MODEL = 0 ;//飞行模式
    quint8 plane_ARMED = 0 ;//0加锁  1解锁

    qint16 plane_ACC_X = 0;//传感器数据
    qint16 plane_ACC_Y = 0;
    qint16 plane_ACC_Z = 0;
    qint16 plane_GYRO_X = 0;
    qint16 plane_GYRO_Y = 0;
    qint16 plane_GYRO_Z = 0;
    qint16 plane_MAG_X = 0;
    qint16 plane_MAG_Y = 0;
    qint16 plane_MAG_Z = 0;

    qint16 remote_THR = 0 ;//遥控器数据
    qint16 remote_YAW = 0 ;
    qint16 remote_ROL = 0 ;
    qint16 remote_PIT = 0 ;
    qint16 remote_AUX1 = 0;
    qint16 remote_AUX2 = 0;
    qint16 remote_AUX3 = 0;
    qint16 remote_AUX4 = 0;
    qint16 remote_AUX5 = 0;
    qint16 remote_AUX6 = 0;

    float plane_Votage = 0;//电源*100
    float plane_Current = 0;//*100

    quint16 plane_PWM_MOTO1 = 0;//电机输出PWM(0~1000)
    quint16 plane_PWM_MOTO2 = 0;
    quint16 plane_PWM_MOTO3 = 0;
    quint16 plane_PWM_MOTO4 = 0;
    quint16 plane_PWM_MOTO5 = 0;
    quint16 plane_PWM_MOTO6 = 0;
    quint16 plane_PWM_MOTO7 = 0;
    quint16 plane_PWM_MOTO8 = 0;

    float plane_ALT_BRA = 0;//板载气压计高度，精确到0.01cm        //*100
    float plane_ALT_ADDITION = 0;//附加测高传感器，精确到0.01cm   //*100
    float plane_SEN_TMP = 0;//传感器温度，精确到0.1              //*10

};
















#endif // FRAMEBOTTOM_H
