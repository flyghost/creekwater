#include "frametop.h"

#include <QApplication>

#include "CreekWater/code/core_app/appinit.h"
#include <QTextCodec>
#include <QFile>
//修改::
#define QSS_LOCATION ":/css/CreekWater/uisource/css/myframeset.css"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    QFile file(QSS_LOCATION);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        //QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor("#444444")));
        qApp->setStyleSheet(qss);
        file.close();
    }



    a.setFont(QFont("Microsoft Yahei", 9));
    AppInit::Instance()->start();

    FrameTop w;
    w.show();


    return a.exec();
}
