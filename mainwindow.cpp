#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    {
        QString base_dir=qApp->applicationDirPath()+"/sav";
        QDir *temp = new QDir;
        bool exist = temp->exists(base_dir);
        if(!exist)
        {
            temp->mkdir(base_dir);
        }
    }
    connect(&refTimer,SIGNAL(timeout()),this,SLOT(refState()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
    this,
    tr("打开文件"),
    NULL,// ".",
    tr("*.csv"));
    ui->lineEdit->setText(fileName);

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    startTime=QTime::currentTime();


    worker.workdir=ui->lineEdit->text();
    ui->label->setText("正在加载文件...");
    worker.start();
    refTimer.start(100);
}
void MainWindow::refState()
{


    int ms= startTime.msecsTo(QTime::currentTime()) ;
    int s=ms/1000;
    int m=s/60;
    int h=m/60;
    QString msg;
    msg= QString::number(h)+"小时"+QString::number(m%60)+"分"+QString::number(s%60)+"秒"+QString::number(ms%1000)+"毫秒";
    if(worker.isFinished())
    {
        msg+="\r\n总共处理了"+QString::number(worker.countAll)+"行";
        msg+="\r\n平均速度"+QString::number(worker.countAll/(ms*1.0)*1000.0)+"行/秒";
        refTimer.stop();
        ui->pushButton->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->pushButton_2->setEnabled(true);

    }
    else
    {
        if(worker.countSec==0)
        {
            msg+="  正在保存到文件....";
        }
        else
        {
            msg+="  当前效率"+QString::number((worker.countSec*10.0))+"行/秒";
            worker.countSec=0;
        }

    }
    if(worker.countAll>0)
    {
        ui->label->setText(msg);
    }


}
