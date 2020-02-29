#include "bin_handle.h"
#include <QDebug>

Bin_Handle::Bin_Handle(QextSerialPort *m_com,Ui_FrameMain *m_ui)
{
    com = m_com;
    ui = m_ui;
}


qint32 Bin_Handle::str_to_hex(QString str)
{
    QByteArray temp1 = str.toLatin1().toHex();
    return  temp1.toInt(nullptr,16);
}
