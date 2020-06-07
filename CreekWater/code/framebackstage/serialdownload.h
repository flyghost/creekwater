#ifndef SERIALDOWNLOAD_H
#define SERIALDOWNLOAD_H

#include <QByteArray>
#include <qextserialport.h>
#include "ui_framemain.h"
#include "buttonedit.h"



class SerialDownload: public QWidget
{
    Q_OBJECT
public:
    SerialDownload(QextSerialPort *m_com,Ui_FrameMain *m_ui);
private:
     quint32 TRS_STUB_BLOCK = 1024;
     quint32 TRS_CMD_BLOCK = 4096;

    QextSerialPort *com;
    Ui_FrameMain *ui;
    ButtonEdit *buttonEdit1;
    ButtonEdit *buttonEdit2;
    ButtonEdit *buttonEdit3;
    ButtonEdit *buttonEdit4;

    void buttonEditInit();

    quint8 retries;
    QByteArray STUB_CODE;

    void write(QByteArray bytes);
    QByteArray read(qint64 length);
    quint32 crc32(quint32 crc, const void *buf, size_t size);
    bool command(quint8 cmd_type, quint8 cmd_subtype=0, quint8 data_content[]=nullptr, quint32 data_length=0);
    QString get_path();

    bool sync_bootrom();    // Perform a connection to bootrom in uart boot mode
//    char receive_response();
    bool load_stub();

private slots:
    void downloadButtonClicked();
    void path_lineEdit1_Clicked();
    void path_lineEdit2_Clicked();
    void path_lineEdit3_Clicked();
    void path_lineEdit4_Clicked();

private:
    QString TRS_ALLINONE = "oneb";


//    QString bin_path1;
//    QString bin_path2;
//    QString bin_path3;
//    QString bin_path4;

//    qint32 bin_addr1;
//    qint32 bin_addr2;
//    qint32 bin_addr3;
//    qint32 bin_addr4;

//    QString bin_path;
//    qint32 bin_addr;
//    QByteArray image;
//    qint32 image_length;
//    qint32 type;


private:
    qint32 str_to_hex(QString str);
    bool bin_handle_unpack(QString path,
                           qint32 *type,
                           qint32 *bin_addr,
                           qint32 *image_length,
                           QByteArray *image);
    bool bin_handle_read(QString path,
                         QString addr,
                         qint32 *type,
                         qint32 *bin_addr,
                         qint32 *image_length,
                         QByteArray *image);


};

//class
//{
//public:
//    SerialDownload(QextSerialPort *com);


//private:

//    QextSerialPort *m_com;

//    qint64 TRS_SYNC        = 0x73796E63;
//    qint64 TRS_DEFAULT_ROM_BAUD = 57600;
//    quint8 SOF = 0xA5 ; // start of a frame

//    // message type define
//    quint8 M_SYNC   = 0x00;
//    quint8 M_CFG    = 0x01;
//    quint8 M_WRITE  = 0x02;
//    quint8 M_READ   = 0x03;
//    quint8 M_ERASE  = 0x04;
//    quint8 M_REBOOT = 0x05;

//    // Mesage_subtype define
//    quint8 M_SUB_SYNC      =  0x00;
//    quint8 M_SUB_BAUD      =  0x01;
//    quint8 M_SUB_FLASH     =  0x02;
//    quint8 M_SUB_FLASH_ID  =  0x03;
//    quint8 M_SUB_MEM       =  0x04;
//    quint8 M_SUB_REG       =  0x05;
//    quint8 M_SUB_VERSION   =  0x06;

//    // response message
//    quint8 ACK_OK  = 0x00;
//    quint8 ACK_ERR = 0x01;

//    qint32 TRS_STUB_BLOCK = 1024;
//    qint32 TRS_CMD_BLOCK = 4096;

//    struct
//    {
//        unsigned char sof;
//        unsigned char cmd_type;
//        unsigned int len;
//        unsigned char cmd_subtype;
//    }hdr_checksum_struct;

//private:
//    void write(QByteArray packet);
//    QByteArray read();
//    void send_command(unsigned char cmd_type, unsigned char cmd_subtype, QString data_content);
//};

#endif // SERIALDOWNLOAD_H
