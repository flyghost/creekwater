#ifndef FRAMEBACKSTAGE_H
#define FRAMEBACKSTAGE_H

#include <QWidget>
#include "ui_framemain.h"

class FrameBackstage : public QWidget
{
    Q_OBJECT
public:
    FrameBackstage(Ui_FrameMain *m_ui) ;
//    ~FrameBackstage();

private:
    Ui_FrameMain *ui;

    QList<int> pixCharList;
    QList<QToolButton *> btnList;

    enum {
        SERIAL = 0,
        TERMINAL, TCPSERVER, TCPCLIENT, UDP, USBHID
    };

    void initLeftButton();

private slots:
    void leftBtnListClick();//左列按钮槽

};















#endif // FRAMEBOTTOM_H
