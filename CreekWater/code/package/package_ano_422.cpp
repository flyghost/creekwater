#include "package_ano_422.h"

#include <QDebug>



Package_ANO_422 *package_ano_422 = new Package_ANO_422();


Package_ANO_422::Package_ANO_422()
{
    this->moveToThread(&thread);
    this->thread.start();

    //    connect(thread, &QThread::finished, package_ano_422, &QObject::deleteLater);
}

Package_ANO_422::~Package_ANO_422()
{

}

void Package_ANO_422::print_thread_id()
{
    qDebug()<<"     package ano 422  thread ID:"<<QThread::currentThreadId()<<'\n';
}

void Package_ANO_422::DataPreProcessing(quint8 data)
{
        static uint8_t _data_len = 0;
        static uint8_t state = 0;
        static uint8_t _data_cnt = 0;
        static quint8 DT_RxBuffer[256];

        if (state == 0 && data == 0xAA)
        {
            state = 1;
            DT_RxBuffer[0] = data;
        }
        else if (state == 1 && data == 0xAA)
        {
            state = 2;
            DT_RxBuffer[1] = data;
        }
        else if (state == 2)
        {
            state = 3;
            DT_RxBuffer[2] = data;
        }
        else if (state == 3)
        {
            state = 4;
            DT_RxBuffer[3] = data;
            _data_len = data;
            _data_cnt = 0;
        }
        else if (state == 4 && _data_len>0)
        {
            _data_len--;
            DT_RxBuffer[4 + _data_cnt++] = data;
            if (_data_len == 0)
                state = 5;
        }
        else if (state == 5)
        {
            state = 0;
            DT_RxBuffer[4 + _data_cnt] = data;
            DataProcessing(DT_RxBuffer, _data_cnt + 5);

        }
        else
            state = 0;

}
void Package_ANO_422::DataPreProcessing(quint8 *data_buf, quint8 length)
{
    for(quint8 i = 0; i< length; i++)
    {
        DataPreProcessing(*(data_buf+i));
    }

}

void Package_ANO_422::DataProcessing(quint8 data_buf[], quint8 num)

