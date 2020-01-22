#ifndef FRAMECONNECT_H
#define FRAMECONNECT_H




#include "bridge.h"



class FrameConnect : public QWidget
{
    Q_OBJECT

public:
    explicit FrameConnect(Ui_FrameMain *mui, Bridge *m_bridge);

private:
    Ui_FrameMain *ui;
    Bridge *bridge;
    QString connect_mode;//连接模式按钮组选择的哪个按钮

    QList<int> pixCharConfig;
    QList<QToolButton *> btnsConfig;


private:
    void check_device_init();
    void initButtonGroup();
    void initLeftConfig();

private slots:
    void check_deviceClick(int buttonId);
    void on_seleckConnect_clicked(QAbstractButton *btn);
    void leftConfigClick();

};
















#endif // FRAMEBOTTOM_H
