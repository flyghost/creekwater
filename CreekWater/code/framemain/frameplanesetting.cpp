#include "frameplanesetting.h"

#include <QDebug>

#include "package_ano_422.h"
#include "framebottom.h"
#include "qextserialport.h"

FramePlaneSetting::FramePlaneSetting(Ui_FrameMain *mui)
{
    ui = mui;

    //读取写入PID按钮信号槽
    connect(ui->getpidButton,SIGNAL(clicked()),this,SLOT(on_getpidButton_clicked()));
    connect(ui->writepidButton,SIGNAL(clicked()),this,SLOT(on_writepidButton_clicked()));
    //校准按钮信号槽
    connect(ui->gyroCalibrateButton,SIGNAL(clicked()),this,SLOT(on_gyroCalibrateButton_clicked()));
    connect(ui->accCalibrateButton,SIGNAL(clicked()),this,SLOT(on_accCalibrateButton_clicked()));
    connect(ui->magCalibrateButton,SIGNAL(clicked()),this,SLOT(on_magCalibrateButton_clicked()));
    connect(ui->baroCalibrateButton,SIGNAL(clicked()),this,SLOT(on_baroCalibrateButton_clicked()));
    //六面校准按钮信号槽
    connect(ui->sixCalibrateButton,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_clicked()));
    connect(ui->sixCalibrateButton_2,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_2_clicked()));
    connect(ui->sixCalibrateButton_3,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_3_clicked()));
    connect(ui->sixCalibrateButton_4,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_4_clicked()));
    connect(ui->sixCalibrateButton_5,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_5_clicked()));
    connect(ui->sixCalibrateButton_6,SIGNAL(clicked()),this,SLOT(on_sixCalibrateButton_6_clicked()));



    connect(this,SIGNAL(signalGetPidButtonClicked()),package_ano_422,SLOT(DataPacking(quint8, quint8)));

    connect(package_ano_422,SIGNAL(signalnew10(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew10(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));
    connect(package_ano_422,SIGNAL(signalnew11(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew11(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));
    connect(package_ano_422,SIGNAL(signalnew12(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew12(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));
    connect(package_ano_422,SIGNAL(signalnew13(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew13(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));
    connect(package_ano_422,SIGNAL(signalnew14(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew14(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));
    connect(package_ano_422,SIGNAL(signalnew15(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)),
            this,SLOT(slotnew15(qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16,qint16)));

}

void FramePlaneSetting::on_writepidButton_clicked()
{
    QByteArray DT_TxBuffer;
    uint8_t sum = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID 1,2,3
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x10;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID1_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID2_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID3_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID 4,5,6
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x11;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID4_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID5_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID6_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID7,8,9
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x12;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID7_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID8_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID9_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID 10,11,12
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x13;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID10_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID11_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID12_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID 13,14,15
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x14;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID13_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID14_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID15_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// PID 16,17,18
    /////////////////////////////////////////////////////////////////////////////////////////////
    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x15;
    DT_TxBuffer[3] = 0x12;//数据长度

    DT_TxBuffer[4] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[5] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[6] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[7] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[8] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[9] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID16_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[10] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[11] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[12] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[13] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[14] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[15] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID17_D_lineEdit->text().toInt())) ;

    DT_TxBuffer[16] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_P_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[17] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_P_lineEdit->text().toInt())) ;
    DT_TxBuffer[18] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_I_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[19] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_I_lineEdit->text().toInt())) ;
    DT_TxBuffer[20] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_D_lineEdit->text().toInt()) >> 8) ;
    DT_TxBuffer[21] = static_cast<qint8>(static_cast<qint16>(ui->plansettingPID18_D_lineEdit->text().toInt())) ;


    sum = 0;
    for (uint8_t i = 0; i<22; i++)
        sum += DT_TxBuffer[i];

    DT_TxBuffer[22] = sum;

    com->write(DT_TxBuffer,23);



}

void FramePlaneSetting::on_getpidButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x02;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x01;
    DT_TxBuffer[5] = 0x5D;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::on_gyroCalibrateButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x02;
    DT_TxBuffer[5] = 0x5D;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::on_accCalibrateButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x01;
    DT_TxBuffer[5] = 0x5C;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::on_magCalibrateButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x04;
    DT_TxBuffer[5] = 0x5F;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::on_baroCalibrateButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x05;
    DT_TxBuffer[5] = 0x60;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::on_sixCalibrateButton_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x21;
    DT_TxBuffer[5] = 0x7C;

    com->write(DT_TxBuffer,6);
}
void FramePlaneSetting::on_sixCalibrateButton_2_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x22;
    DT_TxBuffer[5] = 0x7D;

    com->write(DT_TxBuffer,6);
}
void FramePlaneSetting::on_sixCalibrateButton_3_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x23;
    DT_TxBuffer[5] = 0x7E;

    com->write(DT_TxBuffer,6);
}
void FramePlaneSetting::on_sixCalibrateButton_4_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x24;
    DT_TxBuffer[5] = 0x7F;

    com->write(DT_TxBuffer,6);
}
void FramePlaneSetting::on_sixCalibrateButton_5_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x25;
    DT_TxBuffer[5] = 0x80;

    com->write(DT_TxBuffer,6);
}
void FramePlaneSetting::on_sixCalibrateButton_6_clicked()
{
    QByteArray DT_TxBuffer;

    DT_TxBuffer[0] = 0xAA;
    DT_TxBuffer[1] = 0xAF;

    DT_TxBuffer[2] = 0x01;
    DT_TxBuffer[3] = 0x01;//数据长度
    DT_TxBuffer[4] = 0x26;
    DT_TxBuffer[5] = 0x81;

    com->write(DT_TxBuffer,6);
}

