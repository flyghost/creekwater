#ifndef COMCONFIG_H
#define COMCONFIG_H

class QString;

class ComConfig
{
public:
    static QString PortName;            //串口号
    static int BaudRate;                //波特率
    static int DataBit;                 //数据位
    static QString Parity;              //校验位
    static double StopBit;              //停止位

    static bool HexSend;                //16进制发送
    static bool HexReceive;             //16进制接收
    static bool Debug;                  //模拟设备
    static bool AutoClear;              //自动清空

    static bool AutoSend;               //自动发送
    static int SendInterval;            //自动发送间隔
    static bool AutoSave;               //自动保存
    static int SaveInterval;            //自动保存间隔

    static QString SendFileName;        //发送配置文件名
    static QString DeviceFileName;      //模拟设备数据文件名

    static QString Mode;                //转换模式
    static QString ServerIP;            //服务器IP
    static int ServerPort;              //服务器端口
    static int ListenPort;              //监听端口
    static int SleepTime;               //延时时间
    static bool AutoConnect;            //自动重连

    static void ReadConfig();           //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();          //写入配置文件,在更改配置文件程序关闭时调用
    static void NewConfig();            //以初始值新建配置文件
    static bool CheckConfig();          //校验配置文件
    static void WriteError(QString str);//写入错误信息
    static void NewDir(QString dirName);//新建目录

};

#endif // COMCONFIG_H
