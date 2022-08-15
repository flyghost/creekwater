#ifndef WAVEFORM_H
#define WAVEFORM_H



#include <QWidget>


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
QT_CHARTS_USE_NAMESPACE





class WaveForm : public QWidget
{
	Q_OBJECT	


public:
    explicit WaveForm(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *);

    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;


private:
    void addPoint();
    //void delPoint();

public:
    void updateData(float newdata);


};



extern WaveForm *waveform;

#endif // WAVEFORM_H
