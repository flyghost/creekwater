#ifndef FRAMESERIAL_H
#define FRAMESERIAL_H



#include <QWidget>


#include <QProcess>

#include "ui_framemain.h"



class FrameTerminal : public QWidget
{
    Q_OBJECT
public:
    explicit FrameTerminal(Ui_FrameMain *m_ui) ;
    ~FrameTerminal();

private:
    Ui_FrameMain *ui;
    QProcess *cmd;

private slots:
    void on_readoutput();
    void on_readerror();
    void on_pushButton_clicked();
};















#endif // FRAMEBOTTOM_H
