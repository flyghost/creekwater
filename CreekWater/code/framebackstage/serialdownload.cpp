#include "serialdownload.h"
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include <QFormLayout>
#include <QFileDialog>

//SerialDownload::SerialDownload(QextSerialPort *com)
//{
//    m_com = com;
//}


//void SerialDownload::write(QByteArray packet)
//{
//    m_com->write(packet);
//}

//QByteArray SerialDownload::read()
//{
////    if(m_com->bytesAvailable() >= length)
//    return m_com->readAll();
//}

//void SerialDownload::send_command(unsigned char cmd_type, unsigned char cmd_subtype, QString data_content)
//{
//    if(cmd_type != 0 && cmd_subtype != 0)
//    {
//        struct
//        {
//            SOF;

//        }struct_1;
//    }
//}



SerialDownload::SerialDownload(QextSerialPort *m_com,Ui_FrameMain *m_ui)
{
    com = m_com;
    ui = m_ui;
    STUB_CODE = QByteArray::fromBase64("\
                                 AiYgGAAAAAAAAAAAAAAJbAAAAEAAAcAAAAAAAAAAAABib290LXZlcnNpb24tZGVidWcAAAAAAAAA\
                                 AAAAAAAAAEXRyWJkAIACRhAQAEAgBALCBIQAQg4AIUXyP/BJAAA91QCSADv//rxRz4AIRAHJZEQh\
                                 yWSKQIQgSf8oblH+f/g7//6E3Z47//68Uc+ACEQQAFD+DEn/OwtR/n/4O//+hN2eO//+vFHPgAhG\
                                 EAYBBACCA1gAIwAUAIIDSf860UkAAByEJUQAAP9J/zoVUf5/+Dv//oTdnjv//rxRz4AISf//w0n/\
                                 /+BJAAFqhABR/n/4O//+hN2eO//+vFHPgAhGEAYBBACCA1gAABAUAIIDhEBEEOEARgAGAkn/OOiE\
                                 gIRghECEI0YABgJJ/zkDhGGEQYQhRgAGAkn/OR5R/n/4O//+hN2eOm+evFHPgBCA4IDBRgAGAgQA\
                                 AA2WBMgIRAAAZEn//5PGDo7B1fRGAAYCBAAACK44hABR/n/wOm+ehN2ehB/V+jpvorxRz4AU7/yB\
                                 AIDhhMDVCEYABgJJ/zkWOAQYCIzB4MfoB0YABgJJ/zkJwPzV8lH+f+w6b6KE3Z47//68Uc+ACIBB\
                                 gCBGAAYCSf844lH+f/g7//6E3Z47//48Uc+ABO/8RiBMS1ghBABAIQRXQAEAF0YgBgIEMQALWEGA\
                                 gBRBAAuoVZZAFBEACJIIlgAUAQAJZjGAgBQxAAtR/n/8O//+BN2eO//+vFHPgAhGEAYBBCCDK1gh\
                                 AAQUIIMr+kUUIIIBhChJ///KUf5/+Dv//oTdnjv//rxRz4AI7/iEIBAef/eEIcgKUA5/90n//6hR\
                                 /n/4O//+hN2ehAEQDn/3UA5/90n//5zV9DpvmrxRz4AM79yEwNUFAA5/2cgSjMHky+gRhD9QDn/Y\
                                 iAZJ//9LTgUAMgAOf9haAKXwhMDV8ITA1e5Qbn/kUB5/2IBBOwFEBIAGOwBEJKTQrMCmkq6ChEeE\
                                 AEn/OrwALn/rBB5/+0BQoAj/V9gRhCVQDn/QSf//QoQASf//qIQAUf5/9DpvmoTdnoQf1fqEH9X4\
                                 Om+ivFHPgBTv5IEAgOGEwNUCjMHky+gPhD9QDn/QiAZJ//8DTgUAOAAOf9BaAKXzhMDV8FBuf9xQ\
                                 Hn/QgEE7AUQEgAY7AEQkpNCswKaSroKER4QASf86dgAuf+MEHn/5QFCgCP9X2BkADn/dEAQAAAAO\
                                 f+IQBAABAh5/7wIOf/BAAEAI/g+2B4QAUf5/7DpvooTdnoQf1fqEH9X4Om+avFHPgAxR/+/kRCAQ\
                                 DIQgUA5v5En/JsKEABQOe/hJ//9ZyP5JAAJuhAASDnfu1QaEJVAOb+RJ//7JUB5v4FAOb9xJ//+Q\
                                 yPpEIBAMhCBQDm/kSf8mowAOb9zA61oAARdaAAJNWggDBEgAAJhaCAQESAABEFoIBeMEHnv4jCRQ\
                                 Dm/kSf/+o4QA3SAADm/dWgABCVoAAi9EAAD/Sf//ANXOBB57+IwkUA5v5En//o+EQVAeb+SEAEn/\
                                 OfZQHm/lOhCEAEwAgAdEAAD/Sf/+6NW2hABJ//7kRAALuEn//fgAHm/kRADhAP4MSf/+wkj//6eE\
                                 AEn//tRI//+iAA5v3VoAAgxaAAQlWgAFN0QAAP9J//7GSP//lAQee/iMJFAOb+RJ//5UBC57+lAe\
                                 b+wEDnv5SQABV8AHRAAA/0n//rBI//9+hABJ//6rSP//eQQee/iMJFAOb+RJ//45BC57+lAeb+wE\
                                 Dnv5Sf8lq4QASf/+l0j//2UEHnv4jCRQDm/kSf/+JQQOe/kEHnv6OhAEIIQASf/+hUj//1MADm/d\
                                 WgACFFoABCxaAAVEWggDBEgAAFdaCAYESAAAZEQAAP9J//5vSP//PQQee/iMJFAOb+RJ//39BG57\
                                 +oBGUB5v7AQOe/lJAAGAhABJ//5agCZQDm/sSf/+CUj//yMEHnv4jCRQDm/kSf/94wRue/qARgQe\
                                 e/lQDm/sSf8lVIQASf/+QIAmUA5v7En//e9I//8JBB57+IwkUA5v5En//ckEDnv5OgAAABQOe/qE\
                                 AEn//imEJFAOb+hJ//3YSP/+8kn/Nw5AACAIkggUDnv2hABJ//4YhCRQDm/YSf/9x0j//uGEAEn/\
                                 /g6EJUQByWRJ//29SP/+1wAOb91aAAIIRAAA/0n//f9I//7NBB57+IwkUA5v5En//Y0EDnv5BB57\
                                 +loX/wtJAADYwA1EAAD/Sf/96Uj//rdEAAD/Sf/940j//rGEAEn//d5I//6sOm+mvFHPgBiA4IDC\
                                 gQMEk4ANVJSAAU6T//wEA4AMWAAABhQDgAwUE4AKSf82s0AAIAhAUCAJRgABRIwL0BtQBH//QAAw\
                                 CEYQAf/+DkYWGAD+DxQDgAhEAAAyFAOACVQzAAPLMEBECAlU9AAD6BqMgdUYUAR//0AAMAhGEAH/\
                                 /g5GFxgA/g8UA4AIRAAAOBQDgAnV5oBGohEUA4ALjGGAwuJk6CYEA4ANRhAIAP4OyPvV8gQDgA1G\
                                 EAgA/g7I+xQzgAtOggAWhATiCEAEPBqAoIBpgAniBejugEYIEQABlQNAEJAM/s+PAYwBgMLV9FH+\
                                 f+g6b6aE3Z46b7K8Uc+AJO/8gWCBgYFCVIAA/1KEAQDjAukCgQKBK9UkVAMAAsAtQCSsAYBoiEyA\
                                 KUYABgpJ//9pi0iJKFwFAQHIDUSAAQCE4Fp3/wtJ/zY/gMCWBMAFjOHV+IEK1fWWNMgVToIAD4Tg\
                                 Wnf/3En/NkhJ/zYtgMCWDsjUjOHV9oQfUf5/3DpvsoTdnoQf1fo6b6q8Uc+AHO/8gUBQEI//QJCw\
                                 CYUA1RZUAwACwCdABDAIiApJ/zY6hOBad/8JSf82B4DAlgTAA4zh1fiWNMgYjQHjCegNhOBad//o\
                                 Sf82EUn/NfaAwJYOyOCM4dX2hABR/n/kOm+qhN2ehB/V+oQe1fg7//68Uc+ACIBhRhAMAIgggANJ\
                                 /yPlUf5/+Dv//oTdnjpvmrxRz4AM7/yEwFpn/wpJ/zXmSf81y5YOyAOMwdX3Sf81q0BQIAiSqEYQ\
                                 AUZQEICF0SZGEAFUUBCAodE5RgAGCkYUEAAUEAAIRBAAMRQQAAlGAAYKBAAADUYQCAD+Dsj5RgAG\
                                 CoQiFBAAC4TAWmf/N0n/NZyWBMAyjMHV+UYABgpGFBABFBAACIQhFBAACUYABgoEAAANRhAIAP4O\
                                 yPlGAAYKRBACABQQAAvV4EYABgpGFBABFBAACIQhFBAACUYABgoEAAANRhAIAP4OyPlGAAYKhCIU\
                                 EAAL1clR/n/0Om+ahN2eAAAwLjAuMQAAAA==\
                                 ");
//     qDebug()<< STUB_CODE;

    connect(ui->downloadPushButton, SIGNAL(clicked()), this, SLOT(downloadButtonClicked()));

    buttonEditInit();

}

