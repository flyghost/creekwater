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
#define __version__ "1.0.1"

// # this is frame struct support by uboot
// # ,-----+------+-----+----------+------------+- - - -+-------------,
// # | SOF | TYPE | LEN | SUB_TYPE | HEAD_CKSUM | DATA  | DATA_CKSUM  |
// # |  1  |   1  |  4  |    1     |      4     | ...   |     4       | <- size (bytes)
// # '-----+------+-----+----------+------------+- - - -+-------------'

#define TRS_SYNC                0x73796E63
#define TRS_DEFAULT_ROM_BAUD    57600
#define SOF                     0xA5 // start of a frame

// # message type define
#define M_SYNC                  0x00
#define M_CFG                   0x01
#define M_WRITE                 0x02
#define M_READ                  0x03
#define M_ERASE                 0x04

// #Mesage_subtype define
#define M_SUB_SYNC              0x00
#define M_SUB_BAUD              0x01
#define M_SUB_FLASH             0x02
#define M_SUB_FLASH_ID          0x03
#define M_SUB_MEM               0x04
#define M_SUB_REG               0x05
#define M_SUB_VERSION           0x06

// #response message
#define ACK_OK                  0x00
#define ACK_ERR                 0x01

#define TRS_UBOOT_ADDR   0x0000
#define TRS_APP_ADDR     0x4000
#define TRS_NV_ADDR      0x8000
#define TRS_FRM_TYPE_UBOOT  0x00000001
#define TRS_FRM_TYPE_NV     0x00000002
#define TRS_FRM_TYPE_APP    0x00000003

#define STUB_CODE_BASE          "\
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
                                "

