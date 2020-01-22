#ifndef FRAMETOP_H
#define FRAMETOP_H

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


//namespace Ui {
//class FrameTop;
//}


class FrameTop : public QWidget
{
    Q_OBJECT
public:
    explicit FrameTop(QWidget *parent = nullptr);
    ~FrameTop();

private:
    Ui::FrameMain *ui;

private:
    QList<int> pixCharMain;
    QList<QToolButton *> btnsMain;
    Bridge *bridge;


private:
    enum {
        MAIN = 0,
        SETTING, DATA, HELP, TEST
    };

private:
    void initForm();


private slots:
    void buttonClick();
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

};

#endif // FRAMETOP_H
