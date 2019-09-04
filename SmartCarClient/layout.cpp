#include "animation.h"

/**********************************
 * 初始化函数的功能函数
 **********************************/
void animation::initAll()
{
    initTimer();
    initAnimation();
    QVector<QPropertyAnimation*> vect = {anime_1, anime_2, anime_3};
    //setAnimeGroup(vect);
    initMap();
    carLabel->raise();
}

/**********************************
 * 绘图事件
 * 添加背景图片（地图）
 **********************************/
void animation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);                                    //变量event定义了但不使用，屏蔽警告
    QPainter p(this);
    QRect target(0,0,this->height(),this->height());    //位置，宽，高
    p.drawImage(target, QImage(":/image/map.png"));
}

/**********************************
 * 初始化时钟
 **********************************/
void animation::initTimer()
{
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));//信号源指针
}

/**********************************
 * 构造按钮组
 * 1.第一组按钮表示了小车移动的起点和终点坐标
 * 2.第二组按钮记录了横向道路（横边）的权重
 * 3.第三组按钮记录了纵向道路（纵边）的权重
 **********************************/
void animation::initButtonGroup()
{
    btnGroup = new QButtonGroup(this);
    for(int i = 0; i < 9; i++)
    {
        QPushButton *btn = new QPushButton(this);
        //btn->setFlat(true);                               //设置扁平化、边缘化（看不到）
        //btn->setStyleSheet("background:transparant;");    //设置按钮透明
        btn->setStyleSheet("background-color:gray;");
        //btn->setFixedSize(100, 100);
        btnGroup->addButton(btn, i);
    }

    hBtnWeightGroup = new QButtonGroup(this);
    vBtnWeightGroup = new QButtonGroup(this);
    for(int i = 0; i < 12; i++)
    {
        QPushButton *hBtn = new QPushButton(this);
        QPushButton *vBtn = new QPushButton(this);
        hBtn->setFlat(true);                               //按钮扁平化
        vBtn->setFlat(true);                               //按钮扁平化
        hBtnWeightGroup->addButton(hBtn, i);
        vBtnWeightGroup->addButton(vBtn, i);
    }

    connect(hBtnWeightGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(hBtnWeightGroupSlot(int)));
    connect(vBtnWeightGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(vBtnWeightGroupSlot(int)));
    connect(btnGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(nodeBtnGroupSlot(int)));
}

/***********************************
 * 初始化选车按钮组
 ***********************************/
void animation::initGroupBox()
{
    QFont btnFont("Microsoft Yahei", 10, 10);
    QFont labelFont("Microsoft Yahei", 20, 75);

    chooseCarLabel = new QLabel(this);
    chooseCarLabel->setFont(labelFont);
    chooseCarLabel->setText("菜单");
    chooseCarLabel->setAlignment(Qt::AlignCenter);
    chooseCarLabel->setGeometry(575, 10, 100, 50);

    pushBtnFlag = 1;    //开始时是收缩
    showGroupBoxBtn = new QPushButton(this);
    hideGroupBoxBtn = new QPushButton(this);
    connectNetBtn = new QPushButton(this);
    //testNetBtn = new QPushButton(this);
    testNetBtn = new QTextBrowser(this);

    showGroupBoxBtn->setGeometry(520, 60, 50, 50);
    hideGroupBoxBtn->setGeometry(680, 60, 50, 50);
    showGroupBoxBtn->setFlat(true);
    hideGroupBoxBtn->setFlat(true);
    showGroupBoxBtn->setStyleSheet(("border-image: url(:/image/show.png)"));
    hideGroupBoxBtn->setStyleSheet(("border-image: url(:/image/hide.png)"));
    hideGroupBoxBtn->hide();

    connectNetBtn->setGeometry(520, 60, 80, 50);
    connectNetBtn->setText("连接至网络");
    connectNetBtn->setFont(btnFont);
    connectNetBtn->setFlat(true);
    connectNetBtn->hide();

    testNetBtn->setGeometry(620, 60, 50, 50);
    testNetBtn->setText("测试");
    testNetBtn->setFont(btnFont);
    //testNetBtn->setFlat(true);
    testNetBtn->hide();

    connect(hideGroupBoxBtn, SIGNAL(clicked()),
            this, SLOT(hideButtonGroupSlot()));
    connect(showGroupBoxBtn, SIGNAL(clicked()),
            this, SLOT(showButtonGroupSlot()));
    connect(connectNetBtn, SIGNAL(clicked()),
            this, SLOT(connectToIntnet()));
//    connect(testNetBtn, SIGNAL(clicked()),
//            this, SLOT(testIntNetSlot()));
}

/***********************************
 * 选择控制方式的按钮控件
 ***********************************/
