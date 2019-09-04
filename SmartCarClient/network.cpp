#include "network.h"
#include <QDebug>
Network *Network::netPtr = NULL;    //单例模式：全局声明

Network::Network(QObject *parent) : QObject(parent)
{
      socket = NULL;
      flag   =false ;
}

//获取本类唯一对象的指针
Network *Network::getNetPtr()
{
    if (netPtr == NULL)
    {
        netPtr = new Network;
    }
    qDebug()<<netPtr;
    return netPtr;
}

//初始化网络
void Network::initNetwork()
{
    if(socket == NULL)
    {
        socket = new QTcpSocket;
    }
    socket->connectToHost("192.168.43.208",10086);
    connect(socket,SIGNAL(connected()),this,SLOT(connectedSlot()));
}


//发送数据
bool Network::sendNetData(QByteArray &data)
{
    if (socket == NULL)
    {
        initNetwork();
    }
    if (flag)
    {
        if (socket->write(data))
        {
            return true ;
        }
    }
    return false;
}

//网络连接成功后触发
void Network::connectedSlot()
{
    flag =true;
    connect(socket,SIGNAL(readyRead()),this,SLOT(readDataSlot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnectSlot()));
    qDebug()<<"网络连接成功";
}

//读取数据槽函数
void Network::readDataSlot()
{
    QByteArray data;
    while (socket->bytesAvailable())
    {
       data.append(socket->readAll());
    }
    qDebug()<<"服务器反馈："<<data;
    QJsonDocument jsonDoc=QJsonDocument::fromJson(data);
    emit sendDataToWindow(jsonDoc.object());
}

//断开连接槽函数
void Network::disconnectSlot()
{
    flag = false ;
}
