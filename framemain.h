#ifndef FRAMEMAIN_H
#define FRAMEMAIN_H

#include <QWidget>
#include "bridge.h"
#include "frmcomtool.h"
#include "maininterface.h"
#include "settinginterface.h"

#include <QButtonGroup>
#include <QMessageBox>

#include <QList>
#include <QToolButton>
#include <QDialog>
#include <QScrollBar>

#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QFileDialog>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <QDateTime>


using namespace std;


namespace Ui {
class FrameMain;
}

class FrameMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrameMain(QWidget *parent = nullptr);
    ~FrameMain();

private:
    Ui::FrameMain *ui;
    Bridge *bridge;
    frmComTool *comFrame;//串口调试界面
    MainInterface *maininterface;//主界面
    SettingInterface *settinginterface;//设置界面

private:
    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;

    QList<int> pixCharConfig;
    QList<QToolButton *> btnsConfig;

    QList<int> pixCharTest;
    QList<QToolButton *> btnsTest;

    QList<int> pixCharFind;
    QList<QToolButton *> btnsFind;

    QList<int> pixCharBottom;
    QList<QToolButton *> btnsBottom;


private:
    enum {
        MAIN = 0,
        SETTING, DATA, HELP, TEST
    };
    enum {
        VIDEO = 0,
        MAP, DEVICE
    };
    enum {
        SERIAL = 0,
        TCPSERVER, TCPCLIENT, UDP, DEVICESETTING, OTHERS
    };

private:

    void initForm();
    void initLeftMain();
    void initLeftConfig();
    void initLeftTest();
    void config_bottom_button_init();
    //void check_device_init();
//    void mainPlane_init();


private slots:


    void buttonClick();
    void leftMainClick();
    void leftConfigClick();
    void leftTestClick();
    //void check_deviceClick(int buttonId);
//    void uiUpdate();//界面更新定时器




private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

};

#endif // FRAMEMAIN_H