void SerialDownload::buttonEditInit()
{
    // 按钮显示文字
//    buttonEdit1 = new ButtonEdit("打开");
    // 按钮显示图标
    buttonEdit1 = new ButtonEdit(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    buttonEdit2 = new ButtonEdit(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    buttonEdit3 = new ButtonEdit(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    buttonEdit4 = new ButtonEdit(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));

    QObject::connect(buttonEdit1,  &ButtonEdit::buttonClicked, this, &SerialDownload::path_lineEdit1_Clicked);
    QObject::connect(buttonEdit2,  &ButtonEdit::buttonClicked, this, &SerialDownload::path_lineEdit2_Clicked);
    QObject::connect(buttonEdit3,  &ButtonEdit::buttonClicked, this, &SerialDownload::path_lineEdit3_Clicked);
    QObject::connect(buttonEdit4,  &ButtonEdit::buttonClicked, this, &SerialDownload::path_lineEdit3_Clicked);

    auto layout = new QFormLayout;
    layout->addRow("", buttonEdit1);
    layout->addRow("", buttonEdit2);
    layout->addRow("", buttonEdit3);
    layout->addRow("", buttonEdit4);
    ui->buttonEditGroupWidget->setLayout(layout);
}

void SerialDownload::downloadButtonClicked()
{
    if(ui->download_checkbox1->isChecked())
    {
        if(ui->addr_lineEdit1->text() == nullptr || buttonEdit1->text() == nullptr)
        {
            ui->txtMain->append("配置错误!!!");
            return;
        }

        ui->txtMain->append(QString::number(ui->addr_lineEdit1->text().toInt(nullptr,16)));
    }

    if(ui->download_checkbox2->isChecked())
    {
        if(ui->addr_lineEdit2->text() == nullptr || buttonEdit2->text() == nullptr)
        {
            ui->txtMain->append("download config error !!!");
            return;
        }

        ui->txtMain->append(QString::number(ui->addr_lineEdit2->text().toInt(nullptr,16)));
    }

    if(ui->download_checkbox3->isChecked())
    {
        if(ui->addr_lineEdit3->text() == nullptr || buttonEdit3->text() == nullptr)
        {
            ui->txtMain->append("download config error !!!");
            return;
        }

        ui->txtMain->append(QString::number(ui->addr_lineEdit3->text().toInt(nullptr,16)));
    }

    if(ui->download_checkbox4->isChecked())
    {
        if(ui->addr_lineEdit4->text() == nullptr || buttonEdit4->text() == nullptr)
        {
            ui->txtMain->append("download config error !!!");
            return;
        }

        ui->txtMain->append(QString::number(ui->addr_lineEdit4->text().toInt(nullptr,16)));
    }
}

QString SerialDownload::get_path()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("选中文件"));
    //设置默认文件路径
    fileDialog->setDirectory("/home");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("File(*.*)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    return fileNames.at(0);
}

void SerialDownload::path_lineEdit1_Clicked()
{
    // 方法一
//    bin_path = get_path();
    // 方法二
    QString bin_path=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择bin文件"),
                                                  qApp->applicationDirPath(),
                                                  QString::fromLocal8Bit("bin File(*.bin)"));
    buttonEdit1->setText(bin_path);
}

