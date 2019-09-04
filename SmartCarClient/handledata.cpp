#include "handledata.h"

HandleData::HandleData(QObject *parent) : QObject(parent)
{
    qDebug()<<"hand success";
//    qDebug()<<connect(Network::getNetPtr(),SIGNAL(sendDataToWindow(QJsonObject)),this,
//                      SLOT(receiveNetDataSlot(QJsonObject)));
    connect(Network::getNetPtr(),SIGNAL(sendDataToWindow(QJsonObject)),this,
            SLOT(receiveNetDataSlot(QJsonObject)));
}


void HandleData::ChooseCar()
{
    //心跳包1
    if(HeartPack == 0x31)
    {
        //连接前端选车动画
    }
    //心跳包2
    else if(HeartPack == 0x32)
    {
        //。，。。。。
    }
}

void HandleData::ChangeLight()
{
    //绿灯
    if(LightState == 0x31)
    {
        //调用前端动画
    }
    //红灯
    if(LightState == 0x30)
    {
        //.....
    }
}

void HandleData::Position(QMap<QString, int> RfidNumber)
{

}

/*
void HandleData::on_sendBtn_released()
{
    //返回lineEdit上的文本信息
    QString text = ui->lineEdit->text();

    QByteArray data = Protocol::packData(0,"text",text);
    //发送到服务器，先转换格式
    //QByteArray data = text.toUtf8();
    if(Network::getNetPtr()->sendNetData(data))
    {
        ui->lineEdit->clear();
        ui->textBrowser->append("我：" + text);
    }
    else
    {
        QMessageBox::information(this,"提示","error!");
    }
}
*/
void HandleData::receiveNetDataSlot(const QJsonObject &json)
{
    int type = json.value("type").toInt();
    QString text = NULL;

    qDebug()<<"333";
//    temp.test()->setText("111");
    switch (type)
    {

    //心跳1
    case 1:
        HeartPack = json.value("heart").toString();
//        temp.test()->setText("心跳1："+text);
        qDebug()<<"HeartPack";

        break;
    //心跳2
    case 2:
        HeartPack = json.value("heart").toString();
//        temp.test()->setText("心跳2："+text);
        qDebug()<<"HeartPack";
        break;
    //小车1
    case 3:
        CarPosition = json.value("rfid").toString();
//        temp.test()->setText("小车1："+text);
        break;
    //小车2
    case 4:
        CarPosition = json.value("rfid").toString();
//        temp.test()->setText("小车2："+text);
        break;
    //灯
    case 5:
        LightState = json.value("light").toString();
//        temp.test()->setText("灯："+text);
        break;
    default:
        qDebug()<<"wolaile";
    }
}
