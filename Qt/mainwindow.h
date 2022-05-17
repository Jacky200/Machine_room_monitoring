#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "thread1.h"
#include <QTimer>
#include <QMovie>
#include <QCoreApplication>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void get_data();
    void repaly(QNetworkReply *reply);
public slots:
    void onTimeOut();
private slots:
    void on_Bt1_clicked();

    void on_Bt2_clicked();

    void on_Bt3_clicked();

    void on_Bt4_clicked();

    void on_Bt5_clicked();

    void on_Bt5_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager_data=nullptr;
    void parse_json(QByteArray json);
    thread1 *t1=nullptr;
    QTimer *ti=nullptr;
    int status[5]={0};
    QMovie *gif1=nullptr;
    QMovie *gif2=nullptr;
    QMovie *gif3=nullptr;
    QMovie *gif4=nullptr;
    QMovie *gif5=nullptr;
};

#endif // MAINWINDOW_H
