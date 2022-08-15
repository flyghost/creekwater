#pragma execution_character_set("utf-8")

#include "progressbarwater.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"
#include <QPainterPath>

ProgressBarWater::ProgressBarWater(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 1000;
    value = 0;
    name = "M";

    borderWidth = 0.0;
    waterHeight = 0.02;
    waterDensity = 2.0;

    showValue = true;
    showPercent = true;
    reverse = false;

    borderColor = QColor(50, 50, 50);
    bgColor = QColor(100, 100, 100);
    usedColor = QColor(100, 184, 255);
    textColor = QColor(250, 250, 250);

    percentStyle = PercentStyle_Circle;

    offset = 0;
    timer = new QTimer(this);
    timer->setInterval(70);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setFont(QFont("Arial", 8));
}

ProgressBarWater::~ProgressBarWater()
{
    stop();
}

void ProgressBarWater::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制当前进度
    drawProgress(&painter);

    //绘制当前值
    drawValue(&painter);
}

void ProgressBarWater::drawBg(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //起始点坐标和结束点坐标
    int startX = borderWidth * 0.5;
    int startY = borderWidth * 0.5;
    int endX = width - borderWidth;
    int endY = height - borderWidth;

    //圆形的区域要重新计算
    if (percentStyle == PercentStyle_Circle) {
        side = side - borderWidth;
        startX = (width - side) / 2;
        startY = (height - side) / 2;
        endX = (width + side) / 2;
        endY = (height + side) / 2;
    }

    painter->save();
    painter->setBrush(bgColor);

    //如果边框宽度为0则重新设置为无画笔,否则启用了反锯齿后会有边框
    if (borderWidth == 0) {
        painter->setPen(Qt::NoPen);
    } else {
        QPen pen;
        pen.setColor(borderColor);
        pen.setWidthF(borderWidth);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
    }

    //绘制背景区域
    if (percentStyle == PercentStyle_Rect) {
        painter->drawRect(startX, startY, endX, endY);
    } else if (percentStyle == PercentStyle_Circle) {
        painter->drawEllipse(startX, startY, side, side);
    } else if (percentStyle == PercentStyle_Ellipse) {
        painter->drawEllipse(startX, startY, endX, endY);
    } else if (percentStyle == PercentStyle_Cylinder) {
        QRect rect(startX, startY, endX, endY);
        int side = qMin(rect.width(), rect.height());

        //宽度大于高度则左右两侧半圆,否则上下两侧半圆
        if (rect.width() > rect.height()) {
            //左侧圆
            QPainterPath path1;
            path1.addEllipse(rect.x(), rect.y(), side, side);
            //右侧圆
            QPainterPath path2;
            path2.addEllipse(rect.width() - side, rect.y(), side, side);
            //中间矩形
            QPainterPath path3;
            path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side - borderWidth, rect.height());

            QPainterPath path;
            path = path3 + path1 + path2;
            painter->drawPath(path);
        } else {
            //上侧圆
            QPainterPath path1;
            path1.addEllipse(rect.x(), rect.y(), side, side);
            //下侧圆
            QPainterPath path2;
            path2.addEllipse(rect.x(), rect.height() - side, side, side);
            //中间矩形
            QPainterPath path3;
            path3.addRect(rect.x() , rect.y() + side / 2, rect.width(), rect.height() - side - borderWidth);

            QPainterPath path;
            path = path3 + path1 + path2;
            painter->drawPath(path);
        }
    }

    painter->restore();
}

