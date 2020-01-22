#include "package.h"

#include <QDebug>

Package::Package()
{
}

Package::~Package()
{
}

void Package::run()
{
    while (1)
    {

        while (!m_Stopped)
        {
            //qDebug() << "is doing";

            if (m_Get_Mesg)
            {

                for (qint32 i = 0; i < buf_len; i++)
                {
                    Phantom_Data_Receive_Prepare(buf[i]);
                }
                //this->alldata_lengh += static_cast<quint64>(buf_len);
                m_Get_Mesg = false;
            }
        }
        while (m_Stopped);

    }

}

void Package::mystop()
{
    m_Stopped = true;


}
void Package::mystart()
{
    m_Stopped = false;
}
#include <QDebug>

void Package::Phantom_Data_Receive_Prepare(quint8 data)
{
    static quint8 _data_len = 0;
    static quint8 state = 0;

        if(state==0&&data==0xAA)	//帧头0xAA
        {
            state=1;
            DT_RxBuffer[0]=data;
        }
        else if(state==1&&data==0x05)	//数据源，0xAF表示数据来自上位机
        {
            state=2;
            DT_RxBuffer[1]=data;
        }
        else if(state==2)		//数据目的地
        {
            state=3;
            DT_RxBuffer[2]=data;
        }
        else if(state==3)		//功能字
        {
            state=4;
            DT_RxBuffer[3]=data;
        }
        else if(state==4)		//数据长度
        {
            state = 5;
            DT_RxBuffer[4]=data;
            _data_len = data;
            DT_data_cnt = 0;
        }
        else if(state==5&&_data_len>0)
        {
            _data_len--;
            DT_RxBuffer[5+DT_data_cnt++]=data;
            if(_data_len==0)
                state = 6;
        }
        else if(state==6)
        {
            state = 0;
            DT_RxBuffer[5+DT_data_cnt]=data;
            ano_dt_data_ok = 1;
            Phantom_Data_Receive_Anl(DT_RxBuffer, DT_data_cnt + 6);


        }
        else
            state = 0;

}




/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
//校验通过后对数据进行解析，实现相应功能
//此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
//uint16_t flash_save_en_cnt = 0;
void Package::Phantom_Data_Receive_Anl(quint8 *data_buf, quint8 num)