void FramePlaneSetting::slotnew10(qint16 plane_PID1_P, qint16 plane_PID1_I, qint16 plane_PID1_D,
                 qint16 plane_PID2_P, qint16 plane_PID2_I, qint16 plane_PID2_D,
                 qint16 plane_PID3_P, qint16 plane_PID3_I, qint16 plane_PID3_D )
{
    this->plane_PID1_P =plane_PID1_P;
    this->plane_PID1_I =plane_PID1_I;
    this->plane_PID1_D =plane_PID1_D;

    this->plane_PID2_P =plane_PID2_P;
    this->plane_PID2_I =plane_PID2_I;
    this->plane_PID2_D =plane_PID2_D;

    this->plane_PID3_P =plane_PID3_P;
    this->plane_PID3_I =plane_PID3_I;
    this->plane_PID3_D =plane_PID3_D;

    ui->plansettingPID1_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID1_P)));
    ui->plansettingPID1_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID1_I)));
    ui->plansettingPID1_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID1_D)));

    ui->plansettingPID2_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID2_P)));
    ui->plansettingPID2_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID2_I)));
    ui->plansettingPID2_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID2_D)));

    ui->plansettingPID3_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID3_P)));
    ui->plansettingPID3_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID3_I)));
    ui->plansettingPID3_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID3_D)));

}
void FramePlaneSetting::slotnew11(qint16 plane_PID4_P, qint16 plane_PID4_I, qint16 plane_PID4_D,
                 qint16 plane_PID5_P, qint16 plane_PID5_I, qint16 plane_PID5_D,
                 qint16 plane_PID6_P, qint16 plane_PID6_I, qint16 plane_PID6_D )
{
    this->plane_PID4_P =plane_PID4_P;
    this->plane_PID4_I =plane_PID4_I;
    this->plane_PID4_D =plane_PID4_D;

    this->plane_PID5_P =plane_PID5_P;
    this->plane_PID5_I =plane_PID5_I;
    this->plane_PID5_D =plane_PID5_D;

    this->plane_PID6_P =plane_PID6_P;
    this->plane_PID6_I =plane_PID6_I;
    this->plane_PID6_D =plane_PID6_D;

    ui->plansettingPID4_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID4_P)));
    ui->plansettingPID4_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID4_I)));
    ui->plansettingPID4_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID4_D)));

    ui->plansettingPID5_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID5_P)));
    ui->plansettingPID5_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID5_I)));
    ui->plansettingPID5_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID5_D)));

    ui->plansettingPID6_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID6_P)));
    ui->plansettingPID6_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID6_I)));
    ui->plansettingPID6_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID6_D)));
}
void FramePlaneSetting::slotnew12(qint16 plane_PID7_P, qint16 plane_PID7_I, qint16 plane_PID7_D,
                 qint16 plane_PID8_P, qint16 plane_PID8_I, qint16 plane_PID8_D,
                 qint16 plane_PID9_P, qint16 plane_PID9_I, qint16 plane_PID9_D )
{
    this->plane_PID7_P =plane_PID7_P;
    this->plane_PID7_I =plane_PID7_I;
    this->plane_PID7_D =plane_PID7_D;

    this->plane_PID8_P =plane_PID8_P;
    this->plane_PID8_I =plane_PID8_I;
    this->plane_PID8_D =plane_PID8_D;

    this->plane_PID9_P =plane_PID9_P;
    this->plane_PID9_I =plane_PID9_I;
    this->plane_PID9_D =plane_PID9_D;

    ui->plansettingPID7_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID7_P)));
    ui->plansettingPID7_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID7_I)));
    ui->plansettingPID7_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID7_D)));

    ui->plansettingPID8_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID8_P)));
    ui->plansettingPID8_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID8_I)));
    ui->plansettingPID8_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID8_D)));

    ui->plansettingPID9_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID9_P)));
    ui->plansettingPID9_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID9_I)));
    ui->plansettingPID9_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID9_D)));
}
void FramePlaneSetting::slotnew13(qint16 plane_PID10_P, qint16 plane_PID10_I, qint16 plane_PID10_D,
                 qint16 plane_PID11_P, qint16 plane_PID11_I, qint16 plane_PID11_D,
                 qint16 plane_PID12_P, qint16 plane_PID12_I, qint16 plane_PID12_D )
{
    this->plane_PID10_P =plane_PID10_P;
    this->plane_PID10_I =plane_PID10_I;
    this->plane_PID10_D =plane_PID10_D;

    this->plane_PID11_P =plane_PID11_P;
    this->plane_PID11_I =plane_PID11_I;
    this->plane_PID11_D =plane_PID11_D;

    this->plane_PID12_P =plane_PID12_P;
    this->plane_PID12_I =plane_PID12_I;
    this->plane_PID12_D =plane_PID12_D;

    ui->plansettingPID10_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID10_P)));
    ui->plansettingPID10_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID10_I)));
    ui->plansettingPID10_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID10_D)));

    ui->plansettingPID11_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID11_P)));
    ui->plansettingPID11_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID11_I)));
    ui->plansettingPID11_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID11_D)));

    ui->plansettingPID12_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID12_P)));
    ui->plansettingPID12_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID12_I)));
    ui->plansettingPID12_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID12_D)));
}
void FramePlaneSetting::slotnew14(qint16 plane_PID13_P, qint16 plane_PID13_I, qint16 plane_PID13_D,
                 qint16 plane_PID14_P, qint16 plane_PID14_I, qint16 plane_PID14_D,
                 qint16 plane_PID15_P, qint16 plane_PID15_I, qint16 plane_PID15_D )
{
    this->plane_PID13_P =plane_PID13_P;
    this->plane_PID13_I =plane_PID13_I;
    this->plane_PID13_D =plane_PID13_D;

    this->plane_PID14_P =plane_PID14_P;
    this->plane_PID14_I =plane_PID14_I;
    this->plane_PID14_D =plane_PID14_D;

    this->plane_PID15_P =plane_PID15_P;
    this->plane_PID15_I =plane_PID15_I;
    this->plane_PID15_D =plane_PID15_D;

    ui->plansettingPID13_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID13_P)));
    ui->plansettingPID13_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID13_I)));
    ui->plansettingPID13_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID13_D)));

    ui->plansettingPID14_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID14_P)));
    ui->plansettingPID14_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID14_I)));
    ui->plansettingPID14_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID14_D)));

    ui->plansettingPID15_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID15_P)));
    ui->plansettingPID15_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID15_I)));
    ui->plansettingPID15_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID15_D)));
}
void FramePlaneSetting::slotnew15(qint16 plane_PID16_P, qint16 plane_PID16_I, qint16 plane_PID16_D,
                 qint16 plane_PID17_P, qint16 plane_PID17_I, qint16 plane_PID17_D,
                 qint16 plane_PID18_P, qint16 plane_PID18_I, qint16 plane_PID18_D )
{
    this->plane_PID16_P =plane_PID16_P;
    this->plane_PID16_I =plane_PID16_I;
    this->plane_PID16_D =plane_PID16_D;

    this->plane_PID17_P =plane_PID17_P;
    this->plane_PID17_I =plane_PID17_I;
    this->plane_PID17_D =plane_PID17_D;

    this->plane_PID18_P =plane_PID18_P;
    this->plane_PID18_I =plane_PID18_I;
    this->plane_PID18_D =plane_PID18_D;

    ui->plansettingPID16_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID16_P)));
    ui->plansettingPID16_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID16_I)));
    ui->plansettingPID16_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID16_D)));

    ui->plansettingPID17_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID17_P)));
    ui->plansettingPID17_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID17_I)));
    ui->plansettingPID17_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID17_D)));

    ui->plansettingPID18_P_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID18_P)));
    ui->plansettingPID18_I_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID18_I)));
    ui->plansettingPID18_D_lineEdit->setText(tr("%1").arg(static_cast<double>(this->plane_PID18_D)));
}







