#include "worker.h"
#include "QDir"
#include <QDebug>
Worker::Worker(QThread *parent) : QThread(parent)
{

}
void Worker::run()
{
    loadFile();
    finishedData=new QList<DataBase*>;
    while(!data.empty())
    {
        QString  tmp=data.first();
        data.removeFirst();
        QStringList list=tmp.split(",");
        if(list.count()>=7)
        {
            QString filename=list.at(5);
            filename.remove("/");
            QString filedata=list.at(4)+","+list.at(6)+"\r\n";
            {
            int i=0;

            for(i=0;i<=finishedData->count();i++)
            {
                if(i==finishedData->count())
                {
                    DataBase * base=new DataBase;
                    base->fileName=filename;
                    finishedData->append(base);
                    qDebug()<<"add"<<base->fileName<<"count"<<finishedData->count();
                    break;
                }
                if(finishedData->at(i)->fileName==filename)
                {
                    break;
                }
            }
            finishedData->at(i)->fileData.append(filedata);
            }


            countAll++;
            countSec++;
        }

    }
    saveFile();

}
void Worker::loadFile()
{

    {

        //判断文件是否存在
        QFile *file = new QFile(workdir);
        if(file->open(QIODevice::ReadOnly))
        {
            for(int i=0;i<100000000;i++)
            {
                {
                    QString ba(file->readLine());




                    ba.remove("\r");
                    ba.remove("\n");
                    data.append(ba);

                }


                if(file->atEnd())break;
            }
            file->close();
        }
        file->deleteLater();
    }
    qDebug()<<data.count();
}
void Worker::saveFile()
{
    for(int i=0;i<finishedData->count();i++)
    {
        QString filename=qApp->applicationDirPath()+"/sav/"+finishedData->at(i)->fileName+".csv";

        QFile file(filename);
        if(file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            file.write(finishedData->at(i)->fileData.toLatin1());
            file.flush();
            file.close();
            qDebug()<<filename<<"ok";
        }
        else
        {
            qDebug()<<filename<<"error";
        }
    }


}
