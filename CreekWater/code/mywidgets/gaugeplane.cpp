
#include "gaugeplane.h"
#include "qpainter.h"
#include "qmath.h"
#include "qdebug.h"

GaugePlane::GaugePlane(QWidget *parent) : QWidget(parent)
{
    borderOutColorStart = QColor(180, 180, 180);//外边框渐变开始颜色
    borderOutColorEnd = QColor(50, 50, 50);//外边框渐变结束颜色

    borderInColorStart = QColor(50, 50, 50);//里边框渐变开始颜色
    borderInColorEnd = QColor(220, 220, 220);//里边框渐变结束颜色


    bgColor = QColor(56, 56, 56);//背景颜色
    planeColor = QColor(44, 44, 44);//姿态仪背景
    glassColor = QColor(111, 111, 111);//遮罩层颜色
    scaleColor = QColor(255, 255, 255);//刻度尺颜色
    lineColor = QColor(255, 255, 255);//线条颜色
    textColor = QColor(255, 255, 255);//文字颜色
    pointerColor = QColor(110, 149, 54);//指针颜色
    handleColor = QColor(77, 77, 77);//手柄颜色

    degValue = 0;
    rollValue = 0;
    value = 0;
    precision = 0;

}

void GaugePlane::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 300.0, side / 300.0);

    //绘制偏航外边框
    drawYawBorderOut(&painter);
    //绘制偏航内边框
    drawYawBorderIn(&painter);
    //绘制偏航背景
    drawYawBg(&painter);
    //绘制偏航刻度盘
    drawYawScale(&painter);
    //绘制偏航数字
    drawScaleNum(&painter);
    //绘制偏航指针
    drawYawPointer(&painter);
    //绘制外边框
    drawBorderOut(&painter);
    //绘制内边框
    drawBorderIn(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制姿势仪背景
    drawPlane(&painter);
    //绘制玻璃遮罩层
    drawGlass(&painter);
    //绘制刻度尺
    drawScale(&painter);
    //绘制线条
    drawLine(&painter);
    //绘制手柄
    drawHandle(&painter);
    //绘制文字
    drawValue(&painter);
}

