#ifndef FRAMEMAIN_H
#define FRAMEMAIN_H




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


class FrameMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrameMain(Ui_FrameMain *mui, Bridge *m_bridge);

private:
    Ui_FrameMain *ui;
    Bridge *bridge;

    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;
private:

    enum {
        VIDEO = 0,
        MAP, DEVICE
    };

private:
    void initLeftMain();
    void mainPlane_init();


private slots:
    void leftMainClick();
    void uiUpdate();//界面更新定时器

};
















#endif // FRAMEBOTTOM_H
