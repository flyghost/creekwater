#include "bridge.h"


Bridge::Bridge(Ui_FrameMain *m_ui)
{
    this->ui = m_ui;

//    usbhid = new USBHID();
}

void Bridge::set_communication_hard(quint8 hard)
{
    com_hard = hard;

    this->communication_hard_init();
}

void Bridge::communication_hard_init()
{
    if(com_hard == __USBHID)//使用usbhid作为通信底层
    {
//        usbhid->usb_hid_device_find();
//        device_name = 0xa005;

    }
    else if(com_hard == __SERIAL)
    {
        //待添加
    }
}

void Bridge::open_communication_hard(quint8 hard)
{
    if(hard == __USBHID)
    {


//        bool ret = usbhid->usb_hid_device_open();

//        if (ret)
//        {
//            usbhid->start();
//            usbhid->mystart();
//        }
    }
    else
    {

    }
}

void Bridge::close_communication_hard(quint8 hard)
{
    if(hard == __USBHID)
    {
//        usbhid->mystop();
    }
    else
    {

    }
}



float Bridge::get_plane_pitch()
{
//    return usbhid->package.get_plane_pitch();
}

float Bridge::get_plane_roll()
{
//    return usbhid->package.get_plane_roll();
}
float Bridge::get_plane_yaw()
{
//    return usbhid->package.get_plane_yaw();
}
qint16 Bridge::get_plane_accx()
{
//    return usbhid->package.get_plane_accx();
}
qint16 Bridge::get_plane_accy()
{
//    return usbhid->package.get_plane_accy();
}
qint16 Bridge::get_plane_accz()
{
//    return usbhid->package.get_plane_accz();
}
qint16 Bridge::get_plane_gyrox()
{
//    return usbhid->package.get_plane_gyrox();
}
qint16 Bridge::get_plane_gyroy()
{
//    return usbhid->package.get_plane_gyroy();
}
qint16 Bridge::get_plane_gyroz()
{
//    return usbhid->package.get_plane_gyroz();
}
qint16 Bridge::get_plane_magx()
{
//    return usbhid->package.get_plane_magx();
}
qint16 Bridge::get_plane_magy()
{
//    return usbhid->package.get_plane_magy();
}
qint16 Bridge::get_plane_magz()
{
//    return usbhid->package.get_plane_magz();
}

qint16 Bridge::get_remote_thr()
{
//    return usbhid->package.get_remote_thr();
}
qint16 Bridge::get_remote_pit()
{
//    return usbhid->package.get_remote_pit();
}
qint16 Bridge::get_remote_rol()
{
//    return usbhid->package.get_remote_rol();
}
qint16 Bridge::get_remote_yaw()
{
//    return usbhid->package.get_remote_yaw();
}
qint16 Bridge::get_remote_aux1()
{
//    return usbhid->package.get_remote_aux1();
}
qint16 Bridge::get_remote_aux2()
{
//    return usbhid->package.get_remote_aux2();
}
qint16 Bridge::get_remote_aux3()
{
//    return usbhid->package.get_remote_aux3();
}
qint16 Bridge::get_remote_aux4()
{
//    return usbhid->package.get_remote_aux4();
}
qint16 Bridge::get_remote_aux5()
{
//    return usbhid->package.get_remote_aux5();
}
qint16 Bridge::get_remote_aux6()
{
//    return usbhid->package.get_remote_aux6();
}







