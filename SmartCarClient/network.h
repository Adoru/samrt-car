#ifndef NETWORK_H
#define NETWORK_H
/* 网络接口类*/
#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Network : public QObject
{
    Q_OBJECT

private:
    //单例模式：构造函数必须写在private里
    explicit Network(QObject *parent = nullptr);

signals:
    void sendDataToWindow(const QJsonObject& json);

public:
    static Network* getNetPtr();    //单例模式：从外部获取唯一对象指针的函数
    void initNetwork();
    bool sendNetData(QByteArray &data);

public slots:
    void connectedSlot();
    void readDataSlot();
    void disconnectSlot();


private:
    static Network* netPtr; //单例模式：静态变量
    QTcpSocket   *socket;
    bool flag ;

};

#endif // NETWORK_H