void GaugePlane::drawYawBorderOut(QPainter *painter)
{
    int radius = 149;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderOutColorStart);
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugePlane::drawYawBorderIn(QPainter *painter)
{
    int radius = 146;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderInColorStart);
    borderGradient.setColorAt(1, borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void GaugePlane::drawYawBg(QPainter *painter)
{
    int radius = 145;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, QColor(44, 44, 44));
    borderGradient.setColorAt(1, QColor(44, 44, 44));
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void GaugePlane::drawYawScale(QPainter *painter)
{
    //设置刻度
    int radius = 145;
    painter->save();
    painter->rotate(yawValue);

    int steps = 120;
    double angleStep = 3.0;

    QPen pen;
    pen.setColor(QColor(255, 255, 255));
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % 10 == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }
    painter->restore();


}
void GaugePlane::drawScaleNum(QPainter *painter)
{
    int radius = 135;
    painter->save();
    painter->rotate(yawValue);
    painter->setPen(QColor(110, 149, 54));

    double value = 1.0 * 0 * 30;

    QString strValue = QString("%1").arg(static_cast<double>(value), 0, 'f', precision);

    QRect textRect = QRect(-radius, -radius, radius * 2, radius * 2);

    for (int i = 0; i < 12; i++) {
        value = 1.0 * i * 30;

        if(value == 0.0)
        {
            painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "E");
            //painter->drawText(x, y, "N");
        }
        else if(value == 90.0)
        {
            painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "S");
            //painter->drawText(x, y, "S");
        }
        else if(value == 180.0)
        {
            painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "W");
            //painter->drawText(x, y, "W");
        }
        else if(value == 270.0)
        {
            painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, "N");
            //painter->drawText(x, y, "E");
        }
        else
        {

            if(value > 180)
                value -= 360;

            strValue = QString("%1").arg(static_cast<double>(-value), 0, 'f', precision);
            painter->drawText(textRect, Qt::AlignTop | Qt::AlignHCenter, strValue);
            //painter->drawText(x, y, strValue);
        }

        painter->rotate(30);
    }


    painter->restore();
}
void GaugePlane::drawYawPointer(QPainter *painter)
{
    int radius = 115;
    painter->save();
    painter->setPen(Qt::NoPen);

    //指针长度
    int len = 20;
    //三角形坐标
    QPolygon pts;
    pts.setPoints(3, 0, -radius, -len / 2, -radius + len, len / 2, -radius + len);

    painter->setBrush(pointerColor);
    painter->drawConvexPolygon(pts);

    painter->restore();
}
void GaugePlane::drawBorderOut(QPainter *painter)
{
    int radius = 96;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderOutColorStart);
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugePlane::drawBorderIn(QPainter *painter)
{
    int radius = 93;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderInColorStart);
    borderGradient.setColorAt(1, borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void GaugePlane::drawBg(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    bgColor.setAlpha(255);
    borderGradient.setColorAt(0, bgColor);
    bgColor.setAlpha(150);
    borderGradient.setColorAt(1, bgColor);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}

void GaugePlane::drawPlane(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->rotate(degValue);
    painter->setPen(Qt::NoPen);
    painter->setBrush(planeColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);

#if 0
    painter->drawPie(rect, 0, -16 * 180);
#else
    float offset = -(rollValue * radius / 100);
    float startAngle = 180 + offset;
    float endAngle = offset;
    float span = endAngle + startAngle;
    painter->drawChord(rect, -16 * static_cast<int>(startAngle) , 16 * static_cast<int>(span) );
#endif
    painter->restore();
}

void GaugePlane::drawGlass(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    //饼圆1为整个圆形区域
    QRect pieRect1(-radius, -radius, radius * 2, radius * 2);
    //饼圆2位饼圆1区域的中间部分的四分之一
    QRect pieRect2(-radius, -radius / 4, radius * 2, radius / 4 * 2);

    //颜色线性渐变,颜色透明度产生立体感
    QLinearGradient linearGradient(pieRect1.topLeft(), pieRect1.bottomRight());
    glassColor.setAlpha(30);
    linearGradient.setColorAt(0.1, glassColor);
    glassColor.setAlpha(100);
    linearGradient.setColorAt(0.5, glassColor);

    //绘制两个饼圆
    painter->setBrush(linearGradient);
    painter->drawPie(pieRect1, 0, 16 * 180);
    painter->drawPie(pieRect2, 0, -16 * 180);

    painter->restore();
}

void GaugePlane::drawScale(QPainter *painter)
{
    int radius = 88;
    painter->save();

    //设置画笔颜色
    QPen pen;
    pen.setColor(scaleColor);
    pen.setWidthF(4);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    //线条长度
    int len = 8;

    //左侧平行线
    painter->rotate(90);
    painter->drawLine(0, radius - len, 0, radius);

    //逐个绘制大刻度
    for (int i = 0; i < 6; i++) {
        painter->rotate(30);
        painter->drawLine(0, radius - len, 0, radius);
    }

    //回到小刻度,重新设置画笔宽度
    pen.setWidthF(2);
    painter->setPen(pen);
    painter->rotate(-120);

    //逐个绘制小刻度
    for (int i = 0; i < 5; i++) {
        painter->rotate(10);
        painter->drawLine(0, radius - len, 0, radius);
    }

    painter->restore();
}

void GaugePlane::drawLine(QPainter *painter)
{
    double radius = 95;
    painter->save();

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //重置坐标系
    painter->resetTransform();
    painter->translate(width / 2, height / 2 + rollValue);
    painter->scale(side / 300.0, side / 300.0);

    painter->rotate(degValue);

    //设置画笔颜色
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidthF(2);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    //设置画笔字体
    QFont font;
    font.setPixelSize(10);
    font.setBold(true);
    painter->setFont(font);

    //依次绘制水平距离线条及值
    for (int i = -30; i <= 30; i += 10) {
        //中心点不用绘制
        if(i == 0) {
            continue;
        }

        int value = qAbs(i);

        //绘制横向水平线条
        QPointF pt1(-radius * value / 100, radius / 70 * i);
        QPointF pt2(-pt1.x(), pt1.y());
        painter->drawLine(pt1, pt2);

        //根据字体大小计算绘制文字的区域
        QString strValue = QString::number(value);
        QFontMetrics fm = painter->fontMetrics();
        QRectF textRect(QPointF(0, 0), fm.size(Qt::AlignCenter, strValue));

        textRect.moveCenter(pt1 - QPointF(radius / 10, 0));
        painter->drawText(textRect, Qt::AlignCenter, strValue);

        textRect.moveCenter(pt2 + QPointF(radius / 10, 0));
        painter->drawText(textRect, Qt::AlignCenter, strValue);
    }

    painter->restore();
}

void GaugePlane::drawHandle(QPainter *painter)
{
    painter->save();

    QPen pen;
    pen.setColor(handleColor);
    pen.setWidthF(4);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(handleColor);

    //绘制弧形
    int arcRadius = 15;
    QRect rect(-arcRadius, -arcRadius, arcRadius * 2, arcRadius * 2);
    painter->drawArc(rect, 0, -16 * 180);

    //绘制中心圆
    int centerRadius = 2;
    rect = QRect(-centerRadius, -centerRadius, centerRadius * 2, centerRadius * 2);
    painter->drawEllipse(rect);

    //绘制左侧右侧横向水平线条
    int len = 30;
    QPoint pt1 = QPoint(-len, 0);
    QPoint pt2 = QPoint(-arcRadius, 0);
    painter->drawLine(pt1, pt2);

    pt1 = QPoint(len, 0);
    pt2 = QPoint(arcRadius, 0);
    painter->drawLine(pt1, pt2);

    //绘制纵向垂直线条
    pt1 = QPoint(0, len / 2);
    pt2 = QPoint(0, 80);
    painter->drawLine(pt1, pt2);

    //绘制底部梯形
    QPolygon pts;
    QPoint p1(-30, 82);
    QPoint p2(-20, 60);
    QPoint p3(20, 60);
    QPoint p4(30, 82);
    pts << p1 << p2 << p3 << p4;
    painter->drawConvexPolygon(pts);

    //绘制底部填充圆弧
    int radius = 32;
    rect = QRect(-radius, 77, radius * 2, 13);
    painter->setPen(Qt::NoPen);
    painter->drawPie(rect, 0, -16 * 180);

    painter->restore();
}

void GaugePlane::drawValue(QPainter *painter)
{
    int radius = 120;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(11);
    font.setBold(true);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg(static_cast<double>(value), 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);
    painter->restore();
}

QColor GaugePlane::getBorderOutColorStart() const
{
    return this->borderOutColorStart;
}

QColor GaugePlane::getBorderOutColorEnd() const
{
    return this->borderOutColorEnd;
}

QColor GaugePlane::getBorderInColorStart() const
{
    return this->borderInColorStart;
}

QColor GaugePlane::getBorderInColorEnd() const
{
    return this->borderInColorEnd;
}

QColor GaugePlane::getBgColor() const
{
    return this->bgColor;
}

QColor GaugePlane::getPlaneColor() const
{
    return this->planeColor;
}

QColor GaugePlane::getGlassColor() const
{
    return this->glassColor;
}

QColor GaugePlane::getScaleColor() const
{
    return this->scaleColor;
}

QColor GaugePlane::getLineColor() const
{
    return this->lineColor;
}

QColor GaugePlane::getTextColor() const
{
    return this->textColor;
}

QColor GaugePlane::getPointerColor() const
{
    return this->pointerColor;
}

QColor GaugePlane::getHandleColor() const
{
    return this->handleColor;
}

int GaugePlane::getDegValue() const
{
    return this->degValue;
}

int GaugePlane::getRollValue() const
{
    return this->rollValue;
}

QSize GaugePlane::sizeHint() const
{
    return QSize(200, 200);
}

QSize GaugePlane::minimumSizeHint() const
{
    return QSize(50, 50);
}

void GaugePlane::setBorderOutColorStart(const QColor &borderOutColorStart)
{
    if (this->borderOutColorStart != borderOutColorStart) {
        this->borderOutColorStart = borderOutColorStart;
        update();
    }
}

void GaugePlane::setBorderOutColorEnd(const QColor &borderOutColorEnd)
{
    if (this->borderOutColorEnd != borderOutColorEnd) {
        this->borderOutColorEnd = borderOutColorEnd;
        update();
    }
}

void GaugePlane::setBorderInColorStart(const QColor &borderInColorStart)
{
    if (this->borderInColorStart != borderInColorStart) {
        this->borderInColorStart = borderInColorStart;
        update();
    }
}

void GaugePlane::setBorderInColorEnd(const QColor &borderInColorEnd)
{
    if (this->borderInColorEnd != borderInColorEnd) {
        this->borderInColorEnd = borderInColorEnd;
        update();
    }
}

void GaugePlane::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void GaugePlane::setPlaneColor(const QColor &planeColor)
{
    if (this->planeColor != planeColor) {
        this->planeColor = planeColor;
        update();
    }
}

void GaugePlane::setGlassColor(const QColor &glassColor)
{
    if (this->glassColor != glassColor) {
        this->glassColor = glassColor;
        update();
    }
}

void GaugePlane::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        update();
    }
}

void GaugePlane::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        update();
    }
}

void GaugePlane::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void GaugePlane::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        update();
    }
}

void GaugePlane::setHandleColor(const QColor &handleColor)
{
    if (this->handleColor != handleColor) {
        this->handleColor = handleColor;
        update();
    }
}

void GaugePlane::setDegValue(int degValue)
{
    if (this->degValue != degValue && degValue >= -180 && degValue <= 180) {
        this->degValue = degValue;
        update();
    }
}

void GaugePlane::setRollValue(int rollValue)
{
    if (this->rollValue != rollValue && rollValue >= -100 && rollValue <= 100) {
        this->rollValue = rollValue;
        update();
    }
}
void GaugePlane::setYawValue(int yawValue)
{
    if (this->yawValue != yawValue && yawValue >= -200 && yawValue <= 200) {
        this->yawValue = yawValue;
        update();
    }
}

