#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QApplication>
#include <QList>
struct DataBase
{
    DataBase() {}
    QString fileName;
    QByteArray fileData;
};
class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(QThread *parent = nullptr);
    QString workdir;
    int countSec=0;
    int countAll=0;
    QList<QByteArray> data;


    QList<DataBase*> *finishedData;
signals:

public slots:
    void run();
    void loadFile();
    void saveFile();
};

#endif // WORKER_H
