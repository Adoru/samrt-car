
#include "animation.h"

/***********************************
 * 动画
 * 记录了所有个动画数据
 ***********************************/
void animation::initAnimation()
{
    anime_1 = new QPropertyAnimation(carLabel, "pos");  //动画作用于谁,位置
    anime_1->setStartValue(QPoint(20, 20));             //设置起始位置
    anime_1->setEndValue(QPoint(450, 20));              //设置终止位置
    anime_1->setDuration(5000);                         //设置动画时间，单位为毫秒

    anime_2 = new QPropertyAnimation(carLabel, "pos");
    anime_2->setStartValue(btnGroup->button(1)->pos());
    anime_2->setEndValue(btnGroup->button(4)->pos());
    anime_2->setDuration(5000);

    anime_3 = new QPropertyAnimation(carLabel, "pos");
    anime_3->setStartValue(btnGroup->button(4)->pos());
    anime_3->setEndValue(btnGroup->button(5)->pos());
    anime_3->setDuration(5000);

    anime_4 = new QPropertyAnimation(carLabel, "pos");
    anime_4->setStartValue(btnGroup->button(5)->pos());
    anime_4->setEndValue(btnGroup->button(8)->pos());
    anime_4->setDuration(5000);
}
