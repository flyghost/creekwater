#ifndef PACKAGE_H
#define PACKAGE_H


#include <QThread>
#include "CreekWater/code/package/packagedata.h"

class Package : public QThread
{
    Q_OBJECT

public:
    Package();
    ~Package();


protected:
    void run();
private:
    volatile bool m_Stopped = true;

public:
    void mystart();
    void mystop();
    volatile bool m_Get_Mesg = false;
    quint8 m_mesg;
    unsigned char buf[256];
    qint32 buf_len;

private:
#define GRUOUDADDR 0x05 //下位机地址
#define MYHWADDR   0xAF //上位机地址
private:
    quint64 alldata_lengh;
public:
    quint8 ano_dt_data_ok;
    quint8 DT_RxBuffer[256], DT_data_cnt = 0;// , ano_dt_data_ok;

    //数传0x10
    //拓空者0x05
    int device_name = 0x00;
    bool device_find = false;
    bool device_0x10 = false;//数传是否连接
    bool device_0x05 = false;//拓空者是否连接
    bool device_0x04 = false;//领航者是否连接


private:
    float plane_ROL = 0;//俯仰角*100
    float plane_PIT = 0;//*100
    float plane_YAW = 0;//*100
    qint32 plane_ALT_USE = 0 ;//高度cm
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

public:
    float get_plane_pitch();
    float get_plane_roll();
    float get_plane_yaw();

    qint16 get_plane_accx();
    qint16 get_plane_accy();
    qint16 get_plane_accz();
    qint16 get_plane_gyrox();
    qint16 get_plane_gyroy();
    qint16 get_plane_gyroz();
    qint16 get_plane_magx();
    qint16 get_plane_magy();
    qint16 get_plane_magz();

    qint16 get_remote_thr();
    qint16 get_remote_yaw();
    qint16 get_remote_rol();
    qint16 get_remote_pit();
    qint16 get_remote_aux1();
    qint16 get_remote_aux2();
    qint16 get_remote_aux3();
    qint16 get_remote_aux4();
    qint16 get_remote_aux5();
    qint16 get_remote_aux6();


    float get_plane_votage();
    float get_plane_current();



    quint64 get_recv_length();
    void reset_recv_length();
public:
    void Phantom_Data_Receive_Prepare(quint8 data);
    void Phantom_Data_Receive_Anl(quint8 *data_buf, quint8 num);
    void Phantom_Data_Receive_Anl_Task();


signals:
    void imu_signals();

};

#endif // PACKAGE_H