static const quint32 crc32_table[] =
{
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/**
 * Calculate the CRC32 value of a memory buffer.
 *
 * @param crc accumulated CRC32 value, must be 0 on first call
 * @param buf buffer to calculate CRC32 value for
 * @param size bytes in buffer
 *
 * @return calculated CRC32 value
 */
quint32 SerialDownload::crc32(quint32 crc, const void *buf, size_t size)
{
    const quint8 *p;

    p = (const quint8 *)buf;
    crc = crc ^ ~0U;

    while (size--) {
        crc = crc32_table[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
    }

    return crc ^ ~0U;
}
SerialDownload::SerialDownload(QextSerialPort *m_com,Ui_FrameMain *m_ui)
{
    com = m_com;
    ui = m_ui;
    STUB_CODE = QByteArray::fromBase64(STUB_CODE_BASE);
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
        sync_bootrom();
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
    // com->read(2);
}

QByteArray SerialDownload::read(qint64 length)
{
    return com->read(length);
}

bool SerialDownload::command(quint8 cmd_type, quint8 cmd_subtype, quint8 data_content[], quint32 data_length)
{
    if(cmd_subtype ==0 || data_content == nullptr)
    {
        return false;
    }

    quint32 head_cksum;
    quint32 data_cksum;

    QByteArray frame;

    frame.reserve(static_cast<int>(15 + data_length));

    quint32 offset = 0;

    frame[offset++] = static_cast<char>(SOF);
    frame[offset++] = static_cast<char>(cmd_type);
    frame[offset++] = static_cast<char>(data_length >> 24 & 0xff);
    frame[offset++] = static_cast<char>(data_length >> 16 & 0xff);
    frame[offset++] = static_cast<char>(data_length >> 8 & 0xff);
    frame[offset++] = static_cast<char>(data_length >> 0 & 0xff);
    frame[offset++] = static_cast<char>(cmd_subtype);

    head_cksum = crc32(0,frame, 7);
    frame[offset++] = static_cast<char>(head_cksum >> 24 & 0xff);
    frame[offset++] = static_cast<char>(head_cksum >> 16 & 0xff);
    frame[offset++] = static_cast<char>(head_cksum >> 8 & 0xff);
    frame[offset++] = static_cast<char>(head_cksum >> 0 & 0xff);

    for(quint32 i = 0; i < data_length; i++)
    {
        frame[offset++] = data_content[i];
    }

    data_cksum = crc32(0,data_content , data_length);
    frame[offset++] = static_cast<char>(data_cksum >> 24 & 0xff);
    frame[offset++] = static_cast<char>(data_cksum >> 16 & 0xff);
    frame[offset++] = static_cast<char>(data_cksum >> 8 & 0xff);
    frame[offset++] = static_cast<char>(data_cksum >> 0 & 0xff);

    write(frame);

    QByteArray ret = read(1);

    if(ret.at(0) != 0x00)
    {
        frame.clear();
        frame.end();
        return  false;
    }

    return true;

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

bool SerialDownload::sync_bootrom(void)
{
    qDebug() << "start sync bootrom" ;

    bool baudrate_change = false;
    com->close();

    qDebug() << "start sync bootrom2wwwwwwwwwwwwwwwwwwwwwwwww" ;
    if(com->baudRate() != BAUD57600)
    {qDebug() << "start sync bootrom1" ;
        baudrate_change = true;qDebug() << "start sync bootrom2" ;
        com->close();qDebug() << "start sync bootrom3" ;
        com->flush();qDebug() << "start sync bootrom4" ;
        com->setBaudRate(BAUD57600);qDebug() << "start sync bootrom5" ;
        com->open(QIODevice::ReadWrite);qDebug() << "start sync bootrom6" ;
    }
    qDebug() << "start sync bootrom wwwwww" ;
    quint32 offset = 0;
    QByteArray frame;
    frame[offset++] = static_cast<char>(TRS_SYNC >> 24 & 0xff);
    frame[offset++] = static_cast<char>(TRS_SYNC >> 16 & 0xff);
    frame[offset++] = static_cast<char>(TRS_SYNC >> 8 & 0xff);
    frame[offset++] = static_cast<char>(TRS_SYNC >> 0 & 0xff);

    com->flush();

    write(frame);

    QTime t;
    t.start();
    char resp = 1;

    int time_esp = t.elapsed();

    while(resp == 0)
    {
        while(t.elapsed() < time_esp + 100);
        time_esp = t.elapsed();

        QByteArray ret = read(1);
        resp = ret.at(0);
    }

    qDebug() << "sync bootrom succ" ;

    if(baudrate_change)
    {
        com->close();
        com->setBaudRate(static_cast<BaudRateType>(ui->cboxBaudRate->currentText().toInt()));
        com->open(QIODevice::ReadWrite);
    }
}

bool SerialDownload::load_stub()
{
    int seq = 0;
    int written = 0;
    QByteArray image = STUB_CODE;
    QTime t;
    t.start();

    qDebug()<<"will load stub to ram firstly";
    quint32 image_len = static_cast<quint32>(image.length());
    quint32 num_blocks = (image_len + TRS_STUB_BLOCK - 1) / TRS_STUB_BLOCK;

    quint32 offset = 0;
    QByteArray frame;


    frame[offset++] = static_cast<char>(0x01);
    frame[offset++] = 0;
    frame[offset++] = 0;
    frame[offset++] = 0;

    frame[offset++] = 0;
    frame[offset++] = 0;
    frame[offset++] = 0;
    frame[offset++] = 0;

    frame[offset++] = static_cast<char>(image_len >> 24 & 0xff);
    frame[offset++] = static_cast<char>(image_len >> 16 & 0xff);
    frame[offset++] = static_cast<char>(image_len >> 8 & 0xff);
    frame[offset++] = static_cast<char>(image_len >> 0 & 0xff);

    com->write(frame);

    char resp = 0;

    int time_esp = t.elapsed();

    while(resp == 0)
    {
        while(t.elapsed() < time_esp + 1000);
        time_esp = t.elapsed();

        QByteArray ret = read(1);
        resp = ret.at(0);
    }

    while (image.length() > 0)
    {
        //print('\rWriting at 0x%08x... (%d %%)' % (seq * self.TRS_STUB_BLOCK, 100 * (seq + 1) / num_blocks),end='');

        qDebug()<<"Writing at 0x%08x..." << seq * TRS_STUB_BLOCK << " " << 100 * (seq + 1) / num_blocks << "%";

    }

}













