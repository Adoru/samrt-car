#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)  //此处改为QLabel
    ,rotate(0)
{

}

void MyLabel::setRotate(int rotate)
{
    this->rotate = rotate;
}

void MyLabel::setCarName(QString name)
{
    this->carName = name;
}

void MyLabel::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //1.坐标偏移,以此更改画家的旋转轴(到中心)
    p.translate(this->width()/2,this->height()/2);
    //2.旋转
    p.rotate(rotate);
    //3.把坐标变回去
    p.translate(-this->width()/2,-this->height()/2);
    //4.
    QRect target(0, 0, 58, 58);
    //5.
    p.drawImage(target, QImage(carName));
}
