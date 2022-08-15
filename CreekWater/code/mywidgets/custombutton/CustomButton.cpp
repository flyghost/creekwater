/*
*  圆盘式按钮
*/


#include "CustomButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>

CustomButton::CustomButton(QWidget* parent)
    : QWidget(parent)
    , m_radius(150)
    , m_arcLength(75), m_pressIndex(0)
    , m_enterIndex(0)
    , m_isMousePressed(false)
    , m_isMouseEntered(false)
{
    this->setMouseTracking(true);
    initButton();

}

//设置半径
void CustomButton::setRadiusValue(int radius)
{
    m_radius = radius;
}
//设置弧长
void CustomButton::setArcLength(int arcLength)
{
    m_arcLength = arcLength;
}
void CustomButton::setButtonEnable(int buttonId, bool enable)
{
    buttonsEnable[buttonId] = enable;
}
//初始化按钮
void CustomButton::initButton()
{
    addArc(45,  89.5, qRgb(44, 44, 44));//扇形颜色
    addArc(135, 89.5, qRgb(44, 44, 44));
    addArc(225, 89.5, qRgb(44, 44, 44));
    addArc(315, 89.5, qRgb(44, 44, 44));

    // 绘制中心圆;
    QPainterPath centerRoundPath;
    centerRoundPath.addEllipse(QPoint(0, 0), m_radius - m_arcLength, m_radius - m_arcLength);
    m_arcPathList.append(centerRoundPath);
    m_colorList.append(QColor(66, 66, 66));//中心圆颜色

    // 添加文字;
    QFont font;
    font.setFamily("隶书");
    font.setPointSize(20);

    for (int i = 0; i < m_arcPathList.count(); i++)
    {
        QPainterPath painterPath;
        m_textPathList.append(painterPath);
    }

    m_textPathList[0].addText(QPoint(-45, -90), font, QStringLiteral("拓空者"));//上
    m_textPathList[1].addText(QPoint(-70, 10), font, QStringLiteral(""));//左
    m_textPathList[2].addText(QPoint(-45, 111), font, QStringLiteral("数传"));//下
    m_textPathList[3].addText(QPoint(50, 10), font, QStringLiteral(""));//右
    m_textPathList[4].addText(QPoint(-30, 10), font, QStringLiteral("搜索"));//中间
}

void CustomButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.translate(width() >> 1, height() >> 1);

    painter.setBrush(QColor(60, 60, 60));
    painter.drawEllipse(QPoint(0, 0), 89, 89);

    for (int i = 0; i < m_arcPathList.count(); i++)
    {
        painter.setBrush(m_colorList[i]);
        painter.drawPath(m_arcPathList[i]);
        if (i == m_pressIndex && m_isMousePressed)
        {
            painter.setBrush(QColor(255, 255, 255, 120));
            painter.drawPath(m_arcPathList[i]);

        }
        else if (i == m_pressIndex && m_isMouseEntered)
        {
            painter.setBrush(QColor(255, 255, 255, 60));
            painter.drawPath(m_arcPathList[i]);
        }
        painter.setBrush(Qt::black);
        painter.drawPath(m_textPathList[i]);
    }
}

void CustomButton::addArc(qreal startAngle, qreal angleLength, QRgb color)
{
    QRectF rect(-m_radius, -m_radius, m_radius * 2, m_radius * 2);

    // 设置扇形路径;
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);
    QPainterPath subPath;
    // 设置小扇形路径;
    subPath.addEllipse(rect.adjusted(m_arcLength, m_arcLength, -m_arcLength, -m_arcLength));
    // 大扇形减去小扇形得到圆弧;
    path -= subPath;

    m_arcPathList.append(path);

    // 设置圆弧颜色;
    QRadialGradient radialGradient;
    radialGradient.setCenter(0, 0);
    radialGradient.setRadius(m_radius);
    radialGradient.setColorAt(0, Qt::white);
    radialGradient.setColorAt(1.0, color);
    m_colorList.append(radialGradient);
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePressPoint = event->pos();
    QPoint translatePoint = mousePressPoint - QPoint(width() >> 1, height() >> 1);
    for (int i = 0; i < m_arcPathList.count(); i++)
    {
        if(buttonsEnable[i])
        {
            if (m_arcPathList[i].contains(translatePoint) || m_textPathList[i].contains(translatePoint))
            {
                m_pressIndex = i;
                m_isMousePressed = true;
                update();
                emit CustomButtonClicked(i);
                break;
            }
        }


    }
}

void CustomButton::mouseReleaseEvent(QMouseEvent *)
{
    if (m_isMousePressed)
    {
        m_isMousePressed = false;
        emit CustomButtonReleased(m_pressIndex);
        update();
    }
}

void CustomButton::mouseMoveEvent(QMouseEvent *event)
{
    m_isMouseEntered = false;
    QPoint mousePressPoint = event->pos();
    QPoint translatePoint = mousePressPoint - QPoint(width() >> 1, height() >> 1);
    for (int i = 0; i < m_arcPathList.count(); i++)
    {
        if(buttonsEnable[i])
        {
            if (m_arcPathList[i].simplified().contains(translatePoint) || m_textPathList[i].contains(translatePoint))
            {
                m_pressIndex = i;
                m_isMouseEntered = true;
                break;
            }
        }

    }
    update();
}
