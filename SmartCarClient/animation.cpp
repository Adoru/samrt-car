#include "animation.h"

/**********************************
 * 构造函数
 **********************************/
animation::animation(QWidget *parent)
    : QWidget(parent)
{
    this->setMaximumSize(750*scaleVar, 500*scaleVar);
    this->setMinimumSize(750*scaleVar, 500*scaleVar);
    //this->setStyleSheet(("background-color:white"));

    carLabel = new MyLabel(this);
    carLabel->setGeometry(0*scaleVar, 20*scaleVar, 58*scaleVar, 58*scaleVar);
    carLabel->setRotate(180);
    //carLabel->setStyleSheet(("border-image:url(:/image/car.png)"));

    initButtonGroup();
    initLayout();
    initGroupBox();
    initControlModeGroup();
    initGraph();

    initlineGroup();
    initline();
    turnlight();
    buttonLight();
    initlightControl();
}

/**********************************
 * 析构函数
 **********************************/
animation::~animation()
{
    delete anime_1;
    delete anime_2;
    delete anime_3;
    delete anime_4;
}

/**********************************
 * 动画组
 * 存储需要播放的动画构成的组
 **********************************/
void animation::setAnimeGroup(const QVector<QPropertyAnimation*>& vect)
{
    animeGroup = new QSequentialAnimationGroup;

    for(int i = 0; i < vect.size(); i++)
    {
        animeGroup->addAnimation(vect.at(i));
    }
    animeGroup->start();
    timer->start(200);
}

/**********************************
 * 初始化每幅动画车辆的旋转角
 * map存储动画与这个动画下车辆的旋转角构成
 * 的键值对
 **********************************/
void animation::initMap()
{
    map.insert(anime_1, 180);
    map.insert(anime_2, 270);
    map.insert(anime_3, 180);
    map.insert(anime_4, 90);
}

/**********************************
 * 定时器槽函数
 * 没过一段时间刷新动画
 **********************************/
void animation::timerSlot()
{
    if(animeGroup->state() != QAnimationGroup::Stopped)
    {
        //1.旋转角和当前正在运行的动画有关
        int rotate = map.value
                ((QPropertyAnimation*)animeGroup->currentAnimation());
        //2.设置旋转角
        carLabel->setRotate(rotate);
    }
    else
    {
        timer->stop();
        timer->deleteLater();   //立马释放可能造成能崩溃
    }
}

/**********************************
 * 道路按钮槽函数
 * 当按钮被按下时发生的事件
 * pathVect[i][j]中
 * i表示该道路的起点
 * j表示与该起点连接的第j条道路（根据end节点的值升序）
 * case后接的是道路编号
 * hBtnWeightGroup是横向（水平）按钮
 * vBtnWeightGroup是纵向（垂直）按钮
 **********************************/
void animation::hBtnWeightGroupSlot(int i)
{
    switch (i)
    {
        case 0:  if(pathVect[1][0].cost < maxCar){pathVect[1][0].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[1][0].cost + 48)); break;}
        case 1:  if(pathVect[0][0].cost < maxCar){pathVect[0][0].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[0][0].cost + 48)); break;}
        case 2:  if(pathVect[4][1].cost < maxCar){pathVect[4][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[4][1].cost + 48)); break;}
        case 3:  if(pathVect[3][1].cost < maxCar){pathVect[3][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[3][1].cost + 48)); break;}
        case 4:  if(pathVect[7][1].cost < maxCar){pathVect[7][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[7][1].cost + 48)); break;}
        case 5:  if(pathVect[6][1].cost < maxCar){pathVect[6][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[6][1].cost + 48)); break;}
        case 6:  if(pathVect[2][0].cost < maxCar){pathVect[2][0].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[2][0].cost + 48)); break;}
        case 7:  if(pathVect[1][1].cost < maxCar){pathVect[1][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[1][1].cost + 48)); break;}
        case 8:  if(pathVect[5][1].cost < maxCar){pathVect[5][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[5][1].cost + 48)); break;}
        case 9:  if(pathVect[4][2].cost < maxCar){pathVect[4][2].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[4][2].cost + 48)); break;}
        case 10: if(pathVect[8][1].cost < maxCar){pathVect[8][1].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[8][1].cost + 48)); break;}
        case 11: if(pathVect[7][2].cost < maxCar){pathVect[7][2].cost += 1; hBtnWeightGroup->button(i)->setText(QString(pathVect[7][2].cost + 48)); break;}
    }
}