void SerialDownload::path_lineEdit2_Clicked()
{
//    bin_path = get_path();
    QString bin_path=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择bin文件"),
                                                  qApp->applicationDirPath(),
                                                  QString::fromLocal8Bit("bin File(*.bin)"));
    buttonEdit2->setText(bin_path);
}

void SerialDownload::path_lineEdit3_Clicked()
{
//    bin_path = get_path();
    QString bin_path=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择bin文件"),
                                                  qApp->applicationDirPath(),
                                                  QString::fromLocal8Bit("bin File(*.bin)"));
    buttonEdit3->setText(bin_path);
}

void SerialDownload::path_lineEdit4_Clicked()
{
//    bin_path = get_path();
    QString bin_path=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择bin文件"),
                                                  qApp->applicationDirPath(),
                                                  QString::fromLocal8Bit("bin File(*.bin)"));
    buttonEdit4->setText(bin_path);
}

qint32 SerialDownload::str_to_hex(QString str)
{
    QByteArray temp = str.toLatin1().toHex();
    return  temp.toInt(nullptr,16);
}

bool SerialDownload::bin_handle_unpack(QString path,
                                       qint32 *type,
                                       qint32 *bin_addr,
                                       qint32 *image_length,
                                       QByteArray *image)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        ui->txtMain->setText(file.errorString());//文件打开错误显示错误信息
        return false;
    }
    *image = file.readAll();
    file.close();

    if((*image).length() < 4)
    {
        return false;
    }

    qint32 oneb = str_to_hex(TRS_ALLINONE);



}

