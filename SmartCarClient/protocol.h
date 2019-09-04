#ifndef PROTOCOL_H
#define PROTOCOL_H
/*协议类*/
#include <QObject>
#include <QJsonObject> //json对象类
#include <QJsonDocument> //json文档类
#include <QJsonArray>    //json数组


class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    static QByteArray  packData(int type ,
                                QString key1="", QString value1="",
                                QString key2="", QString value2="",
                                QString key3="", QString value3="",
                                QString key4="", QString value4=""
                                );

signals:

public slots:
};

#endif // PROTOCOL_H
