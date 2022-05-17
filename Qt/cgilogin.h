#ifndef CGILOGIN_H
#define CGILOGIN_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
QT_BEGIN_NAMESPACE
namespace Ui { class CgiLogin; }
QT_END_NAMESPACE

class CgiLogin : public QMainWindow
{
    Q_OBJECT

public:
    CgiLogin(QWidget *parent = nullptr);
    ~CgiLogin();
    void paintEvent(QPaintEvent *);

    //注册请求和响应
    void regist_get();
    void regist_replay(QNetworkReply *replay);
    //登录请求和响应
    void login_get();
    void login_repaly(QNetworkReply *replay);
    //加密函数
    QString password_md5(QString inputpass);
private slots:
    void on_login_clicked();

    void on_regist_clicked();

private:
    Ui::CgiLogin *ui;
    QNetworkAccessManager *manager_regist=NULL;
    QNetworkAccessManager *manager_login=NULL;


};
#endif // CGILOGIN_H
