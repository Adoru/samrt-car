#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <QObject>
#include "network.h"
#include <QMessageBox>
#include "protocol.h"
#include <QVector>
#include <QDebug>
#include <QMap>
//#include "animation.h"

class HandleData : public QObject
{
    Q_OBJECT
public:
    explicit HandleData(QObject *parent = nullptr);
    //判断心跳包以及选车
    void ChooseCar();
    //红绿灯  上行下行都写进里面
    void ChangeLight();
    //定位
    void Position(QMap<QString, int> RfidNumber);
    //改变路颜色
    void ChangeRoadColor();
signals:

private slots:
    //void on_sendBtn_released();
    void receiveNetDataSlot(const QJsonObject& json);//接收网络数据的槽函数
public slots:
private:
    //QVector DataFromServer;
    QString HeartPack;  //心跳包状态
    QString LightState;
    QString CarPosition; //车位置
    QMap<QString, int> RfidNumber;  //RFID卡号键值对
};

#endif // HANDLEDATA_H
