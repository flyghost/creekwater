
#include "radiobuttons.h"
#include "qpainter.h"
#include "qevent.h"
#include <QPainterPath>

RadioButtons::RadioButtons(QWidget *parent) : QWidget(parent)
{
    text = "";
    textColor = QColor(255, 255, 255);

    borderOutColorStart = QColor(11, 11, 11);
    borderOutColorEnd = QColor(44, 44, 4);

    borderInColorStart = QColor(66, 66, 66);
    borderInColorEnd = QColor(11, 11, 11);

    bgColor = QColor(55, 55, 55);

    showOverlay = true;
    overlayColor = QColor(255, 255, 255);

    canMove = false;
    this->installEventFilter(this);

    this->ifEnable = true;

    setFont(QFont("Consolas", 8));
}
void RadioButtons::setMouseEnable(bool enable)
{
    if(enable)
    {
        this->ifEnable = true;
    }
    else
    {
        this->ifEnable = false;
    }
}


//鼠标进入控件的事件
void RadioButtons::enterEvent(QEvent *e)
{
    if(ifEnable)
    {
        if(e->type() == QEvent::Enter)
        {
            this->setBlack();
        }
    }


}
//鼠标离开控件的事件
void RadioButtons::leaveEvent(QEvent *e)
{
    if(ifEnable)
    {
        if(e->type() == QEvent::Leave)
        {
            this->setDark();
        }
    }


}

void RadioButtons::mousePressEvent(QMouseEvent *e)
{
    if(ifEnable)
    {
        if (e->button() == Qt::LeftButton) {
            this->move(this->pos() + QPoint(2,2));
            e->accept();
            emit this->clicked();
        }
    }

}

void RadioButtons::mouseReleaseEvent(QMouseEvent *)
{
    if(ifEnable)
    {
        this->move(this->pos() + QPoint(-2,-2));
    }

}

bool RadioButtons::eventFilter(QObject *obj, QEvent *evt)
{
    if (canMove) {
        static QPoint lastPnt;
        static bool isHover = false;

        if (evt->type() == QEvent::MouseButtonPress) {
            setCursor(QCursor(Qt::OpenHandCursor));
            QMouseEvent *e = static_cast<QMouseEvent *>(evt);

            if (this->rect().contains(e->pos()) && (e->button() == Qt::LeftButton)) {
                lastPnt = e->pos();
                isHover = true;
            }
        } else if (evt->type() == QEvent::MouseMove && isHover) {
            QMouseEvent *e = static_cast<QMouseEvent *>(evt);
            int dx = e->pos().x() - lastPnt.x();
            int dy = e->pos().y() - lastPnt.y();
            this->move(this->x() + dx, this->y() + dy);
        } else if (evt->type() == QEvent::MouseButtonRelease && isHover) {
            setCursor(QCursor(Qt::ArrowCursor));
            isHover = false;
        }
    }

    return QWidget::eventFilter(obj, evt);
}

void RadioButtons::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);    
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框
    drawBorderOut(&painter);
    //绘制内边框
    drawBorderIn(&painter);
    //绘制内部指示颜色
    drawBg(&painter);
    //绘制居中文字
    drawText(&painter);
    //绘制遮罩层
    drawOverlay(&painter);
}

void RadioButtons::drawBorderOut(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderOutColorStart);
    borderGradient.setColorAt(1, borderOutColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void RadioButtons::drawBorderIn(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, borderInColorStart);
    borderGradient.setColorAt(1, borderInColorEnd);
    painter->setBrush(borderGradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void RadioButtons::drawBg(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void RadioButtons::drawText(QPainter *painter)
{
    if (text.isEmpty()) {
        return;
    }

    int radius = 100;
    painter->save();
    painter->setFont(QFont("Arial", 20, QFont::Bold, false));
    painter->setPen(textColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void RadioButtons::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

QString RadioButtons::getText() const
{
    return this->text;
}

QColor RadioButtons::getTextColor() const
{
    return this->textColor;
}

QColor RadioButtons::getBorderOutColorStart() const
{
    return this->borderOutColorStart;
}

QColor RadioButtons::getBorderOutColorEnd() const
{
    return this->borderOutColorEnd;
}

QColor RadioButtons::getBorderInColorStart() const
{
    return this->borderInColorStart;
}

QColor RadioButtons::getBorderInColorEnd() const
{
    return this->borderInColorEnd;
}

QColor RadioButtons::getBgColor() const
{
    return this->bgColor;
}

bool RadioButtons::getCanMove() const
{
    return this->canMove;
}

bool RadioButtons::getShowOverlay() const
{
    return this->showOverlay;
}

QColor RadioButtons::getOverlayColor() const
{
    return this->overlayColor;
}

QSize RadioButtons::sizeHint() const
{
    return QSize(100, 100);
}

QSize RadioButtons::minimumSizeHint() const
{
    return QSize(10, 10);
}

void RadioButtons::setText(const QString &text)
{
    if (this->text != text) {
        this->text = text;
        update();
    }
}

void RadioButtons::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        update();
    }
}

void RadioButtons::setBorderOutColorStart(const QColor &borderOutColorStart)
{
    if (this->borderOutColorStart != borderOutColorStart) {
        this->borderOutColorStart = borderOutColorStart;
        update();
    }
}

void RadioButtons::setBorderOutColorEnd(const QColor &borderOutColorEnd)
{
    if (this->borderOutColorEnd != borderOutColorEnd) {
        this->borderOutColorEnd = borderOutColorEnd;
        update();
    }
}

void RadioButtons::setBorderInColorStart(const QColor &borderInColorStart)
{
    if (this->borderInColorStart != borderInColorStart) {
        this->borderInColorStart = borderInColorStart;
        update();
    }
}

void RadioButtons::setBorderInColorEnd(const QColor &borderInColorEnd)
{
    if (this->borderInColorEnd != borderInColorEnd) {
        this->borderInColorEnd = borderInColorEnd;
        update();
    }
}

void RadioButtons::setBgColor(const QColor &bgColor)
{
    if (this->bgColor != bgColor) {
        this->bgColor = bgColor;
        update();
    }
}

void RadioButtons::setCanMove(bool canMove)
{
    if (this->canMove != canMove) {
        this->canMove = canMove;
        update();
    }
}

void RadioButtons::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        update();
    }
}

void RadioButtons::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        update();
    }
}

void RadioButtons::setGreen()
{
    setBgColor(QColor(0, 166, 0));
}

void RadioButtons::setRed()
{
    setBgColor(QColor(166, 0, 0));
}

void RadioButtons::setYellow()
{
    setBgColor(QColor(238, 238, 0));
}

void RadioButtons::setBlack()
{
    setBgColor(QColor(10, 10, 10));
}

void RadioButtons::setGray()
{
    setBgColor(QColor(129, 129, 129));
}

void RadioButtons::setBlue()
{
    setBgColor(QColor(0, 0, 166));
}

void RadioButtons::setLightBlue()
{
    setBgColor(QColor(100, 184, 255));
}

void RadioButtons::setLightRed()
{
    setBgColor(QColor(255, 107, 107));
}

void RadioButtons::setLightGreen()
{
    setBgColor(QColor(24, 189, 155));
}

void RadioButtons::setDark()
{
    setBgColor(QColor(55, 55, 55));
}


