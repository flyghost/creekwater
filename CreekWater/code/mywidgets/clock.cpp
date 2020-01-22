#include "clock.h"
#include <QHBoxLayout>
#include <QDateTime>


Clock::Clock(QWidget *parent)
{
    //cenWidget = new QWidget();

    cenWidget = parent;

    //parent->setCentralWidget(cenWidget);
    //this->setWindowTitle("闹钟");
//    this->setWindowFlags(this->windowFlags() | Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    cenWidget->setAttribute(Qt::WA_TranslucentBackground);
//    cenWidget->setStyleSheet("background-image:url(:/images/bg.png)");
    //cenWidget->setFixedSize(450,100);

    parent->setStyleSheet("background-image:url(:/image/CreekWater/uisource/images/bg.png)");

    intiTime();
    //QTimer
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}



//Clock::~Clock()
//{
//    myTrayIcon->hide();
//    delete ui;
//}

void Clock::intiTime()
{
    //初始化图片路径
    listPath.append(":/image/CreekWater/uisource/images/0.png");
    listPath.append(":/image/CreekWater/uisource/images/1.png");
    listPath.append(":/image/CreekWater/uisource/images/2.png");
    listPath.append(":/image/CreekWater/uisource/images/3.png");
    listPath.append(":/image/CreekWater/uisource/images/4.png");
    listPath.append(":/image/CreekWater/uisource/images/5.png");
    listPath.append(":/image/CreekWater/uisource/images/6.png");
    listPath.append(":/image/CreekWater/uisource/images/7.png");
    listPath.append(":/image/CreekWater/uisource/images/8.png");
    listPath.append(":/image/CreekWater/uisource/images/9.png");


    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    label4 = new QLabel(this);
    label5 = new QLabel(this);
    label6 = new QLabel(this);
    labelDot1 = new QLabel(this);
    labelDot2 = new QLabel(this);


    label1->setPixmap(QPixmap(listPath[0]));
    label2->setPixmap(QPixmap(listPath[0]));
    label3->setPixmap(QPixmap(listPath[0]));
    label4->setPixmap(QPixmap(listPath[0]));
    label5->setPixmap(QPixmap(listPath[0]));
    label6->setPixmap(QPixmap(listPath[0]));
    labelDot1->setPixmap(QPixmap(":/image/CreekWater/uisource/images/dot.png"));
    labelDot2->setPixmap(QPixmap(":/image/CreekWater/uisource/images/dot.png"));

    QHBoxLayout * hLayout = new QHBoxLayout();
    hLayout->addWidget(label1);
    hLayout->addWidget(label2);
    hLayout->addWidget(labelDot1);
    hLayout->addWidget(label3);
    hLayout->addWidget(label4);
    hLayout->addWidget(labelDot2);
    hLayout->addWidget(label5);
    hLayout->addWidget(label6);
    hLayout->setSpacing(0);
    hLayout->setMargin(0);

    cenWidget->setLayout(hLayout);
}

void Clock::updateTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();

    //QDate date = dateTime.date();
    QTime time = dateTime.time();
    //checkClock(time.toString("hh:mm:ss"));

    int hour = time.hour();
    int minute = time.minute();
    int second = time.second();

    int hour1 = hour / 10;
    int hour2 = hour % 10;
    int minute1 = minute / 10;
    int minute2 = minute % 10;
    int second1 = second / 10;
    int second2 = second % 10;

    label1->setPixmap(QPixmap(listPath[hour1]));
    label2->setPixmap(QPixmap(listPath[hour2]));
    label3->setPixmap(QPixmap(listPath[minute1]));
    label4->setPixmap(QPixmap(listPath[minute2]));
    label5->setPixmap(QPixmap(listPath[second1]));
    label6->setPixmap(QPixmap(listPath[second2]));
}
