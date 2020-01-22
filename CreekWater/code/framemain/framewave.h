#ifndef FRAMEWAVE_H
#define FRAMEWAVE_H




#include "bridge.h"
#include "frmcomtool.h"
#include "maininterface.h"
#include "settinginterface.h"


#include <QWidget>

class FrameWave : public QWidget
{
    Q_OBJECT

public:
    explicit FrameWave(Ui_FrameMain *mui, Bridge *m_bridge);

private:
    Ui_FrameMain *ui;
    Bridge *bridge;


};
















#endif // FRAMEBOTTOM_H