{
    uint8_t sum = 0;

    for(uint8_t i=0;i<(num-1);i++)
        sum += *(data_buf+i);
    if(!(sum==*(data_buf+num-1)))		return;		//判断sum
    if(!(*(data_buf)==0xAA && *(data_buf+1)==0x05))		return;		//判断帧头

    if (*(data_buf + 3) == 0X01)//姿态等基本信息
    {
        this->plane_ROL = static_cast<float>(static_cast<qint16>(*(data_buf + 5) << 8) | *(data_buf + 6))  / 100;
        this->plane_PIT = static_cast<float>(static_cast<qint16>(*(data_buf + 7) << 8) | *(data_buf + 8))  / 100;
        this->plane_YAW = static_cast<float>(static_cast<qint16>(*(data_buf + 9) << 8) | *(data_buf + 10)) / 100;

        this->plane_ALT_USE = static_cast<qint32>(((*(data_buf + 11)) << 24) + //高度cm
                        ((*(data_buf + 12)) << 16) +
                        ((*(data_buf + 13)) << 8) +
                        (*(data_buf + 14)));
        this->plane_FLY_MODEL = static_cast<quint8>(*(data_buf + 14));//飞行模式
        this->plane_ARMED = static_cast<quint8>(*(data_buf + 15));//0：加锁   1：解锁



        imu_signals();

    }
    else if (*(data_buf + 3) == 0X02)//传感器数据
    {
        this->plane_ACC_X =  static_cast<qint16>(*(data_buf + 5) << 8) | *(data_buf + 6);
        this->plane_ACC_Y =  static_cast<qint16>(*(data_buf + 7) << 8) | *(data_buf + 8);
        this->plane_ACC_Z =  static_cast<qint16>(*(data_buf + 9) << 8) | *(data_buf + 10);
        this->plane_GYRO_X = static_cast<qint16>(*(data_buf + 11) << 8) | *(data_buf + 12);
        this->plane_GYRO_Y = static_cast<qint16>(*(data_buf + 13) << 8) | *(data_buf + 14);
        this->plane_GYRO_Z = static_cast<qint16>(*(data_buf + 15) << 8) | *(data_buf + 16);
        this->plane_MAG_X =  static_cast<qint16>(*(data_buf + 17) << 8) | *(data_buf + 18);
        this->plane_MAG_Y =  static_cast<qint16>(*(data_buf + 19) << 8) | *(data_buf + 20);
        this->plane_MAG_Z =  static_cast<qint16>(*(data_buf + 21) << 8) | *(data_buf + 22);

    }
    else if (*(data_buf + 3) == 0X03)//控制数据
    {
        this->remote_THR = static_cast<qint16>(*(data_buf + 5) << 8) | *(data_buf + 6);
        this->remote_YAW = static_cast<qint16>(*(data_buf + 7) << 8) | *(data_buf + 8);
        this->remote_ROL = static_cast<qint16>(*(data_buf + 9) << 8) | *(data_buf + 10);
        this->remote_PIT = static_cast<qint16>(*(data_buf + 11) << 8) | *(data_buf + 12);
        this->remote_AUX1 = static_cast<qint16>(*(data_buf + 13) << 8) | *(data_buf + 14);
        this->remote_AUX2 = static_cast<qint16>(*(data_buf + 15) << 8) | *(data_buf + 16);
        this->remote_AUX3 = static_cast<qint16>(*(data_buf + 17) << 8) | *(data_buf + 18);
        this->remote_AUX4 = static_cast<qint16>(*(data_buf + 19) << 8) | *(data_buf + 20);
        this->remote_AUX5 = static_cast<qint16>(*(data_buf + 21) << 8) | *(data_buf + 22);
        this->remote_AUX6 = static_cast<qint16>(*(data_buf + 23) << 8) | *(data_buf + 24);
    }
    else if (*(data_buf + 2) == 0X04)//实时GPS信息
    {



    }
    else if (*(data_buf + 3) == 0X05)//
    {


    }
    else if (*(data_buf + 2) == 0X06)//马达PWM（范围：0-1000）
    {


    }
    else if (*(data_buf + 3) == 0X07)//板载气压计，附加测高传感器
    {

    }
}


float Package::get_plane_pitch()
{
    return this->plane_PIT;
}

float Package::get_plane_roll()
{
    return this->plane_ROL;
}
float Package::get_plane_yaw()
{
    return this->plane_YAW;
}

qint16 Package::get_plane_accx()
{
    return this->plane_ACC_X;
}
qint16 Package::get_plane_accy()
{
    return this->plane_ACC_Y;
}
qint16 Package::get_plane_accz()
{
    return this->plane_ACC_Z;
}
qint16 Package::get_plane_gyrox()
{
    return this->plane_GYRO_X;
}
qint16 Package::get_plane_gyroy()
{
    return this->plane_GYRO_Y;
}
qint16 Package::get_plane_gyroz()
{
    return this->plane_GYRO_Z;
}
qint16 Package::get_plane_magx()
{
    return this->plane_MAG_X;
}
qint16 Package::get_plane_magy()
{
    return this->plane_MAG_Y;
}
qint16 Package::get_plane_magz()
{
    return this->plane_MAG_Z;
}

qint16 Package::get_remote_thr()
{
    return this->remote_THR;
}
qint16 Package::get_remote_pit()
{
    return this->remote_PIT;
}
qint16 Package::get_remote_rol()
{
    return this->remote_ROL;
}
qint16 Package::get_remote_yaw()
{
    return this->remote_YAW;
}
qint16 Package::get_remote_aux1()
{
    return this->remote_AUX1;
}
qint16 Package::get_remote_aux2()
{
    return this->remote_AUX2;
}
qint16 Package::get_remote_aux3()
{
    return this->remote_AUX3;
}
qint16 Package::get_remote_aux4()
{
    return this->remote_AUX4;
}
qint16 Package::get_remote_aux5()
{
    return this->remote_AUX5;
}
qint16 Package::get_remote_aux6()
{
    return this->remote_AUX6;
}

quint64 Package::get_recv_length()
{
    return this->alldata_lengh;
}

void Package::reset_recv_length()
{
    this->alldata_lengh = 0;
}

