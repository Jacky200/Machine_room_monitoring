#include "cgilogin.h"
#include "ui_cgilogin.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include "mainwindow.h"

CgiLogin::CgiLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CgiLogin)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("登录"));
    this->setWindowIcon(QIcon(":/image/icon.jpg"));
    //获取配置文件信息
    QSettings setting(QSettings::IniFormat,QSettings::SystemScope,"config_apache");
    QString username=setting.value("username").toString();
    QString password=setting.value("password").toString();

    ui->username->setText(username);
    ui->password->setText(password);

    //初始化manager
    manager_regist=new QNetworkAccessManager(this);
    manager_login=new QNetworkAccessManager(this);
    //设置注册与登录的请求与响应信号和槽
    connect(manager_regist,&QNetworkAccessManager::finished,this,&CgiLogin::regist_replay);
    connect(manager_login,&QNetworkAccessManager::finished,this,&CgiLogin::login_repaly);


}

CgiLogin::~CgiLogin()
{
    delete ui;
}

void CgiLogin::paintEvent(QPaintEvent *)
{
    //申请一个画家，画背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/login_2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

QString CgiLogin::password_md5(QString inputpass)
{
    //创建加密对象
    QCryptographicHash hash(QCryptographicHash::Md5);
    //添加明文数据
    hash.addData(inputpass.toUtf8());
    //获取加密后的数据
    QByteArray pass=hash.result(); //16个字节的数据
    //把pass转16进制
    return pass.toHex();
}

void CgiLogin::regist_get()
{
    QString username=ui->username->text();
    QString password=ui->password->text();
    //进行密码加密
    password=password_md5(password);
    qDebug()<<password;
    QString url=QString("http://192.168.200.134/cgi-bin/regist?username=%1&password=%2").arg(username).arg(password);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager_regist->get(request);
}

void CgiLogin::regist_replay(QNetworkReply *replay)
{
    QByteArray data=replay->readAll();
    qDebug()<<QString(data);
    if(QString(data)=='1'){
        qDebug()<<"注册成功";
        QMessageBox::warning(this,"注册","注册成功");
    }else {
        qDebug()<<"注册失败";
        QMessageBox::warning(this,"注册","注册失败");
    }
}

void CgiLogin::login_get()
{
    QString username=ui->username->text();
    QString password=ui->password->text();
    //进行密码加密
    password=password_md5(password);
    qDebug()<<password;
    QString url=QString("http://192.168.200.134/cgi-bin/login?username=%1&password=%2").arg(username).arg(password);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager_login->get(request);
}

void CgiLogin::login_repaly(QNetworkReply *replay)
{
    QByteArray data=replay->readAll();
    qDebug()<<QString(data);
    if(QString(data)=='1'){
        qDebug()<<"登录成功";
        //记录用户名和密码到配置文件
        if(ui->checkBox->isChecked()){
            //获取配置对象
            QSettings setting(QSettings::IniFormat,QSettings::SystemScope,"config_apache");
            setting.setValue("username",ui->username->text());
            setting.setValue("password",ui->password->text());
        }
        //进入主页面
        MainWindow *main=new MainWindow();
        main->show();
        this->close();
    }else {
        QMessageBox::warning(this,"登录","登录失败");
    }
}



//登录
void CgiLogin::on_login_clicked()
{
    login_get();
}
//注册
void CgiLogin::on_regist_clicked()
{
    regist_get();
}
