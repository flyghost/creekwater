#pragma once

#include <QtWidgets/QWidget>


class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget* parent = nullptr);
    // 设置弧长及半径;
    void setRadiusValue(int radius);
    void setArcLength(int arcLength);
    void setButtonEnable(int buttonId, bool enable);
private:
    // 初始化按钮;
    void initButton();
    // 绘制按钮; 
    void paintEvent(QPaintEvent *);
    // 添加圆弧;
    void addArc(qreal startAngle, qreal angleLength, QRgb color);

    // 鼠标事件;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

    // 鼠标离开事件;
    //void leaveEvent(QEvent *event);

signals:
    // 鼠标点击;
    void CustomButtonClicked(int buttonId);
    // 鼠标松开;
    void CustomButtonReleased(int buttonId);

private:
    // 弧长及半径;
    int m_radius, m_arcLength;
    // 圆弧路径;
    QList<QPainterPath> m_arcPathList;
    QList<QPainterPath> m_textPathList;
    // 圆弧颜色;
    QList<QBrush> m_colorList;
    // 当前鼠标按钮/进入 按钮的索引;
    int m_pressIndex, m_enterIndex;
    // 鼠标事件标志位;
    bool m_isMousePressed;
    bool m_isMouseEntered;
    bool buttonsEnable[5] = {false,false,false,false,true};

};