void ProgressBarWater::drawProgress(QPainter *painter)
{
    int height = this-> height();
    int width = this->width();
    int side = qMin(width, height);

    //起始点坐标和结束点坐标
    int startX = borderWidth;
    int startY = borderWidth;
    int endX = width - borderWidth;
    int endY = height - borderWidth;

    //圆形的区域要重新计算
    if (percentStyle == PercentStyle_Circle) {
        side = side - borderWidth * 2;
        startX = (width - side) / 2;
        startY = (height - side) / 2;
        endX = (width + side) / 2;
        endY = (height + side) / 2;
    }

    //计算当前值所占百分比
    double percent = 1 - (double)(value - minValue) / (maxValue - minValue);

    //正弦曲线公式 y = A * qSin(ωx + φ) + k

    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double w = waterDensity * M_PI / endX;

    //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double A = endY * waterHeight;

    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比
    double k = endY * percent;

    //圆形的区域要重新计算
    if (percentStyle == PercentStyle_Circle) {
        k = (side * percent) + startY;
    }

    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;

    //移动到左上角起始点
    waterPath1.moveTo(startX, endY);
    waterPath2.moveTo(startX, endY);

    offset += 0.6;
    if (offset > (endX / 2)) {
        offset = 0;
    }

    for(int x = startX; x <= endX; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * qSin(w * x + offset)) + k;
        //第二条波浪Y轴
        double waterY2;
        if (reverse) {
            waterY2 = (double)(A * qSin(w * -x + offset + 10)) + k;
        } else {
            waterY2 = (double)(A * qSin(w * x + offset + (endX / 2 * w))) + k;
        }

        //如果当前值为最小值则Y轴为右下角Y轴
        if (this->value == minValue) {
            waterY1 = endY;
            waterY2 = endY;
        }

        //如果当前值为最大值则Y轴为右上角Y轴
        if (this->value == maxValue) {
            waterY1 = startY;
            waterY2 = startY;
        }

        //将两个点连接成线
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }

    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(endX, endY);
    waterPath2.lineTo(endX, endY);

    //大路径
    QPainterPath bigPath;
    if (percentStyle == PercentStyle_Rect) {
        bigPath.addRect(startX, startY, endX, endY);
    } else if (percentStyle == PercentStyle_Circle) {
        bigPath.addEllipse(startX, startY, side, side);
    } else if (percentStyle == PercentStyle_Ellipse) {
        bigPath.addEllipse(startX, startY, width - borderWidth * 2, height - borderWidth * 2);
    } else if (percentStyle == PercentStyle_Cylinder) {
        QRect rect(startX, startY, endX - borderWidth, endY - borderWidth);
        int side = qMin(rect.width(), rect.height());

        //宽度大于高度则左右两侧半圆,否则上下两侧半圆
        if (rect.width() > rect.height()) {
            //左侧圆
            QPainterPath path1;
            path1.addEllipse(rect.x(), rect.y(), side, side);
            //右侧圆
            QPainterPath path2;
            path2.addEllipse(rect.width() - side + borderWidth / 2, rect.y(), side, side);
            //中间矩形
            QPainterPath path3;
            path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side - borderWidth / 2, rect.height());

            QPainterPath path;
            path = path3 + path1 + path2;
            bigPath.addPath(path);
        } else {
            //上侧圆
            QPainterPath path1;
            path1.addEllipse(rect.x(), rect.y(), side, side);
            //下侧圆
            QPainterPath path2;
            path2.addEllipse(rect.x(), rect.height() - side + borderWidth / 2, side, side);
            //中间矩形
            QPainterPath path3;
            path3.addRect(rect.x(), rect.y() + side / 2, rect.width(), rect.height() - side - borderWidth / 2);

            QPainterPath path;
            path = path3 + path1 + path2;
            bigPath.addPath(path);
        }
    }

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;
    QColor waterColor1 = usedColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = usedColor;
    waterColor2.setAlpha(200);

    painter->save();
    painter->setPen(Qt::NoPen);

    //第一条波浪挖去后的路径
    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    //第二条波浪挖去后的路径
    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);

    painter->restore();
}

