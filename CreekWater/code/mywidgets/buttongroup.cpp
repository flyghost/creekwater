//#pragma execution_character_set("utf-8")

/*
*  按钮组
*/



#include "buttongroup.h"
#include "qpainter.h"
#include "qevent.h"
#include "qabstractbutton.h"
#include "qpushbutton.h"
#include "qbuttongroup.h"
#include "qpropertyanimation.h"
#include "qlayout.h"
#include "qtimer.h"
#include "qdebug.h"

ButtonGroup::ButtonGroup(QWidget *parent) : QWidget(parent)
{
    interval = 300;
    lineLen = 3;
    texts = "";
    linePosition = LinePosition_Top;

    lineColor = QColor(34, 163, 169);
    btnNormalColor = QColor(255, 255, 255);
    btnHoverColor = QColor(34, 163, 169, 100);
    btnDarkColor = QColor(34, 163, 169, 180);
    textNormalColor = QColor(0, 0, 0);
    textHoverColor = QColor(255, 255, 255);
    textDarkColor = QColor(255, 255, 255);
    baseColor = QColor(34, 163, 169);

    index = 0;
    previousIndex = 0;
    offset = 0;
    btnSize = QSize(30, 30);
    layout = 0;

    btnGroup = new QButtonGroup(this);
    connect(btnGroup, SIGNAL(buttonClicked(int)), SLOT(onButtonClicked(int)));

    animation = new QPropertyAnimation(this, "");
    animation->setDuration(interval);
    connect(animation, SIGNAL(valueChanged(QVariant)), SLOT(onValueChanged(QVariant)));

    //默认在底部
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, lineLen, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
}

ButtonGroup::~ButtonGroup()
{
}

void ButtonGroup::resizeEvent(QResizeEvent *)
{
    //尺寸改变的时候要重新计算并绘制
    this->init();
}

void ButtonGroup::showEvent(QShowEvent *)
{
    //显示时需要重新计算并绘制
    this->init();
}

void ButtonGroup::paintEvent(QPaintEvent *)
{
    if (btns.count() == 0) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    //设置颜色
    painter.setPen(Qt::NoPen);
    painter.setBrush(lineColor);

    //根据不同的位置绘制线条区域,也可以改成绘制两点之间的距离
    if (linePosition == LinePosition_Top) {
        painter.drawRect(offset, 0, btnSize.width(), lineLen);
    } else if (linePosition == LinePosition_Bottom) {
        painter.drawRect(offset, this->height() - lineLen, btnSize.width(), lineLen);
    } else if (linePosition == LinePosition_Left) {
        painter.drawRect(0, offset, lineLen, btnSize.height());
    } else if (linePosition == LinePosition_Right) {
        painter.drawRect(this->width() - lineLen, offset, lineLen, btnSize.height());
    }
}

void ButtonGroup::onButtonClicked(int index)
{
    //当前按钮选中
    btnGroup->button(index)->setChecked(true);

    //更新当前按钮和上一个按钮的索引
    previousIndex = this->index;
    this->index = index;

    //根据线条位置设置动画启动和结束值
    if (linePosition == LinePosition_Top || linePosition == LinePosition_Bottom) {
        animation->setStartValue(btns.at(previousIndex)->x());
        animation->setEndValue(btns.at(index)->x());
    } else if (linePosition == LinePosition_Left || linePosition == LinePosition_Right) {
        animation->setStartValue(btns.at(previousIndex)->y());
        animation->setEndValue(btns.at(index)->y());
    }

    //启动动画移动线条
    animation->start();

    //发送信号出去
    emit buttonClicked(index);
    emit buttonClicked(btns.at(index));
}

void ButtonGroup::onValueChanged(const QVariant &value)
{
    offset = value.toInt();
    update();
}

int ButtonGroup::getInterval() const
{
    return this->interval;
}

int ButtonGroup::getLineLen() const
{
    return this->lineLen;
}

int ButtonGroup::getIndex() const
{
    return this->index;
}

QString ButtonGroup::getTexts() const
{
    return this->texts;
}

ButtonGroup::LinePosition ButtonGroup::getLinePosition() const
{
    return this->linePosition;
}

