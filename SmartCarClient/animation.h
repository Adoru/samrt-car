#ifndef animation_H
#define animation_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QHBoxLayout>  //水平布局
#include <QVBoxLayout>  //垂直布局
#include <QPushButton>  //按钮
#include <QButtonGroup> //按钮组
#include <fstream>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>   //定时器
#include <QMap>     //键值对
#include <QPropertyAnimation>
#include <QAnimationGroup>
#include <QSequentialAnimationGroup>    //组成连贯动画
#include <QResizeEvent> //页面大小改变事件
#include "mylabel.h"
#include "protocol.h"
#include "handledata.h"
#include <QIcon>
#include "network.h"
#include <algorithm>
//#include <QHash>  //哈希表
#include <QLineEdit>
#include <QTextBrowser>
#include <QQueue>

class animation : public QWidget
{
    Q_OBJECT

public:
    animation(QWidget *parent = 0);
    ~animation();
    float scaleVar = 1.2;   //组件缩放比例
    void initAll();
    void initAnimation();
    void initTimer();
    void setAnimeGroup(const QVector<QPropertyAnimation*>&);
    void initMap();
    void initButtonGroup();
    void initControlModeGroup();
    void initGroupBox();
    void initLayout();
    void initGraph();
    void buttonlight();
    void initlineGroup();
    void initline();
    void turnlight();
    void initlightControl();
    void djkstra(int, int);
    QTextBrowser *test();
    struct edge
    {
        int to;
        int cost;
    };
public slots:   //槽函数定义必须
    void timerSlot();
    void hBtnWeightGroupSlot(int);
    void vBtnWeightGroupSlot(int);
    void resetWeightSlot();         //重置权重
    void nodeBtnGroupSlot(int);
    void showButtonGroupSlot(); //展开和回缩
    void hideButtonGroupSlot();
    void selfControlModeSlot();
    void autoControlModeSlot();

    void goStreight();              //手动控制
    void goRight();
    void goLeft();
    void connectToIntnet();
    void testIntNetSlot();
    void goToTargetSlot();          //路径规划
    bool endNodeNotExplored(QVector<int>, int);
    void buttonLight();
    void controllightGroupSLot(int);
protected:
    void paintEvent(QPaintEvent *event);
private:
    MyLabel *carLabel;
    QTimer *timer;
    QPropertyAnimation *anime_1;
    QPropertyAnimation *anime_2;
    QPropertyAnimation *anime_3;
    QPropertyAnimation *anime_4;

    QSequentialAnimationGroup *animeGroup;
    QMap<QPropertyAnimation *, int> map;   //模板类定义要加尖括号

    //路径规划
    QVector<edge> pathVect[9];
    QVector<int> minPath;       //最短路径
    int pathGoal;       //终点
    QVector<int> pathArray[9];  //到所有终点的最短路径
    int pathWeightArray[9][9];//最短路径
    int maxCar = 4;     //最大车流量

    //左边道路按钮布局
    QVBoxLayout *v1;
    QVBoxLayout *v2;
    QVBoxLayout *v3;
    QVBoxLayout *v4;
    QVBoxLayout *v5;

    //左边地图,右边控件, 总布局
    QHBoxLayout *h1;
    QHBoxLayout *h2;
    QHBoxLayout *h;

    //左边道路按钮布局
    QHBoxLayout *h11;
    QHBoxLayout *h12;
    QHBoxLayout *h21;
    QHBoxLayout *h22;
    QHBoxLayout *h31;
    QHBoxLayout *h32;

    QButtonGroup *btnGroup;
    QButtonGroup *hBtnWeightGroup;
    QButtonGroup *vBtnWeightGroup;

    //展开和收缩
    QPushButton *showGroupBoxBtn;
    QPushButton *hideGroupBoxBtn;
    QPushButton *connectNetBtn;
    //QPushButton *testNetBtn;
    QTextBrowser *testNetBtn;
    QLabel *chooseCarLabel;
    bool pushBtnFlag;

    //控制方式
    QLabel *chooseCtrlModeLabel;
    QLabel *ctrlSelfLabel;
    QLabel *ctrlAutoLabel;
    QLabel *startPlanningLabel;
    QPushButton *ctrlSelfBtn;
    QPushButton *ctrlAutoBtn;
    QPushButton *goUpBtn;
    QPushButton *goLeftBtn;
    QPushButton *goRightBtn;
    QPushButton *goToTargetBtn;
    QPushButton *resetWeightBtn;
    bool ctrlFlag;

    HandleData  *handle;

    //车流辅助显示
    QButtonGroup  *lineGroup;

    //红绿灯控制
    QLabel  *chooselightLabel;
    QPushButton  *threeSecond;
    QPushButton  *fiveSecond;
    QPushButton  *eightSecond;
    QButtonGroup *coliGroup;
};


#endif // ANIMATION_H
