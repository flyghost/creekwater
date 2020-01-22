#include "comConfig.h"
//#include "myhelper.h"
#include <QtCore>
#include <QtGui>
#include <QtSql/QSql>
#include <QtNetwork/QtNetwork>
#include <QtXml/QtXml>
#include <QString>


#define TIMEMS qPrintable (QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME qPrintable (QTime::currentTime().toString("HH:mm:ss"))
#define QDATE qPrintable (QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME qPrintable (QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))


#define AppName "Com"
#define AppPath qApp->applicationDirPath()

QString ComConfig::PortName = "COM1";
int ComConfig::BaudRate = 9600;
int ComConfig::DataBit = 8;
QString ComConfig::Parity = "NO";
double ComConfig::StopBit = 1;

bool ComConfig::HexSend = false;
bool ComConfig::HexReceive = false;
bool ComConfig::Debug = false;
bool ComConfig::AutoClear = false;

bool ComConfig::AutoSend = false;
int ComConfig::SendInterval = 1000;
bool ComConfig::AutoSave = false;
int ComConfig::SaveInterval = 5000;

QString ComConfig::SendFileName = "send.txt";
QString ComConfig::DeviceFileName = "device.txt";

QString ComConfig::Mode = "Tcp_Client";
QString ComConfig::ServerIP = "127.0.0.1";
int ComConfig::ServerPort = 6000;
int ComConfig::ListenPort = 6000;
int ComConfig::SleepTime = 100;
bool ComConfig::AutoConnect = true;

void ComConfig::ReadConfig()
{
    if (!CheckConfig()) {
        return;
    }

    QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);
    QSettings set(fileName, QSettings::IniFormat);

    set.beginGroup("ComConfig");
    ComConfig::PortName = set.value("PortName").toString();
    ComConfig::BaudRate = set.value("BaudRate").toInt();
    ComConfig::DataBit = set.value("DataBit").toInt();
    ComConfig::Parity = set.value("Parity").toString();
    ComConfig::StopBit = set.value("StopBit").toInt();

    ComConfig::HexSend = set.value("HexSend").toBool();
    ComConfig::HexReceive = set.value("HexReceive").toBool();
    ComConfig::Debug = set.value("Debug").toBool();
    ComConfig::AutoClear = set.value("AutoClear").toBool();

    ComConfig::AutoSend = set.value("AutoSend").toBool();
    ComConfig::SendInterval = set.value("SendInterval").toInt();
    ComConfig::AutoSave = set.value("AutoSave").toBool();
    ComConfig::SaveInterval = set.value("SaveInterval").toInt();

    ComConfig::SendFileName = set.value("SendFileName").toString();
    ComConfig::DeviceFileName = set.value("DeviceFileName").toString();
    set.endGroup();

    set.beginGroup("NetConfig");
    ComConfig::Mode = set.value("Mode").toString();
    ComConfig::ServerIP = set.value("ServerIP").toString();
    ComConfig::ServerPort = set.value("ServerPort").toInt();
    ComConfig::ListenPort = set.value("ListenPort").toInt();
    ComConfig::SleepTime = set.value("SleepTime").toInt();
    ComConfig::AutoConnect = set.value("AutoConnect").toBool();
    set.endGroup();
}

void ComConfig::WriteConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);
    QSettings set(fileName, QSettings::IniFormat);

    set.beginGroup("ComConfig");
    set.setValue("PortName", ComConfig::PortName);
    set.setValue("BaudRate", ComConfig::BaudRate);
    set.setValue("DataBit", ComConfig::DataBit);
    set.setValue("Parity", ComConfig::Parity);
    set.setValue("StopBit", ComConfig::StopBit);

    set.setValue("HexSend", ComConfig::HexSend);
    set.setValue("HexReceive", ComConfig::HexReceive);
    set.setValue("Debug", ComConfig::Debug);
    set.setValue("AutoClear", ComConfig::AutoClear);

    set.setValue("AutoSend", ComConfig::AutoSend);
    set.setValue("SendInterval", ComConfig::SendInterval);
    set.setValue("AutoSave", ComConfig::AutoSave);
    set.setValue("SaveInterval", ComConfig::SaveInterval);

    set.setValue("SendFileName", ComConfig::SendFileName);
    set.setValue("DeviceFileName", ComConfig::DeviceFileName);
    set.endGroup();

    set.beginGroup("NetConfig");
    set.setValue("Mode", ComConfig::Mode);
    set.setValue("ServerIP", ComConfig::ServerIP);
    set.setValue("ServerPort", ComConfig::ServerPort);
    set.setValue("ListenPort", ComConfig::ListenPort);
    set.setValue("SleepTime", ComConfig::SleepTime);
    set.setValue("AutoConnect", ComConfig::AutoConnect);
    set.endGroup();
}

void ComConfig::NewConfig()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    ComConfig::Parity = ComConfig::Parity.toLatin1();
#endif
    WriteConfig();
}

bool ComConfig::CheckConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(AppPath).arg(AppName);

    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(fileName);

    if (file.size() == 0) {
        NewConfig();
        return false;
    }

    //如果配置文件不完整,则以初始值继续运行,并生成配置文件
    if (file.open(QFile::ReadOnly)) {
        bool ok = true;

        while (!file.atEnd()) {
            QString line = file.readLine();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            QStringList list = line.split("=");

            if (list.count() == 2) {
                if (list.at(1) == "") {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok) {
            NewConfig();
            return false;
        }
    } else {
        NewConfig();
        return false;
    }

    return true;
}

void ComConfig::WriteError(QString str)
{
    QString fileName = QString("%1/%2_Error_%3.txt").arg(AppPath).arg(AppName).arg(QDATE);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << DATETIME << "  " << str << "\n";
}

void ComConfig::NewDir(QString dirName)
{
    //如果路径中包含斜杠字符则说明是绝对路径
    //linux系统路径字符带有 /  windows系统 路径字符带有 :/
    if (!dirName.startsWith("/") && !dirName.contains(":/")) {
        dirName = QString("%1/%2").arg(AppPath).arg(dirName);
    }

    QDir dir(dirName);

    if (!dir.exists()) {
        dir.mkpath(dirName);
    }
}
