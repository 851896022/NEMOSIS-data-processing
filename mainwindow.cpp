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

    QString str("hello world");
    QByteArray ba("hello world");
    qDebug()<<sizeof(str)<<sizeof(ba);
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
        msg+="  总共处理了"+QString::number(worker.countAll)+"行";
        refTimer.stop();

    }
    else
    {
        msg+="  当前效率"+QString::number(worker.countSec*10)+"行/秒";
        worker.countSec=0;
    }
    if(worker.countAll>0)
    {
        ui->label->setText(msg);
    }

}