void animation::initControlModeGroup()
{
    QFont labelFont("Microsoft Yahei", 20, 75);
    QFont labelFont2("Microsoft Yahei", 16, 10);
    chooseCtrlModeLabel = new QLabel(this);
    startPlanningLabel = new QLabel(this);
    ctrlAutoLabel = new QLabel(this);
    ctrlSelfLabel = new QLabel(this);
    //设置字体
    chooseCtrlModeLabel->setFont(labelFont);
    startPlanningLabel->setFont(labelFont2);
    ctrlAutoLabel->setFont(labelFont2);
    ctrlSelfLabel->setFont(labelFont2);
    //文本居中
    chooseCtrlModeLabel->setAlignment(Qt::AlignCenter);
    startPlanningLabel->setAlignment(Qt::AlignCenter);
    ctrlSelfLabel->setAlignment(Qt::AlignCenter);
    ctrlAutoLabel->setAlignment(Qt::AlignCenter);


    chooseCtrlModeLabel->setText("控制方式");
    startPlanningLabel->setText("开始规划");
    ctrlAutoLabel->setText("自动遥控");
    ctrlSelfLabel->setText("手动遥控");
    chooseCtrlModeLabel->setGeometry(500, 130, 250, 50);
    startPlanningLabel->setGeometry(500, 300, 250, 50);
    ctrlAutoLabel->setGeometry(625, 180, 125, 50);
    ctrlSelfLabel->setGeometry(500, 180, 125, 50);

    ctrlFlag = 1;   //手动
    ctrlSelfBtn = new QPushButton(this);
    ctrlAutoBtn = new QPushButton(this);
    goUpBtn = new QPushButton(this);
    goLeftBtn = new QPushButton(this);
    goRightBtn = new QPushButton(this);
    goToTargetBtn = new QPushButton(this);

    ctrlSelfBtn->setGeometry(550, 240, 50, 50);
    ctrlAutoBtn->setGeometry(650, 240, 50, 50);
    goUpBtn->setGeometry(600, 360, 50, 50);
    goLeftBtn->setGeometry(530, 430, 50, 50);
    goRightBtn->setGeometry(670, 430, 50, 50);
    goToTargetBtn->setGeometry(600, 360, 50, 50);

    ctrlSelfBtn->setStyleSheet(("border-image: url(:/image/choosed.png)"));
    ctrlAutoBtn->setStyleSheet(("border-image: url(:/image/nochoosed.png)"));

    goToTargetBtn->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/nochoosed.png);}"
                                 "QPushButton:hover:pressed { border-image: url(:/image/target.png);}");
    goUpBtn->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/goUp.png);}"
                           "QPushButton:hover:pressed { border-image: url(:/image/goUpHover.png);}");
    goLeftBtn->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/goLeft.png);}"
                             "QPushButton:hover:pressed { border-image: url(:/image/goLeftHover.png);}");
    goRightBtn->setStyleSheet("QPushButton:!pressed { border-image: url(:/image/goRight.png);}"
                              "QPushButton:hover:pressed { border-image: url(:/image/goRightHover.png);}");
    goToTargetBtn->hide();
    startPlanningLabel->hide();

    connect(ctrlSelfBtn, SIGNAL(clicked()),
            this, SLOT(selfControlModeSlot()));
    connect(ctrlAutoBtn, SIGNAL(clicked()),
            this, SLOT(autoControlModeSlot()));

}

/***********************************
 * 布局
 * 摆放24个道路按钮位置
 ***********************************/
void animation::initLayout()
{
    hBtnWeightGroup->button(0)->setGeometry ( 60,   5, 160, 30);
    hBtnWeightGroup->button(1)->setGeometry ( 60,  32, 160, 30);
    hBtnWeightGroup->button(2)->setGeometry ( 60, 223, 160, 30);
    hBtnWeightGroup->button(3)->setGeometry ( 60, 248, 160, 30);
    hBtnWeightGroup->button(4)->setGeometry ( 60, 439, 160, 30);
    hBtnWeightGroup->button(5)->setGeometry ( 60, 466, 160, 30);
    hBtnWeightGroup->button(6)->setGeometry (279,   5, 160, 30);
    hBtnWeightGroup->button(7)->setGeometry (279,  32, 160, 30);
    hBtnWeightGroup->button(8)->setGeometry (279, 223, 160, 30);
    hBtnWeightGroup->button(9)->setGeometry (279, 248, 160, 30);
    hBtnWeightGroup->button(10)->setGeometry(279, 439, 160, 30);
    hBtnWeightGroup->button(11)->setGeometry(279, 466, 160, 30);

    vBtnWeightGroup->button(0)->setGeometry (  2,  65, 30, 160);
    vBtnWeightGroup->button(1)->setGeometry ( 32,  65, 30, 160);
    vBtnWeightGroup->button(2)->setGeometry (220,  65, 30, 160);
    vBtnWeightGroup->button(3)->setGeometry (250,  65, 30, 160);
    vBtnWeightGroup->button(4)->setGeometry (438,  65, 30, 160);
    vBtnWeightGroup->button(5)->setGeometry (468,  65, 30, 160);
    vBtnWeightGroup->button(6)->setGeometry (  2, 280, 30, 160);
    vBtnWeightGroup->button(7)->setGeometry ( 32, 280, 30, 160);
    vBtnWeightGroup->button(8)->setGeometry (220, 280, 30, 160);
    vBtnWeightGroup->button(9)->setGeometry (250, 280, 30, 160);
    vBtnWeightGroup->button(10)->setGeometry(438, 280, 30, 160);
    vBtnWeightGroup->button(11)->setGeometry(468, 280, 30, 160);

    btnGroup->button(0)->setGeometry(  2,   5, 60, 60);
    btnGroup->button(1)->setGeometry(220,   5, 60, 60);
    btnGroup->button(2)->setGeometry(437,   5, 60, 60);
    btnGroup->button(3)->setGeometry(  2, 222, 60, 60);
    btnGroup->button(4)->setGeometry(220, 222, 60, 60);
    btnGroup->button(5)->setGeometry(437, 222, 60, 60);
    btnGroup->button(6)->setGeometry(  2, 439, 60, 60);
    btnGroup->button(7)->setGeometry(220, 439, 60, 60);
    btnGroup->button(8)->setGeometry(437, 439, 60, 60);

    for(int i = 0; i < 12; i++)
    {
        hBtnWeightGroup->button(i)->setStyleSheet("color:white");
        vBtnWeightGroup->button(i)->setStyleSheet("color:white");
        hBtnWeightGroup->button(i)->setText("0");
        vBtnWeightGroup->button(i)->setText("0");
    }
}