QColor ButtonGroup::getLineColor() const
{
    return this->lineColor;
}

QColor ButtonGroup::getBtnNormalColor() const
{
    return this->btnNormalColor;
}

QColor ButtonGroup::getBtnHoverColor() const
{
    return this->btnHoverColor;
}

QColor ButtonGroup::getBtnDarkColor() const
{
    return this->btnDarkColor;
}

QColor ButtonGroup::getTextNormalColor() const
{
    return this->textNormalColor;
}

QColor ButtonGroup::getTextHoverColor() const
{
    return this->textHoverColor;
}

QColor ButtonGroup::getTextDarkColor() const
{
    return this->textDarkColor;
}

QColor ButtonGroup::getBaseColor() const
{
    return this->baseColor;
}

QSize ButtonGroup::sizeHint() const
{
    return QSize(200, 200);
}

QSize ButtonGroup::minimumSizeHint() const
{
    return QSize(20, 20);
}

void ButtonGroup::setInterval(int interval)
{
    if (this->interval != interval) {
        this->interval = interval;
        animation->setDuration(interval);
        update();
    }
}

void ButtonGroup::setLineLen(int lineLen)
{
    if (this->lineLen != lineLen) {
        this->lineLen = lineLen;
        update();
    }
}

void ButtonGroup::setIndex(int index)
{
    if (index < btns.count() && this->index != index) {
        this->index = index;
        btns.at(index)->click();
    }
}

void ButtonGroup::setTexts(const QString &texts)
{
    if (this->texts != texts && !texts.isEmpty()) {
        QStringList list = texts.split(";");
        if (list.count() == 0) {
            return;
        }

        this->texts = texts;
        index = 0;
        previousIndex = 0;
        offset = 0;

        //清空原有按钮
        qDeleteAll(btns);
        btns.clear();

        //重新逐个根据文本分割实例化按钮加入
        for (int i = 0; i < list.count(); i++) {
            QPushButton *btn = new QPushButton;
            btn->setCheckable(true);
            btn->setText(list.at(i));
            btn->setMinimumHeight(30);
            this->addButton((QAbstractButton *)btn, i);
        }

        //重新初始化,以便线条立即跟踪过去
        QTimer::singleShot(0, this, SLOT(init()));
    }
}

void ButtonGroup::setLinePosition(const ButtonGroup::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;

        //清除布局
        if (layout != 0) {
            delete layout;
            layout = 0;
        }

        //重新设置布局
        if (linePosition == LinePosition_Top) {
            layout = new QHBoxLayout(this);
            layout->setContentsMargins(0, lineLen, 0, 0);
        } else if (linePosition == LinePosition_Bottom) {
            layout = new QHBoxLayout(this);
            layout->setContentsMargins(0, 0, 0, lineLen);
        } else if (linePosition == LinePosition_Left) {
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(lineLen, 0, 0, 0);
        } else if (linePosition == LinePosition_Right) {
            layout = new QVBoxLayout(this);
            layout->setContentsMargins(0, 0, lineLen, 0);
        }

        layout->setSpacing(0);
        setLayout(layout);

        //重新加载按钮到布局
        foreach (QAbstractButton *btn, btns) {
            layout->addWidget(btn);
        }

        //重新初始化,以便线条立即跟踪过去
        QTimer::singleShot(0, this, SLOT(init()));
    }
}

