#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <worker.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTime startTime;
    QTimer refTimer;
    Worker worker;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void refState();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
