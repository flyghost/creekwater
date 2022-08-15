#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QIcon>

class ButtonEdit: public QLineEdit {
    Q_OBJECT
public:
    explicit ButtonEdit(const QString &btnText, QWidget *parent = nullptr);
    explicit ButtonEdit(const QIcon &icon, QWidget *parent = nullptr);
    ~ButtonEdit() override = default;

private:
    // 设置文本按钮或图标按钮的大小和外观
    void setTextButton();
    void setIconButton();
    // 将按钮添加到edit
    void addButton();

    QPushButton *button;

Q_SIGNALS:
    void buttonClicked(bool);
};

// 按钮和输入内容的边距
constexpr int buttonMargin = 10;

#endif // BUTTONEDIT_H