void animation::vBtnWeightGroupSlot(int i)
{
    switch (i)
    {
        case 0:  if(pathVect[0][1].cost < maxCar){pathVect[0][1].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[0][1].cost + 48));break;}
        case 1:  if(pathVect[3][0].cost < maxCar){pathVect[3][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[3][0].cost + 48));break;}
        case 2:  if(pathVect[1][2].cost < maxCar){pathVect[1][2].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[1][2].cost + 48));break;}
        case 3:  if(pathVect[4][0].cost < maxCar){pathVect[4][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[4][0].cost + 48));break;}
        case 4:  if(pathVect[2][1].cost < maxCar){pathVect[2][1].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[2][1].cost + 48));break;}
        case 5:  if(pathVect[5][0].cost < maxCar){pathVect[5][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[5][0].cost + 48));break;}
        case 6:  if(pathVect[3][2].cost < maxCar){pathVect[3][2].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[3][2].cost + 48));break;}
        case 7:  if(pathVect[6][0].cost < maxCar){pathVect[6][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[6][0].cost + 48));break;}
        case 8:  if(pathVect[4][3].cost < maxCar){pathVect[4][3].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[4][3].cost + 48));break;}
        case 9:  if(pathVect[7][0].cost < maxCar){pathVect[7][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[7][0].cost + 48));break;}
        case 10: if(pathVect[5][2].cost < maxCar){pathVect[5][2].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[5][2].cost + 48));break;}
        case 11: if(pathVect[8][0].cost < maxCar){pathVect[8][0].cost += 1; vBtnWeightGroup->button(i)->setText(QString(pathVect[8][0].cost + 48));break;}
    }
}

/**********************************
 * 节点按钮事件
 * 设置终点
 **********************************/
void animation::nodeBtnGroupSlot(int goal)
{
    pathGoal = goal;
    for(int i = 0; i < 9; i++)
    {
        btnGroup->button(i)->setStyleSheet("background-color:gray;");
    }
    btnGroup->button(goal)->setStyleSheet("background-color:white;");
}

/**********************************
 * 选车按钮组展开
 **********************************/
void animation::showButtonGroupSlot()
{
    if(pushBtnFlag == 1)
    {
        connectNetBtn->show();
        testNetBtn->show();
        showGroupBoxBtn->hide();
        hideGroupBoxBtn->show();

        pushBtnFlag = 0;
    }
}

/**********************************
 * 选车按钮组回缩
 **********************************/
void animation::hideButtonGroupSlot()
{
    if(pushBtnFlag == 0)
    {
        connectNetBtn->hide();
        testNetBtn->hide();
        showGroupBoxBtn->show();
        hideGroupBoxBtn->hide();

        pushBtnFlag =1;
    }
}


/***********************************
 * 选择手动控制方式
 ***********************************/
void animation::selfControlModeSlot()
{
    if(ctrlFlag == 0)
    {
        ctrlSelfBtn->setStyleSheet(("border-image: url(:/image/choosed.png)"));
        ctrlAutoBtn->setStyleSheet(("border-image: url(:/image/nochoosed.png)"));
        goUpBtn->show();
        goLeftBtn->show();
        goRightBtn->show();
        goToTargetBtn->hide();
        resetWeightBtn->hide();
        startPlanningLabel->hide();
        ctrlFlag = 1;
    }
}

/***********************************
 * 选择自动控制方式
 ***********************************/
void animation::autoControlModeSlot()
{
    if(ctrlFlag == 1)
    {
        ctrlSelfBtn->setStyleSheet(("border-image: url(:/image/nochoosed.png)"));
        ctrlAutoBtn->setStyleSheet(("border-image: url(:/image/choosed.png)"));
        goUpBtn->hide();
        goLeftBtn->hide();
        goRightBtn->hide();
        goToTargetBtn->show();
        resetWeightBtn->show();
        startPlanningLabel->show();
        ctrlFlag = 0;
    }
}

/***********************************
 * 连接至服务器
 ***********************************/
void animation::connectToIntnet()
{
    qDebug() << "连接至网络...";
    Network::getNetPtr()->initNetwork();
}

void animation::testIntNetSlot()
{
    QString text = "网络连接测试";
    QByteArray data = Protocol::packData(0,"text",text);
    if (Network::getNetPtr()->sendNetData(data))
    {
        testNetBtn->setText("成功！");
    }
    else
    {
        testNetBtn->setText("失败！");
    }
}

QTextBrowser* animation::test()
{
    return testNetBtn;
}

/***********************************
 * 自动规划路径
 ***********************************/
void animation::goToTargetSlot()
{
    djkstra(0, pathGoal);
    qDebug() << minPath;
}


/***********************************
 * 重置权重
 * 将所有的道路按钮标签置零
 * pathVect中所有边的cost置零
 ***********************************/
void animation::resetWeightSlot()
{
    for(int i = 0; i < 11; i++)
    {
        hBtnWeightGroup->button(i)->setText("0");
        vBtnWeightGroup->button(i)->setText("0");
    }
    for(int i = 0; i < 2; i++)
    {
        pathVect[0][i].cost = 0;
        pathVect[2][i].cost = 0;
        pathVect[6][i].cost = 0;
        pathVect[8][i].cost = 0;
    }
    for(int i = 0; i < 3; i++)
    {
        pathVect[1][i].cost = 0;
        pathVect[3][i].cost = 0;
        pathVect[5][i].cost = 0;
        pathVect[7][i].cost = 0;
    }
    for(int i = 0; i < 4; i++)
    {
        pathVect[4][i].cost = 0;
    }
}




