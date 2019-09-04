#include "animation.h"

/***********************************
 * 控制红绿灯延时
 ***********************************/
void animation::controllightGroupSLot(int i)
{
    if (i==1)
    {
        qDebug() << "light second:3";
        coliGroup->button(1)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/threenext.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/threenext.png);}");
        coliGroup->button(2)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/five.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/fivenext.png);}");
        coliGroup->button(3)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/eight.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/eightnext.png);}");
    }

    if (i==2)
    {
        qDebug() << "light second:5";
        coliGroup->button(1)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/three.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/threenext.png);}");
        coliGroup->button(2)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/fivenext.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/fivenext.png);}");
        coliGroup->button(3)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/eight.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/eightnext.png);}");
    }
    if (i==3)
    {
        qDebug() << "light second:8";
        coliGroup->button(1)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/three.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/threenext.png);}");
        coliGroup->button(2)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/five.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/fivenext.png);}");
        coliGroup->button(3)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/eightnext.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/eightnext.png);}");
    }
}

/***********************************
 * 初始化红绿灯控制
 ***********************************/
void animation::initlightControl()
{
    QFont labelFont("Microsoft Yahei", 16, 10);
    chooselightLabel =  new QLabel(this);
    chooselightLabel -> setFont(labelFont);  //设置字体
    chooselightLabel -> setAlignment(Qt::AlignCenter);  //文本居中
    chooselightLabel -> setText("交通灯时间");
    chooselightLabel -> setGeometry(510*scaleVar, 120*scaleVar, 130, 50);

    coliGroup = new QButtonGroup(this);

    for(int i=1 ; i<4 ;i++)
    {
        QPushButton *coli = new QPushButton(this);
        coliGroup->addButton(coli, i);
    }

    coliGroup->button(1)->setGeometry(610*scaleVar, 125*scaleVar, 50, 50);
    coliGroup->button(2)->setGeometry(650*scaleVar, 125*scaleVar, 50, 50);
    coliGroup->button(3)->setGeometry(690*scaleVar, 125*scaleVar, 50, 50);

    coliGroup->button(1)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/three.png);}"
                          "QPushButton:hover:pressed { border-image: url(:/image/threenext.png);}");
    coliGroup->button(2)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/five.png);}"
                          "QPushButton:hover:pressed { border-image: url(:/image/fivenext.png);}");
    coliGroup->button(3)->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/eight.png);}"
                          "QPushButton:hover:pressed { border-image: url(:/image/eightnext.png);}");

    connect(coliGroup, SIGNAL(buttonClicked(int)),
         this, SLOT(controllightGroupSLot(int)));
}


/***********************************
 * 设置红绿灯
 ***********************************/
void animation::buttonLight()
{

      QIcon  icon1(":/image/light1.png");
      QIcon  icon2(":/image/light2.png");

      int i=0;
      if(i == 1)
      {
          btnGroup->button(1)->setIcon(icon2);
          btnGroup->button(3)->setIcon(icon2);
          btnGroup->button(4)->setIcon(icon1);
          btnGroup->button(5)->setIcon(icon2);
          btnGroup->button(7)->setIcon(icon2);
      }
      if(i == 0)
      {
          btnGroup->button(1)->setIcon(icon1);
          btnGroup->button(3)->setIcon(icon1);
          btnGroup->button(4)->setIcon(icon2);
          btnGroup->button(5)->setIcon(icon1);
          btnGroup->button(7)->setIcon(icon1);
      }
      btnGroup->button(1)->setIconSize(QSize(62*scaleVar,62*scaleVar));
      btnGroup->button(3)->setIconSize(QSize(62*scaleVar,62*scaleVar));
      btnGroup->button(4)->setIconSize(QSize(62*scaleVar,62*scaleVar));
      btnGroup->button(5)->setIconSize(QSize(62*scaleVar,62*scaleVar));
      btnGroup->button(7)->setIconSize(QSize(62*scaleVar,62*scaleVar));
}


/***********************************
 * 初始化车流辅助显示
 * 以改变 button 的背景颜色表示
 ***********************************/
void animation::initlineGroup()
{
    lineGroup = new QButtonGroup(this);

    for(int i=1 ; i<25 ;i++)
    {
        QPushButton *line = new QPushButton(this);
        line->setStyleSheet("background-color: rgb(0,255,0)");
        lineGroup->addButton(line, i);
    }
}

/***********************************
 * 初始化车流辅助显示的按钮位置
 ***********************************/
void animation::initline()
{
    lineGroup->button(1)->setGeometry ( 62 *scaleVar, 0  *scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(2)->setGeometry ( 281*scaleVar, 0  *scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(3)->setGeometry ( 62 *scaleVar, 58 *scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(4)->setGeometry ( 281*scaleVar, 58 *scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(5)->setGeometry ( 62 *scaleVar, 218*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(6)->setGeometry ( 281*scaleVar, 218*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(7)->setGeometry ( 62 *scaleVar, 276*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(8)->setGeometry ( 281*scaleVar, 276*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(9)->setGeometry ( 62 *scaleVar, 436*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(10)->setGeometry( 281*scaleVar, 436*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(11)->setGeometry( 62 *scaleVar, 495*scaleVar , 156*scaleVar, 5*scaleVar  );
    lineGroup->button(12)->setGeometry( 281*scaleVar, 495*scaleVar , 156*scaleVar, 5*scaleVar  );

    lineGroup->button(13)->setGeometry( 0  *scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(14)->setGeometry( 58 *scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(15)->setGeometry( 218*scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(16)->setGeometry( 278*scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(17)->setGeometry( 437*scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(18)->setGeometry( 496*scaleVar , 61 *scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(19)->setGeometry( 0  *scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(20)->setGeometry( 58 *scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(21)->setGeometry( 218*scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(22)->setGeometry( 278*scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(23)->setGeometry( 437*scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
    lineGroup->button(24)->setGeometry( 496*scaleVar , 278*scaleVar, 5*scaleVar, 156*scaleVar  );
}

/***********************************
 * 改变车流辅助显示颜色
 * 车辆数小于等于1时为绿色
 * 车辆数等于2时为黄色
 * 车辆数大于等于3时为红色
 ***********************************/
void animation::turnlight()
{
    int a[24] = {0} ;
    a[12] = 5 ;
    a[10] = 2 ;

    for(int w=0 ; w<24 ; w++)
    {
        if(a[w]<=1)
        {
             lineGroup->button(w+1)->setStyleSheet("background-color:rgb(0,255,0)");
        }
        if(a[w]==2)
        {
             lineGroup->button(w+1)->setStyleSheet("background-color: yellow");
        }
        if(a[w]>=3)
        {
            lineGroup->button(w+1)->setStyleSheet("background-color: red");
        }
    }
}

