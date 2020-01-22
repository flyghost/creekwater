#ifndef SETTINGINTERFACE_H
#define SETTINGINTERFACE_H

#include <QWidget>

#include "ui_framemain.h"
#include "bridge.h"




class SettingInterface : public QWidget
{
	Q_OBJECT

public:
    SettingInterface(Ui::FrameMain *m_ui, Bridge *m_bridge) ;


private:
    Ui::FrameMain *ui;
    Bridge *bridge;
    QString connect_mode;//连接模式按钮组选择的哪个按钮


private:
    void check_device_init();
    void initButtonGroup();

private slots:
    void check_deviceClick(int buttonId);
    void on_seleckConnect_clicked(QAbstractButton *btn);


};

#endif
