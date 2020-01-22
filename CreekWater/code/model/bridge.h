#ifndef BRIDGE_H
#define BRIDGE_H

#include "ui_framemain.h"
//#include "CreekWater/code/hardware/usbhid/usbhid.h"


class Bridge
{
public:
    Bridge(Ui_FrameMain *m_ui);
    Ui_FrameMain *ui;

private:
//    USBHID *usbhid;

    quint8 com_hard;//通信底层选择

public:
    enum communication_driver{
        __USBHID = 10,//通信底层
        __SERIAL,
    };

public:
    void open_communication_hard(quint8 hard);//打开底层通信
    void close_communication_hard(quint8 hard);//关闭底层通信
    void set_communication_hard(quint8 hard);//设置通信底层
    void communication_hard_init();//通信底层初始化

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


    quint64 get_recv_length();
    void reset_recv_length();


};

#endif // BRIDGE_H