{
    uint8_t sum = 0;
    for (uint8_t i = 0; i<(num - 1); i++)
        sum += *(data_buf + i);
    if (!(sum == *(data_buf + num - 1)))
    {
        //printf("sum error\r\n");
        return;		//判断sum
    }
    if (!(*(data_buf) == 0xAA && *(data_buf + 1) == 0xAA))
    {
        //printf("head error\r\n");
        return;		//判断帧头
    }
//    static int once = 5;
//    if(once)
//    {
//        once--;
//        qDebug()<<"     package ano 422  thread ID:"<<QThread::currentThreadId()<<'\n';
//    }

    if (*(data_buf + 2) == 0X01)//姿态等基本信息
    {
        this->plane_ROL = static_cast<float>(static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5))  / 100;//ROL*100
        this->plane_PIT = static_cast<float>(static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7))  / 100;//PIT*100
        this->plane_YAW = static_cast<float>(static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9))  / 100;//YAW*100

        //qDebug() << this->plane_ROL << this->plane_PIT << this->plane_YAW;
        //qDebug() << this->plane_ALT_USE;

        this->plane_ALT_USE = static_cast<float>(static_cast<qint32>(((*(data_buf + 10)) << 24) + //高度cm
                        ((*(data_buf + 11)) << 16) +
                        ((*(data_buf + 12)) << 8) +
                        (*(data_buf + 13)))) / 100;
        this->plane_FLY_MODEL = static_cast<quint8>(*(data_buf + 14));//飞行模式
        this->plane_ARMED = static_cast<quint8>(*(data_buf + 15));//0：加锁   1：解锁

        signalnew1( plane_ROL,  plane_PIT,  plane_YAW,  plane_ALT_USE,  plane_FLY_MODEL,  plane_ARMED);
    }
    else if (*(data_buf + 2) == 0X02)//传感器数据
    {
        this->plane_ACC_X =  static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_ACC_Y =  static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_ACC_Z =  static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);
        this->plane_GYRO_X = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_GYRO_Y = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_GYRO_Z = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);
        this->plane_MAG_X =  static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_MAG_Y =  static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_MAG_Z =  static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew2( plane_ACC_X,  plane_ACC_Y,  plane_ACC_Z,
                         plane_GYRO_X,  plane_GYRO_Y,  plane_GYRO_Z,
                         plane_MAG_X,  plane_MAG_Y,  plane_MAG_Z);
    }
    else if (*(data_buf + 2) == 0X03)//控制数据
    {
        this->remote_THR = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->remote_YAW = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->remote_ROL = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);
        this->remote_PIT = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->remote_AUX1 = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->remote_AUX2 = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);
        this->remote_AUX3 = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->remote_AUX4 = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->remote_AUX5 = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);
        this->remote_AUX6 = static_cast<qint16>(*(data_buf + 22) << 8) | *(data_buf + 23);

        signalnew3( remote_THR,  remote_YAW,  remote_ROL,  remote_PIT,
                         remote_AUX1,
                         remote_AUX2,
                         remote_AUX3,
                         remote_AUX4,
                         remote_AUX5,
                         remote_AUX6);
    }
    else if (*(data_buf + 2) == 0X04)//实时GPS信息
    {

    }
    else if (*(data_buf + 2) == 0X05)//电压电流
    {
        this->plane_Votage = static_cast<float>(static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5)) / 100;
        this->plane_Current = static_cast<float>(static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7)) /100;
        signalnew5(this->plane_Votage, this->plane_Current);
    }
    else if (*(data_buf + 2) == 0X06)//马达PWM（范围：0-1000）
    {
        this->plane_PWM_MOTO1 = static_cast<quint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PWM_MOTO2 = static_cast<quint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PWM_MOTO3 = static_cast<quint16>(*(data_buf + 8) << 8) | *(data_buf + 9);
        this->plane_PWM_MOTO4 = static_cast<quint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PWM_MOTO5 = static_cast<quint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PWM_MOTO6 = static_cast<quint16>(*(data_buf + 14) << 8) | *(data_buf + 15);
        this->plane_PWM_MOTO7 = static_cast<quint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PWM_MOTO8 = static_cast<quint16>(*(data_buf + 18) << 8) | *(data_buf + 19);

        signalnew6( plane_PWM_MOTO1,  plane_PWM_MOTO2,
                    plane_PWM_MOTO3,  plane_PWM_MOTO4,
                    plane_PWM_MOTO5,  plane_PWM_MOTO6,
                    plane_PWM_MOTO7,  plane_PWM_MOTO8);

        //qDebug() << plane_PWM_MOTO1 << plane_PWM_MOTO2 << plane_PWM_MOTO3 << plane_PWM_MOTO4;

    }
    else if (*(data_buf + 2) == 0X07)//板载气压计，附加测高传感器
    {
        this->plane_ALT_BRA = static_cast<float>(static_cast<qint32>(((*(data_buf + 4)) << 24) + //高度cm
                        ((*(data_buf + 5)) << 16) +
                        ((*(data_buf + 6)) << 8) +
                        (*(data_buf + 7)))) / 100;
        this->plane_ALT_ADDITION = static_cast<float>(static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9)) / 100;
        signalnew7(this->plane_ALT_BRA, this->plane_ALT_ADDITION);
    }
    else if (*(data_buf + 2) == 0X10)//pid1 pid2 pid3
    {
        this->plane_PID1_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID1_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID1_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID2_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID2_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID2_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID3_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID3_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID3_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew10( plane_PID1_P,  plane_PID1_I,  plane_PID1_D,
                     plane_PID2_P,  plane_PID2_I,  plane_PID2_D,
                     plane_PID3_P,  plane_PID3_I,  plane_PID3_D );
    }
    else if (*(data_buf + 2) == 0X11)//pid4 pid5 pid6
    {
        this->plane_PID4_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID4_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID4_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID5_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID5_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID5_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID6_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID6_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID6_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew11( plane_PID4_P,  plane_PID4_I,  plane_PID4_D,
                     plane_PID5_P,  plane_PID5_I,  plane_PID5_D,
                     plane_PID6_P,  plane_PID6_I,  plane_PID6_D );
    }
    else if (*(data_buf + 2) == 0X12)//pid7 pid8 pid9
    {
        this->plane_PID7_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID7_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID7_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID8_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID8_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID8_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID9_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID9_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID9_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew12( plane_PID7_P,  plane_PID7_I,  plane_PID7_D,
                     plane_PID8_P,  plane_PID8_I,  plane_PID8_D,
                     plane_PID9_P,  plane_PID9_I,  plane_PID9_D );
    }
    else if (*(data_buf + 2) == 0X13)//pid10 pid11 pid12
    {
        this->plane_PID10_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID10_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID10_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID11_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID11_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID11_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID12_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID12_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID12_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew13( plane_PID10_P,  plane_PID10_I,  plane_PID10_D,
                     plane_PID11_P,  plane_PID11_I,  plane_PID11_D,
                     plane_PID12_P,  plane_PID12_I,  plane_PID12_D );
    }
    else if (*(data_buf + 2) == 0X14)//pid13 pid14 pid15
    {
        this->plane_PID13_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID13_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID13_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID14_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID14_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID14_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID15_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID15_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID15_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew14( plane_PID13_P,  plane_PID13_I,  plane_PID13_D,
                     plane_PID14_P,  plane_PID14_I,  plane_PID14_D,
                     plane_PID15_P,  plane_PID15_I,  plane_PID15_D );
    }
    else if (*(data_buf + 2) == 0X15)//pid16 pid17 pid18
    {
        this->plane_PID16_P = static_cast<qint16>(*(data_buf + 4) << 8) | *(data_buf + 5);
        this->plane_PID16_I = static_cast<qint16>(*(data_buf + 6) << 8) | *(data_buf + 7);
        this->plane_PID16_D = static_cast<qint16>(*(data_buf + 8) << 8) | *(data_buf + 9);

        this->plane_PID17_P = static_cast<qint16>(*(data_buf + 10) << 8) | *(data_buf + 11);
        this->plane_PID17_I = static_cast<qint16>(*(data_buf + 12) << 8) | *(data_buf + 13);
        this->plane_PID17_D = static_cast<qint16>(*(data_buf + 14) << 8) | *(data_buf + 15);

        this->plane_PID18_P = static_cast<qint16>(*(data_buf + 16) << 8) | *(data_buf + 17);
        this->plane_PID18_I = static_cast<qint16>(*(data_buf + 18) << 8) | *(data_buf + 19);
        this->plane_PID18_D = static_cast<qint16>(*(data_buf + 20) << 8) | *(data_buf + 21);

        signalnew15( plane_PID16_P,  plane_PID16_I,  plane_PID16_D,
                     plane_PID17_P,  plane_PID17_I,  plane_PID17_D,
                     plane_PID18_P,  plane_PID18_I,  plane_PID18_D );
    }
}


void Package_ANO_422::DataPacking(quint8 function, quint8 CMD)
{
    static quint8 DT_TxBuffer[256];
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    if(function == 0x01)
    {

    }
    else if(function == 0x02)
    {
        DT_TxBuffer[2] = 0x02;
        DT_TxBuffer[3] = 0x01;//数据长度
        DT_TxBuffer[4] = CMD;
        DT_TxBuffer[5] = 0x5D;


    }

    signal_send_new1(DT_TxBuffer);

}


