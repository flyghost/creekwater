#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QSystemTrayIcon>

class Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent);


private:
    //Ui::MainWindow *ui;
    QWidget * cenWidget;
    QSystemTrayIcon *myTrayIcon;

    QTimer * timer;
    QLabel * label1;
    QLabel * label2;
    QLabel * label3;
    QLabel * label4;
    QLabel * label5;
    QLabel * label6;
    QLabel * labelDot1;
    QLabel * labelDot2;
    QStringList listPath;



private:
    void intiTime();

public slots:
    void updateTime();
};

#endif // CLOCK_H