void ProgressBarWater::drawValue(QPainter *painter)
{
    if (!showValue) {
        return;
    }

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    painter->save();
    painter->setPen(textColor);

    //设置当前字体大小随着窗体大小变化而变化
    int fontSize = (side - borderWidth) / 2;
    if (showPercent) {
        //fontSize = (side - borderWidth) / 3;
        fontSize = (side - borderWidth) / 5;
    }

    QFont font;
    font.setPixelSize(fontSize);
    painter->setFont(font);

    QRectF textRect(0, 0, width, height);
    //QString strValue = QString("%1 %2").arg(name).arg(value);
    QString strValue = QString("%1\r\n%2").arg(name).arg(value);

    if (showPercent) {
        //strValue = QString("%1%2%").arg(name).arg(value);
        //strValue = QString("%1%2%").arg(name).arg((double)(value - minValue) / (maxValue - minValue) * 100, 0, 'f', 0);
        strValue = QString("%1\r\n%2\r\n%3%").arg(name).arg(value).arg((double)(value - minValue) / (maxValue - minValue) * 100, 0, 'f', 0);
    }

    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

int ProgressBarWater::getMinValue() const
{
    return this->minValue;
}

int ProgressBarWater::getMaxValue() const
{
    return this->maxValue;
}

int ProgressBarWater::getValue() const
{
    return this->value;
}

double ProgressBarWater::getBorderWidth() const
{
    return this->borderWidth;
}

double ProgressBarWater::getWaterHeight() const
{
    return this->waterHeight;
}

double ProgressBarWater::getWaterDensity() const
{
    return this->waterDensity;
}

bool ProgressBarWater::getShowValue() const
{
    return this->showValue;
}

bool ProgressBarWater::getReverse() const
{
    return this->reverse;
}

bool ProgressBarWater::getShowPercent() const
{
    return this->showPercent;
}

QColor ProgressBarWater::getBorderColor() const
{
    return this->borderColor;
}

QColor ProgressBarWater::getBgColor() const
{
    return this->bgColor;
}

QColor ProgressBarWater::getUsedColor() const
{
    return this->usedColor;
}

QColor ProgressBarWater::getTextColor() const
{
    return this->textColor;
}

ProgressBarWater::PercentStyle ProgressBarWater::getPercentStyle() const
{
    return this->percentStyle;
}

QSize ProgressBarWater::sizeHint() const
{
    return QSize(200, 200);
}

QSize ProgressBarWater::minimumSizeHint() const
{
    return QSize(10, 10);
}

void ProgressBarWater::setRange(int minValue, int maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    if (value < minValue || value > maxValue) {
        setValue(value);
    }

    update();
}

void ProgressBarWater::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void ProgressBarWater::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void ProgressBarWater::setValue(int value)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (value < minValue || value > maxValue || value == this->value) {
        return;
    }

    this->value = value;
    update();
    emit valueChanged(value);

    //如果当前值为最小值或者最大值则停止浪,不要再浪了 ^_^
    if (this->value == minValue || this->value == maxValue) {
        if (timer->isActive()) {
            timer->stop();
        }
    } else {
        if (!timer->isActive()) {
            timer->start();
        }
    }
}

void ProgressBarWater::setBorderWidth(double borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        update();
    }
}

void ProgressBarWater::setWaterHeight(double waterHeight)
{
    if (waterHeight > 0.1) {
        return;
    }

    if (this->waterHeight != waterHeight) {
        this->waterHeight = waterHeight;
        update();
    }
}

void ProgressBarWater::setWaterDensity(double waterDensity)
{
    if (this->waterDensity != waterDensity) {
        this->waterDensity = waterDensity;
        update();
    }
}

void ProgressBarWater::setShowValue(bool showValue)
{
    if (this->showValue != showValue) {
        this->showValue = showValue;
        update();
    }
}

void ProgressBarWater::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent) {
        this->showPercent = showPercent;
        update();
    }
}

void ProgressBarWater::setReverse(bool reverse)
{
    if (this->reverse != reverse) {
        this->reverse = reverse;
        update();
    }
}

void ProgressBarWater::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void ProgressBarWater::setBorderColor(const QColor &borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        update();
    }
}

void ProgressBarWater::setUsedColor(const QColor &usedColor)
{
    if (this->usedColor != usedColor) {
        this->usedColor = usedColor;
        update();
    }
}

void ProgressBarWater::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}
void ProgressBarWater::setTextName(QString usedname)
{
    if (this->name != usedname) {
        this->name = usedname;
        update();
    }
}

void ProgressBarWater::setPercentStyle(const ProgressBarWater::PercentStyle &percentStyle)
{
    if (this->percentStyle != percentStyle) {
        this->percentStyle = percentStyle;
        update();
    }
}

void ProgressBarWater::start()
{
    if (!timer->isActive()) {
        timer->start();
    }
}

void ProgressBarWater::stop()
{
    if (timer->isActive()) {
        timer->stop();
    }
}
