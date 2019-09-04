#ifndef MYLABEL_H
#define MYLABEL_H
/*自定义标签类*/

#include <QWidget>
#include <QLabel>
#include <QPainter>

class MyLabel : public QLabel   //此处改成继承自QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
    void setRotate(int rotate);
    void setCarName(QString name);
protected:
    void paintEvent(QPaintEvent *);
signals:
private:
    int rotate; //旋转角度
    QString carName = ":/image/car.png";

public slots:
};

#endif // MYLABEL_H