void ButtonGroup::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setBtnNormalColor(const QColor &btnNormalColor)
{
    if (this->btnNormalColor != btnNormalColor) {
        this->btnNormalColor = btnNormalColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setBtnHoverColor(const QColor &btnHoverColor)
{
    if (this->btnHoverColor != btnHoverColor) {
        this->btnHoverColor = btnHoverColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setBtnDarkColor(const QColor &btnDarkColor)
{
    if (this->btnDarkColor != btnDarkColor) {
        this->btnDarkColor = btnDarkColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setTextNormalColor(const QColor &textNormalColor)
{
    if (this->textNormalColor != textNormalColor) {
        this->textNormalColor = textNormalColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setTextHoverColor(const QColor &textHoverColor)
{
    if (this->textHoverColor != textHoverColor) {
        this->textHoverColor = textHoverColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setTextDarkColor(const QColor &textDarkColor)
{
    if (this->textDarkColor != textDarkColor) {
        this->textDarkColor = textDarkColor;
        this->setBtnStyle();
        update();
    }
}

void ButtonGroup::setBaseColor(const QColor &baseColor, bool normal)
{
    if (this->baseColor != baseColor) {
        this->baseColor = baseColor;

        //根据基准颜色设置其他颜色
        if (normal) {
            this->btnNormalColor = this->baseColor;
        }

        this->lineColor = this->baseColor;
        this->baseColor.setAlpha(100);
        this->btnHoverColor = this->baseColor;
        this->baseColor.setAlpha(180);
        this->btnDarkColor = this->baseColor;
        this->setBtnStyle();

        update();
    }
}

void ButtonGroup::init()
{
    //首次显示重新纠正按钮尺寸大小
    if (btns.count() > 0) {
        btnSize = btns.at(0)->size();
        btns.at(index)->click();
    }
}

void ButtonGroup::addButton(QAbstractButton *btn, int id)
{
    layout->addWidget(btn);
    btns.append(btn);
    btnGroup->addButton(btn, id);

    //按钮的样式,可以自行拓展比如圆角
    QStringList qss;
    qss.append(QString("QAbstractButton{border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnNormalColor.red()).arg(btnNormalColor.green()).arg(btnNormalColor.blue()).arg(btnNormalColor.alpha())
               .arg(textNormalColor.red()).arg(textNormalColor.green()).arg(textNormalColor.blue()).arg(textNormalColor.alpha()));
    qss.append(QString("QAbstractButton:hover{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnHoverColor.red()).arg(btnHoverColor.green()).arg(btnHoverColor.blue()).arg(btnHoverColor.alpha())
               .arg(textHoverColor.red()).arg(textHoverColor.green()).arg(textHoverColor.blue()).arg(textHoverColor.alpha()));
    qss.append(QString("QAbstractButton:pressed,QAbstractButton:checked{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnDarkColor.red()).arg(btnDarkColor.green()).arg(btnDarkColor.blue()).arg(btnDarkColor.alpha())
               .arg(textDarkColor.red()).arg(textDarkColor.green()).arg(textDarkColor.blue()).arg(textDarkColor.alpha()));
    btn->setStyleSheet(qss.join(""));

    //获取所有按钮的文本集合
    QStringList list;
    foreach (QAbstractButton *btn, btns) {
        list.append(btn->text());
    }

    texts = list.join(";");
}

void ButtonGroup::addFinsh()
{
    //添加末尾拉伸弹簧
    layout->addStretch();
}

void ButtonGroup::setBtnStyle()
{
    //按钮的样式,可以自行拓展比如圆角
    QStringList qss;
    qss.append(QString("QAbstractButton{border:none;background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnNormalColor.red()).arg(btnNormalColor.green()).arg(btnNormalColor.blue()).arg(btnNormalColor.alpha())
               .arg(textNormalColor.red()).arg(textNormalColor.green()).arg(textNormalColor.blue()).arg(textNormalColor.alpha()));
    qss.append(QString("QAbstractButton:hover{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnHoverColor.red()).arg(btnHoverColor.green()).arg(btnHoverColor.blue()).arg(btnHoverColor.alpha())
               .arg(textHoverColor.red()).arg(textHoverColor.green()).arg(textHoverColor.blue()).arg(textHoverColor.alpha()));
    qss.append(QString("QAbstractButton:pressed,QAbstractButton:checked{background:rgba(%1,%2,%3,%4);color:rgba(%5,%6,%7,%8);}")
               .arg(btnDarkColor.red()).arg(btnDarkColor.green()).arg(btnDarkColor.blue()).arg(btnDarkColor.alpha())
               .arg(textDarkColor.red()).arg(textDarkColor.green()).arg(textDarkColor.blue()).arg(textDarkColor.alpha()));

    foreach (QAbstractButton *btn, btns) {
        btn->setStyleSheet(qss.join(""));
    }
}
