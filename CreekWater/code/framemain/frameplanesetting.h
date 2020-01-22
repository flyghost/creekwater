#ifndef FRAMEPLANESETTING_H
#define FRAMEPLANESETTING_H





#include <QWidget>
#include "ui_framemain.h"

class FramePlaneSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FramePlaneSetting(Ui_FrameMain *mui);

private:
    Ui_FrameMain *ui;

public slots:
    void on_getpidButton_clicked();
    void on_writepidButton_clicked();
    void on_gyroCalibrateButton_clicked();
    void on_accCalibrateButton_clicked();
    void on_magCalibrateButton_clicked();
    void on_baroCalibrateButton_clicked();
    void on_sixCalibrateButton_clicked();
    void on_sixCalibrateButton_2_clicked();
    void on_sixCalibrateButton_3_clicked();
    void on_sixCalibrateButton_4_clicked();
    void on_sixCalibrateButton_5_clicked();
    void on_sixCalibrateButton_6_clicked();

    void slotnew10(qint16 plane_PID1_P, qint16 plane_PID1_I, qint16 plane_PID1_D,
                     qint16 plane_PID2_P, qint16 plane_PID2_I, qint16 plane_PID2_D,
                     qint16 plane_PID3_P, qint16 plane_PID3_I, qint16 plane_PID3_D );
    void slotnew11(qint16 plane_PID4_P, qint16 plane_PID4_I, qint16 plane_PID4_D,
                     qint16 plane_PID5_P, qint16 plane_PID5_I, qint16 plane_PID5_D,
                     qint16 plane_PID6_P, qint16 plane_PID6_I, qint16 plane_PID6_D );
    void slotnew12(qint16 plane_PID7_P, qint16 plane_PID7_I, qint16 plane_PID7_D,
                     qint16 plane_PID8_P, qint16 plane_PID8_I, qint16 plane_PID8_D,
                     qint16 plane_PID9_P, qint16 plane_PID9_I, qint16 plane_PID9_D );
    void slotnew13(qint16 plane_PID10_P, qint16 plane_PID10_I, qint16 plane_PID10_D,
                     qint16 plane_PID11_P, qint16 plane_PID11_I, qint16 plane_PID11_D,
                     qint16 plane_PID12_P, qint16 plane_PID12_I, qint16 plane_PID12_D );
    void slotnew14(qint16 plane_PID13_P, qint16 plane_PID13_I, qint16 plane_PID13_D,
                     qint16 plane_PID14_P, qint16 plane_PID14_I, qint16 plane_PID14_D,
                     qint16 plane_PID15_P, qint16 plane_PID15_I, qint16 plane_PID15_D );
    void slotnew15(qint16 plane_PID16_P, qint16 plane_PID16_I, qint16 plane_PID16_D,
                     qint16 plane_PID17_P, qint16 plane_PID17_I, qint16 plane_PID17_D,
                     qint16 plane_PID18_P, qint16 plane_PID18_I, qint16 plane_PID18_D );

signals:
    void signalGetPidButtonClicked(quint8 function, quint8 CMD);

private:
    qint16 plane_PID1_P = 0;
    qint16 plane_PID1_I = 0;
    qint16 plane_PID1_D = 0;
    qint16 plane_PID2_P = 0;
    qint16 plane_PID2_I = 0;
    qint16 plane_PID2_D = 0;
    qint16 plane_PID3_P = 0;
    qint16 plane_PID3_I = 0;
    qint16 plane_PID3_D = 0;
    qint16 plane_PID4_P = 0;
    qint16 plane_PID4_I = 0;
    qint16 plane_PID4_D = 0;
    qint16 plane_PID5_P = 0;
    qint16 plane_PID5_I = 0;
    qint16 plane_PID5_D = 0;
    qint16 plane_PID6_P = 0;
    qint16 plane_PID6_I = 0;
    qint16 plane_PID6_D = 0;
    qint16 plane_PID7_P = 0;
    qint16 plane_PID7_I = 0;
    qint16 plane_PID7_D = 0;
    qint16 plane_PID8_P = 0;
    qint16 plane_PID8_I = 0;
    qint16 plane_PID8_D = 0;
    qint16 plane_PID9_P = 0;
    qint16 plane_PID9_I = 0;
    qint16 plane_PID9_D = 0;
    qint16 plane_PID10_P = 0;
    qint16 plane_PID10_I = 0;
    qint16 plane_PID10_D = 0;
    qint16 plane_PID11_P = 0;
    qint16 plane_PID11_I = 0;
    qint16 plane_PID11_D = 0;
    qint16 plane_PID12_P = 0;
    qint16 plane_PID12_I = 0;
    qint16 plane_PID12_D = 0;
    qint16 plane_PID13_P = 0;
    qint16 plane_PID13_I = 0;
    qint16 plane_PID13_D = 0;
    qint16 plane_PID14_P = 0;
    qint16 plane_PID14_I = 0;
    qint16 plane_PID14_D = 0;
    qint16 plane_PID15_P = 0;
    qint16 plane_PID15_I = 0;
    qint16 plane_PID15_D = 0;
    qint16 plane_PID16_P = 0;
    qint16 plane_PID16_I = 0;
    qint16 plane_PID16_D = 0;
    qint16 plane_PID17_P = 0;
    qint16 plane_PID17_I = 0;
    qint16 plane_PID17_D = 0;
    qint16 plane_PID18_P = 0;
    qint16 plane_PID18_I = 0;
    qint16 plane_PID18_D = 0;

};
















#endif // FRAMEBOTTOM_H
