#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口标题和标签
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    this->setWindowTitle(QString("机房监控系统"));
    //隐藏进度条文本
    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->progressBar_2->setAlignment(Qt::AlignCenter);
    ui->progressBar_3->setAlignment(Qt::AlignCenter);
    ui->progressBar_4->setAlignment(Qt::AlignCenter);
    ui->progressBar_5->setAlignment(Qt::AlignCenter);

    //设置动画
    gif1=new QMovie("D:\\Qt\\WorkSpace\\Machine_room_monitoring\\CgiLogin\\image\\fan.gif");
    gif2=new QMovie("D:\\Qt\\WorkSpace\\Machine_room_monitoring\\CgiLogin\\image\\fan.gif");
    gif3=new QMovie("D:\\Qt\\WorkSpace\\Machine_room_monitoring\\CgiLogin\\image\\fan.gif");
    gif4=new QMovie("D:\\Qt\\WorkSpace\\Machine_room_monitoring\\CgiLogin\\image\\fan.gif");
    gif5=new QMovie("D:\\Qt\\WorkSpace\\Machine_room_monitoring\\CgiLogin\\image\\fan.gif");
    QSize si(40,40);


    ui->movie_1->setFixedSize(40,40);
    ui->movie_2->setFixedSize(40,40);
    ui->movie_3->setFixedSize(40,40);
    ui->movie_4->setFixedSize(40,40);
    ui->movie_5->setFixedSize(40,40);

    gif1->setScaledSize(si);
    gif2->setScaledSize(si);
    gif3->setScaledSize(si);
    gif4->setScaledSize(si);
    gif5->setScaledSize(si);

    ui->movie_1->setMovie(gif1);
    ui->movie_2->setMovie(gif2);
    ui->movie_3->setMovie(gif3);
    ui->movie_4->setMovie(gif4);
    ui->movie_5->setMovie(gif5);

    gif1->stop();
    gif2->stop();
    gif3->stop();
    gif4->stop();
    gif5->stop();


    manager_data=new QNetworkAccessManager(this);
    //注册发送与接收的信号与槽
    connect(manager_data,&QNetworkAccessManager::finished,this,&MainWindow::repaly);
    ti =new QTimer();
    ti->setInterval(3000);
    connect(ti,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    ti->start();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager_data;
    delete t1;
    delete ti;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/show.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void MainWindow::get_data()
{
    QString url=QString("http://192.168.200.134/cgi-bin/get_data");
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager_data->get(request);
}

void MainWindow::repaly(QNetworkReply *reply)
{
    QByteArray data=reply->readAll();
    parse_json(data);
}

void MainWindow::onTimeOut()
{
    get_data();
}


void MainWindow::parse_json(QByteArray json)
{
    qDebug()<<QString(json);
    QJsonParseError err;
    QJsonDocument doc=QJsonDocument::fromJson(json,&err);
    if(err.error!=QJsonParseError::NoError){
        qDebug()<<"json error";
        return ;
    }
    //是JSON数据
    QJsonObject obj=doc.object();

    QString t=obj["temperature1"].toString();
    ui->progressBar->setValue(obj["temperature1"].toString().toFloat());
    ui->progressBar->setFormat(QString("%1℃").arg(t));

    ui->progressBar_2->setValue(obj["temperature2"].toString().toFloat());
    t=obj["temperature2"].toString();
    ui->progressBar_2->setFormat(QString("%1℃").arg(t));

    ui->progressBar_3->setValue(obj["temperature3"].toString().toFloat());
    t=obj["temperature3"].toString();
    ui->progressBar_3->setFormat(QString("%1℃").arg(t));

    ui->progressBar_4->setValue(obj["temperature4"].toString().toFloat());
    t=obj["temperature4"].toString();
    ui->progressBar_4->setFormat(QString("%1℃").arg(t));

    ui->progressBar_5->setValue(obj["temperature5"].toString().toFloat());
    t=obj["temperature5"].toString();
    ui->progressBar_5->setFormat(QString("%1℃").arg(t));

}



void MainWindow::on_Bt1_clicked()
{
    if(status[0]==0){
        gif1->start();
        status[0]=1;
    }else{
        gif1->stop();
        status[0]=0;
    }
}

void MainWindow::on_Bt2_clicked()
{
    if(status[1]==0){
        gif2->start();
        status[1]=1;
    }else{
        gif2->stop();
        status[1]=0;
    }
}

void MainWindow::on_Bt3_clicked()
{
    if(status[2]==0){
        gif3->start();
        status[2]=1;
    }else{
        gif3->stop();
        status[2]=0;
    }
}

void MainWindow::on_Bt4_clicked()
{
    if(status[3]==0){
        gif4->start();
        status[3]=1;
    }else{
        gif4->stop();
        status[3]=0;
    }
}



void MainWindow::on_Bt5_clicked()
{
    if(status[4]==0){
        gif5->start();
        status[4]=1;
    }else{
        gif5->stop();
        status[4]=0;
    }
}
