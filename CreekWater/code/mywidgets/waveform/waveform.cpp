//#pragma execution_character_set("utf-8")

#include "waveform.h"
#include "qpainter.h"

#include "qdebug.h"


#include <QHBoxLayout>



WaveForm *waveform;

WaveForm::WaveForm(QWidget *parent) : QWidget(parent)
{    
    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
//    for (int i = 0; i < 500; i++) {
//        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
//        p.ry() += QRandomGenerator::global()->bounded(20);
//        *series << p;
//    }



    chart->addSeries(series);
    chart->setTitle("波形助手");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();




    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand);

    QHBoxLayout *cmdLayout=new QHBoxLayout(this);
    cmdLayout->addWidget(chartView);
}
void WaveForm::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);




}



void WaveForm::updateData(float newdata)
{
    int i;
    QVector<QPointF> oldData = series->pointsVector();
    QVector<QPointF> data;

    //qDebug() << "dddd" ;

    if (oldData.size() < 510) {
        data = series->pointsVector();
    } else {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
        for (i = 1; i < oldData.size(); ++i) {
            data.append(QPointF(i - 1 , oldData.at(i).y()));
        }
    }

    qint64 size = data.size();
    /* 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
//    for(i = 0; i < 1; ++i){
//        data.append(QPointF(i + size, 10 * sin(M_PI * count * 4 / 180)));
//    }
    data.append(QPointF(i + size, static_cast<qreal>(newdata)));

    series->replace(data);


}









