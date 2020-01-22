#ifndef PACKAGE_ANO_422_H
#define PACKAGE_ANO_422_H


#include <QObject>
#include <QThread>


class Package_ANO_422 : public QObject
{
    Q_OBJECT

public:
    Package_ANO_422();
    ~Package_ANO_422();

private:
    QThread thread;
    void print_thread_id();
    void DataProcessing(quint8 *data_buf, quint8 num);

public slots:
    //接收到消息调用槽函数进行解析
    void DataPreProcessing(quint8 data);
    void DataPreProcessing(quint8 *data_buf, quint8 length);
    //调用槽函数打包，打包完发送信号
    void DataPacking(quint8 function, quint8 CMD);
signals:
    //解析接受的消息发出信号
    void signalnew1(float plane_ROL, float plane_PIT, float plane_YAW,
                    float plane_ALT_USE, quint8 plane_FLY_MODEL, quint8 plane_ARMED);
    void signalnew2(qint16 plane_ACC_X, qint16 plane_ACC_Y, qint16 plane_ACC_Z,
                    qint16 plane_GYRO_X, qint16 plane_GYRO_Y, qint16 plane_GYRO_Z,
                    qint16 plane_MAG_X, qint16 plane_MAG_Y, qint16 plane_MAG_Z);
    void signalnew3(qint16 remote_THR, qint16 remote_YAW, qint16 remote_ROL, qint16 remote_PIT,
                    qint16 remote_AUX1,
                    qint16 remote_AUX2,
                    qint16 remote_AUX3,
                    qint16 remote_AUX4,
                    qint16 remote_AUX5,
                    qint16 remote_AUX6);
    void signalnew5(float plane_Votage, float plane_Current);
    void signalnew6(quint16 plane_PWM_MOTO1, quint16 plane_PWM_MOTO2,
                    quint16 plane_PWM_MOTO3, quint16 plane_PWM_MOTO4,
                    quint16 plane_PWM_MOTO5, quint16 plane_PWM_MOTO6,
                    quint16 plane_PWM_MOTO7, quint16 plane_PWM_MOTO8);
    void signalnew7(float plane_ALT_BRA, float plane_ALT_ADDITION);
    void signalnew10(qint16 plane_PID1_P, qint16 plane_PID1_I, qint16 plane_PID1_D,
                     qint16 plane_PID2_P, qint16 plane_PID2_I, qint16 plane_PID2_D,
                     qint16 plane_PID3_P, qint16 plane_PID3_I, qint16 plane_PID3_D );
    void signalnew11(qint16 plane_PID4_P, qint16 plane_PID4_I, qint16 plane_PID4_D,
                     qint16 plane_PID5_P, qint16 plane_PID5_I, qint16 plane_PID5_D,
                     qint16 plane_PID6_P, qint16 plane_PID6_I, qint16 plane_PID6_D );
    void signalnew12(qint16 plane_PID7_P, qint16 plane_PID7_I, qint16 plane_PID7_D,
                     qint16 plane_PID8_P, qint16 plane_PID8_I, qint16 plane_PID8_D,
                     qint16 plane_PID9_P, qint16 plane_PID9_I, qint16 plane_PID9_D );
    void signalnew13(qint16 plane_PID10_P, qint16 plane_PID10_I, qint16 plane_PID10_D,
                     qint16 plane_PID11_P, qint16 plane_PID11_I, qint16 plane_PID11_D,
                     qint16 plane_PID12_P, qint16 plane_PID12_I, qint16 plane_PID12_D );
    void signalnew14(qint16 plane_PID13_P, qint16 plane_PID13_I, qint16 plane_PID13_D,
                     qint16 plane_PID14_P, qint16 plane_PID14_I, qint16 plane_PID14_D,
                     qint16 plane_PID15_P, qint16 plane_PID15_I, qint16 plane_PID15_D );
    void signalnew15(qint16 plane_PID16_P, qint16 plane_PID16_I, qint16 plane_PID16_D,
                     qint16 plane_PID17_P, qint16 plane_PID17_I, qint16 plane_PID17_D,
                     qint16 plane_PID18_P, qint16 plane_PID18_I, qint16 plane_PID18_D );

signals:
    void signal_send_new1(quint8 groundstation_CMD[]);


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

    qint16 plane_PID1_P = 0;
    qint16 plane_PID1_I = 0;
    qint16 plane_PID1_D = 0;
    qint16 plane_PID2_P = 0;
    qint16 plane_PID2_I = 0;
    qint16 plane_PID2_D = 0;
    qint16 plane_PID3_P = 0;
    qint16 plane_PID3_I = 0;
    qint16 plane_PID3_D = 0;
    qint16 plane_PID4_P = 0;
    qint16 plane_PID4_I = 0;
    qint16 plane_PID4_D = 0;
    qint16 plane_PID5_P = 0;
    qint16 plane_PID5_I = 0;
    qint16 plane_PID5_D = 0;
    qint16 plane_PID6_P = 0;
    qint16 plane_PID6_I = 0;
    qint16 plane_PID6_D = 0;
    qint16 plane_PID7_P = 0;
    qint16 plane_PID7_I = 0;
    qint16 plane_PID7_D = 0;
    qint16 plane_PID8_P = 0;
    qint16 plane_PID8_I = 0;
    qint16 plane_PID8_D = 0;
    qint16 plane_PID9_P = 0;
    qint16 plane_PID9_I = 0;
    qint16 plane_PID9_D = 0;
    qint16 plane_PID10_P = 0;
    qint16 plane_PID10_I = 0;
    qint16 plane_PID10_D = 0;
    qint16 plane_PID11_P = 0;
    qint16 plane_PID11_I = 0;
    qint16 plane_PID11_D = 0;
    qint16 plane_PID12_P = 0;
    qint16 plane_PID12_I = 0;
    qint16 plane_PID12_D = 0;
    qint16 plane_PID13_P = 0;
    qint16 plane_PID13_I = 0;
    qint16 plane_PID13_D = 0;
    qint16 plane_PID14_P = 0;
    qint16 plane_PID14_I = 0;
    qint16 plane_PID14_D = 0;
    qint16 plane_PID15_P = 0;
    qint16 plane_PID15_I = 0;
    qint16 plane_PID15_D = 0;
    qint16 plane_PID16_P = 0;
    qint16 plane_PID16_I = 0;
    qint16 plane_PID16_D = 0;
    qint16 plane_PID17_P = 0;
    qint16 plane_PID17_I = 0;
    qint16 plane_PID17_D = 0;
    qint16 plane_PID18_P = 0;
    qint16 plane_PID18_I = 0;
    qint16 plane_PID18_D = 0;

};


extern Package_ANO_422 *package_ano_422;



#endif // PACKAGE_ANO_422_H
