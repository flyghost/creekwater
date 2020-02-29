#include "buttonedit.h"
#include <QHBoxLayout>

ButtonEdit::ButtonEdit(const QString &btnText, QWidget *parent)
 : QLineEdit(parent)
{
    button = new QPushButton(btnText);
    setTextButton();
    addButton();
}

ButtonEdit::ButtonEdit(const QIcon &icon, QWidget *parent)
 : QLineEdit(parent)
{
    button = new QPushButton;
    button->setIcon(icon);
    setIconButton();
    addButton();
}

void ButtonEdit::addButton() {
    connect(button,
            &QPushButton::clicked,
            this,
            &ButtonEdit::buttonClicked);
    // 按钮已经是edit的一部分了，不应该再能被单独聚焦，否则可能导致误触
    button->setFocusPolicy(Qt::NoFocus);
    // 设置鼠标，否则点击按钮时仍然会显示输入内容时的鼠标图标
    button->setCursor(Qt::ArrowCursor);

    auto btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(button);
    // 设置组件右对齐，按钮会显示在edit的右侧
    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(btnLayout);
    // 设置输入区域的范围，从edit的最左到按钮的最左(包含了按钮设置的buttonMargin)
    setTextMargins(0, 0, button->width(), 0);
}

// 帮助函数，设置按钮的width，大小策略为fixed，不可放大或缩小
static void setButtonSize(QPushButton *button, int width) {
    auto policy = button->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    button->setSizePolicy(policy);
    // 固定宽度，加上边距
    button->setFixedWidth(width + buttonMargin*2);
}

void ButtonEdit::setTextButton() {
    if (!button) {
        return;
    }

    // 获得当前字体下文本内容的像素宽度
    auto width = QWidget::fontMetrics().width(button->text());
    setButtonSize(button, width);
}

void ButtonEdit::setIconButton() {
    if (!button) {
        return;
    }

    // 获取图标的width简单得多
    auto width = button->iconSize().width();
    setButtonSize(button, width);
    // 设置背景和边框在非点击时不可见
    button->setFlat(true);
}
