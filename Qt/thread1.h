#ifndef THREAD_H
#define THREAD_H

#include <QNetworkReply>
#include <QObject>
#include <QThread>
#include <QTimer>
class thread1 : public QThread
{
    Q_OBJECT
public:
    explicit thread1(QObject *parent = nullptr);
protected:
    void run() override;
private:

};

#endif // THREAD_H
