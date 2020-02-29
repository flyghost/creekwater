#ifndef BIN_HANDLE_H
#define BIN_HANDLE_H

#include <QByteArray>
#include <qextserialport.h>
#include "ui_framemain.h"

class Bin_Handle
{
public:
    Bin_Handle(QextSerialPort *m_com,Ui_FrameMain *m_ui);

private:
    QextSerialPort *com;
    Ui_FrameMain *ui;

    QString TRS_ALLINONE = "oneb";

    qint32 TRS_UBOOT_ADDR   = 0x0000;
    qint32 TRS_APP_ADDR     = 0x4000;
    qint32 TRS_NV_ADDR      = 0x8000;

    qint32 TRS_FRM_TYPE_UBOOT = 0x00000001;
    qint32 TRS_FRM_TYPE_NV    = 0x00000002;
    qint32 TRS_FRM_TYPE_APP   = 0x00000003;

    QString bin_path1;
    QString bin_path2;
    QString bin_path3;
    QString bin_path4;

    QString bin_addr1;
    QString bin_addr2;
    QString bin_addr3;
    QString bin_addr4;


private:
    qint32 str_to_hex(QString str);
};

#endif // BIN_HANDLE_H