// 打开bin文件
bool SerialDownload::bin_handle_read(QString path,
                                     QString addr,
                                     qint32 *type,
                                     qint32 *bin_addr,
                                     qint32 *image_length,
                                     QByteArray *image)
{
    *bin_addr = str_to_hex(addr);
    switch (*bin_addr)
    {
    case TRS_UBOOT_ADDR:
        *type = TRS_FRM_TYPE_UBOOT;
        break;
    case TRS_APP_ADDR:
        *type = TRS_FRM_TYPE_APP;
        break;
    case TRS_NV_ADDR:
        *type = TRS_FRM_TYPE_NV;
        break;
    default :
        *type = TRS_FRM_TYPE_NV;
        break;

    }

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        ui->txtMain->setText(file.errorString());//文件打开错误显示错误信息
        return false;
    }


    *image = file.readAll();
    ui->txtMain->append(QString::fromLocal8Bit("打开文件："));
    ui->txtMain->append(path);
    file.close();

    *image_length = (*image).size();//计算长度

    return true;

}

void SerialDownload::write(QByteArray bytes)
{
    com->write(bytes);
    com->read(2);
}

QByteArray SerialDownload::read(qint64 length)
{
    return com->read(length);
}

void SerialDownload::send_command(unsigned char cmd_type, unsigned char cmd_subtype, QByteArray data_content)
{
    if(cmd_subtype ==0 || data_content == nullptr)
    {
        return;
    }

    struct dd
    {
        unsigned char a;
        unsigned char b;
        unsigned int c;
        unsigned char d;
    }hdr;
    hdr.a = SOF;
    hdr.b = cmd_type;
    hdr.c = static_cast<int>(data_content.length());
    hdr.d = cmd_subtype;

    QByteArray cmd;
    memcpy(&cmd,&hdr,sizeof (hdr));

    //qDebug() << cmd.at(0) << cmd.at(1) << cmd.at(2) << cmd.at(3) << cmd.at(4) << cmd.at(5) << cmd.at(6) << cmd.at(7);
}

//char TRS::receive_response()
//{
//    char data;
//    com->read(&data,1);
//    return data;
//}
//bool TRS::sync_bootrom()
//{
//    com->flush();
//    retries = 100;

//    while(retries)
//    {
//        QByteArray array;

//        array[0] = 0x63;
//        array[1] = 0x6E;
//        array[2] = 0x79;
//        array[3] = 0x73;


//        com->write(array);

//        qDebug()<<"connecting....";

//        QTime t;
//        t.start();
//        while(t.elapsed()<1000);

//        char resp = receive_response();

//        if(resp ==0x01)
//            break;

//    }

//    if(retries <= 0)
//    {
//        qDebug()<<"connecting error....";
//        return false;
//    }

//    return true;

//}

//bool TRS::load_stub()
//{
//    int seq = 0;
//    int written = 0;
//    QByteArray image = STUB_CODE;
//    QTime t;
//    t.start();

//    qDebug()<<"will load stub to ram firstly";
//    int num_blocks = (image.length() + TRS_STUB_BLOCK - 1); // self.TRS_STUB_BLOCK

//    #pragma pack(push, 1)
//    struct
//    {
//        unsigned int a;
//        unsigned int b;
//        unsigned int c;
//    }image_config_t;
//    #pragma pack(pop)

//    image_config_t.a = 0x00000001;
//    image_config_t.b = 0;
//    image_config_t.c =static_cast<unsigned int>(image.length());


//    QByteArray image_config;
//    image_config.append(reinterpret_cast<char *>(&image_config_t), sizeof (image_config_t));

//    com->write(image_config);

//    char resp = 0;

//    int time_esp = t.elapsed();

//    while(resp == 0)
//    {
//        while(t.elapsed() < time_esp + 1000);
//        time_esp = t.elapsed();
//        resp = receive_response();

//    }

//    while (image.length() > 0)
//    {
//        //print('\rWriting at 0x%08x... (%d %%)' % (seq * self.TRS_STUB_BLOCK, 100 * (seq + 1) / num_blocks),end='');

//        qDebug()<<"Writing at 0x%08x..." << seq * TRS_STUB_BLOCK << " " << 100 * (seq + 1) / num_blocks << "%";

//    }

//}













