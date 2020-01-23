#include "frameterminal.h"


FrameTerminal::FrameTerminal(Ui_FrameMain *m_ui)
{
    ui = m_ui;


//    cmd = new QProcess(this);
//    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
//    connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
//    ui->pushButton->setShortcut(Qt::Key_Return);//将字母区回车键与发送按钮绑定在一起
//    cmd->start("bash");
//    cmd->waitForStarted();
}

//MainWindow::~MainWindow()
//{
//        if(cmd)
//        {
//            cmd->terminate();
//            cmd->waitForFinished();
//        }
//    delete ui;
//}

//void MainWindow::on_readoutput()
//{
//    ui->textEdit->append(cmd->readAllStandardOutput().data());
//}
//#include <QDebug>
//void MainWindow::on_readerror()
//{
//    //QMessageBox::information(0, "Error", cmd->readAllStandardError().data());
//    qDebug()<< cmd->readAllStandardError().data();
//    ui->textEdit->append(cmd->readAllStandardError().data());
//}


//void MainWindow::on_pushButton_clicked()
//{
//    cmd->write(ui->lineEdit->text().toLocal8Bit() + '\n');
//    ui->lineEdit->setText("");
//    cmd->write("pwd\n");

//}
