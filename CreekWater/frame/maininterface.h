#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>

#include "ui_framemain.h"
#include "bridge.h"




class MainInterface : public QWidget
{
	Q_OBJECT

public:
    MainInterface(Ui::FrameMain *m_ui, Bridge *m_bridge) ;


private:
    Ui::FrameMain *ui;
    Bridge *bridge;


private:
    void mainPlane_init();

private slots:
    void uiUpdate();//界面更新定时器


};

#endif
