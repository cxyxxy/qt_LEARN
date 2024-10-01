#include "desktop_pets.h"
#include "stdafx.h"

Desktop_pets::Desktop_pets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setStatusBar(nullptr);
    setMenuBar(nullptr);
    removeToolBar(ui.mainToolBar);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);//去掉窗口标题
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);//保持窗口置顶2

    int coordX, coordY;//桌面坐标
    QFile file("./file/file.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    if (file.isOpen())//读取体型、装扮编号参数、相对桌面坐标
        in >> m_size >> m_bodyNum >> m_earsNum >> coordX >> coordY;
    else {
        m_size = 400;
        m_bodyNum = 0;
        m_earsNum = 0;
        coordX = x();
        coordY = y();
    }
    file.close();
    move(coordX, coordY);

    m_timer = new QTimer;
    m_timer->start(40);//动画速度
    connect(m_timer, &QTimer::timeout, this, &Desktop_pets::eyesMovement);//关联眼部动作

    imageLoad();//载入部位图片
    eyesMovementLoad();//载入表情图片
    specialMovementLoad();//载入特殊动作图片

    m_bodyImage = new QLabel(this);//身体图片指针
    m_eyesImage = new QLabel(this);//眼部图片指针
    m_stripeImage = new QLabel(this);//屏幕遮盖条纹图片指针
    m_earsImage = new QLabel(this);//耳朵图片指针

    imageSet(m_bodyImage, m_body[m_bodyNum]);

    imageSet(m_eyesImage, m_eyes);

    if (m_size > 140) 
    {
        imageSet(m_stripeImage, m_stripe);
        m_stripeImage->show();
    }
    else m_stripeImage->hide();

    imageSet(m_earsImage, m_earsLeft[m_earsNum]);

    initBtn();//初始化按钮
    initSystemTray();//初始化系统托盘
}

Desktop_pets::~Desktop_pets()
{
    //清理各类指针申请的空间
    delete m_earsImage;
    delete m_bodyImage;
    delete m_eyesImage;
    delete m_stripeImage;

    delete m_closeBtn;
    //delete dressBtn;
    //delete moreBtn;
    delete m_minBtn;
    delete m_setBtn;
    //delete musicBtn;
    //delete gameBtn;
    //delete calenBtn;

    /*delete dressWindow;*/
    delete m_settingWidget;
    /*delete calenWindow;
    delete musicWindow;*/
}

void Desktop_pets::mousePressEvent(QMouseEvent* event)
{
    static int flag = 0;//触发特殊动作的计数变量
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_mouseStartPoint = event->globalPos();
        m_windowTopLeftPoint = this->frameGeometry().topLeft();

        if (m_face < 0 && m_specialMove < 0) {//随机播放表情
            m_face = qrand() % (m_faceSum - 1) + 1;
            flag++;
            if (flag == 10) {//触发蓝屏
                flag = 0;
                m_specialMove = 0;
                m_face = -1;
            }
        }

    }
    else if (event->button() == Qt::RightButton) {//鼠标右键事件
        if (m_btnSwitch1) {//隐藏按钮
            m_btnSwitch1 = 0;
            m_btnSwitch2 = 0;
        }
        else
            m_btnSwitch1 = 1;//显示按钮

        //dressWindow->hide();
        btnSwitchRole();
    }
}

void Desktop_pets::mouseMoveEvent(QMouseEvent* event)
{
    if (this->isMaximized()) //如果当前是最大化，则不允许移动
        return;

    if (m_bPressed)
    {
        QPoint distance = event->globalPos() - m_mouseStartPoint;
        this->move(m_windowTopLeftPoint + distance);
    }
}

void Desktop_pets::mouseReleaseEvent(QMouseEvent* event)
{

    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = false;
    }
}

void Desktop_pets::imageLoad()
{
    //载入装扮图片
    m_body.push_back(QPixmap(QString(":/images/appearance/body/def_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/blue_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/pink_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/icefire_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/cat_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/Gundam_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/drill_body.png")));
    m_body.push_back(QPixmap(QString(":/images/appearance/body/angel_body.png")));

    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/def_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/blue_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/pink_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/icefire_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/cat_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/Gundam_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/drill_ears1.png")));
    m_earsLeft.push_back(QPixmap(QString(":/images/appearance/ears/angel_ears1.png")));

    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/def_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/blue_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/pink_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/icefire_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/cat_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/Gundam_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/drill_ears2.png")));
    m_earsRight.push_back(QPixmap(QString(":/images/appearance/ears/angel_ears2.png")));

    m_eyes.load(":/images/appearance/eyes/def_eyes.png");
    m_stripe.load(":/images/appearance/stripe.png");
}

void Desktop_pets::eyesMovementLoad()
{
    m_faceNum.push_back(9);//帧数-例：9代表9帧
    m_faceNum.push_back(0);//起始位置-例：0代表该表情第一张图片下标
    for (int i = 1; i <= m_faceNum[0]; i++)//表情1-眨眼
        m_movement.push_back(QPixmap(QString(":/images/movement/blink/%1.png").arg(i)));

    m_faceNum.push_back(12);
    m_faceNum.push_back(9);
    for (int i = 1; i <= m_faceNum[2]; i++)//表情2-心动
        m_movement.push_back(QPixmap(QString(":/images/movement/heart/%1.png").arg(i)));

    m_faceNum.push_back(16);
    m_faceNum.push_back(21);
    for (int i = 1; i <= m_faceNum[4]; i++)//表情3-疑惑
        m_movement.push_back(QPixmap(QString(":/images/movement/question/%1.png").arg(i)));

    m_faceNum.push_back(15);
    m_faceNum.push_back(37);
    for (int i = 1; i <= m_faceNum[6]; i++)//表情4-闭眼
        m_movement.push_back(QPixmap(QString(":/images/movement/closeEyes/%1.png").arg(i)));

    m_faceNum.push_back(9);
    m_faceNum.push_back(52);
    for (int i = 1; i <= m_faceNum[8]; i++)//表情5-单眨眼
        m_movement.push_back(QPixmap(QString(":/images/movement/wink/%1.png").arg(i)));

    m_face = -1;//表情序号初始化为-1，不生效
    m_faceSum = 5;//表情数量
}

void Desktop_pets::specialMovementLoad()
{
    for (int i = 1; i <= 11; i++)
        m_specialMovement.push_back(QPixmap(QString(":/images/movement/error/%1.png").arg(i)));
    for (int i = 1; i <= 22; i++)
        m_specialMovement.push_back(QPixmap(QString(":/images/movement/fly/%1.png").arg(i)));

    m_specialMove = -1;
}

void Desktop_pets::imageSet(QLabel* image, QPixmap map)
{
    //根据size设定各图片大小和坐标
    image->setPixmap(map.scaled(m_size, m_size));//使用scaled修改图片大小，能避免图片因缩放模糊
    image->setScaledContents(true);
    image->resize(m_size, m_size);
    image->move(this->frameGeometry().width() / 2 - m_size / 2,
        this->frameGeometry().height() / 2 - m_size / 2);
}

void Desktop_pets::eyesMovement()
{
    //各种静态变量，用于计数、记录状态等↓
    static int flag = 0, second1 = 0, second2 = 0, earSwitch = 1;
    int valve = qrand() % 200;
    if (m_face < 0 && m_specialMove < 0) {//控制眨眼动作
        second1++;
        if (second1 >= valve && valve > 100) {
            m_face = 0;
            second1 = 0;
        }
    }

    second2++;//控制耳朵的动画
    if (second2 > 40 && earSwitch) {
        m_earsImage->setPixmap(m_earsRight[m_earsNum].scaled(m_size, m_size));
        earSwitch = 0;
        second2 = 0;
    }
    else if (second2 > 10 && !earSwitch) {
        m_earsImage->setPixmap(m_earsLeft[m_earsNum].scaled(m_size, m_size));
        earSwitch = 1;
        second2 = 0;
    }

    if (m_face != -1) {//控制表情变化
        int num = m_faceNum[m_face * 2], start = m_faceNum[m_face * 2 + 1];
        flag++;
        if (flag < num)
            m_eyesImage->setPixmap(
                m_movement[start + flag].scaled(m_size, m_size));
        else
            m_eyesImage->setPixmap(
                m_movement[start - flag + (num - 1) * 2].scaled(m_size, m_size));

        if (flag >= (num - 1) * 2) {
            flag = 0;
            m_face = -1;
            m_eyesImage->setPixmap(m_eyes.scaled(m_size, m_size));
        }
    }
    //if (!dressWindow->isHidden()) {
    //    //从换装窗口中获取bodyNum、earsNum参数
    //    if (bodyNum != dressWindow->getBodyNum()) {
    //        bodyNum = dressWindow->getBodyNum();
    //        bodyImage->setPixmap(body[bodyNum].scaled(m_size, m_size));
    //        saveData();
    //    }
    //    if (earsNum != dressWindow->getEarsNum()) {
    //        earsNum = dressWindow->getEarsNum();
    //        earsImage->setPixmap(ears1[earsNum].scaled(m_size, m_size));
    //        saveData();
    //    }
    //}

    //if (!setWindow->isHidden()) {//从设置窗口中获取size参数
    //    if (size != setWindow->getSize()) {
    //        size = setWindow->getSize();

    //        imageSet(bodyImage, body[bodyNum]);
    //        imageSet(eyesImage, eyes);
    //        if (size > 140) {
    //            imageSet(stripeImage, stripe);
    //            stripeImage->show();
    //        }
    //        else
    //            stripeImage->hide();
    //        imageSet(earsImage, ears1[earsNum]);

    //        saveData();
    //        reInitBtn();
    //    }
    //}
    if (m_specialMove > -1)//特殊动作
        specialMovement();
}

void Desktop_pets::specialMovement() {
    static int flag = 0;

    if (m_specialMove == 0) {//动作-error
        if (flag % 20 == 0 && flag <= 200)
            m_eyesImage->setPixmap(m_specialMovement[flag / 20].scaled(m_size, m_size));
        else if (flag > 300) {
            m_eyesImage->setPixmap(m_eyes.scaled(m_size, m_size));
            flag = 0;
            m_specialMove = -1;
            return;
        }
    }
    flag++;
}

void Desktop_pets::saveData()
{
    QFile file("./file/file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_size << m_bodyNum << m_earsNum << x() << y();//存储体型、装扮编号参数、窗口坐标
    file.close();
}

void Desktop_pets::initBtn()
{
    m_closeBtn = new QPushButton(this);//关闭按钮
    //dressBtn = new QPushButton(this);//换装按钮
    //moreBtn = new QPushButton(this);//展开更多按钮
    m_minBtn = new QPushButton(this);//最小化按钮
    m_setBtn = new QPushButton(this);//设置按钮
    //musicBtn = new QPushButton(this);//音乐按钮
    //gameBtn = new QPushButton(this);//游戏按钮
    //calenBtn = new QPushButton(this);//日历按钮

    m_closeBtn->setIcon(QIcon(":/images/icon/close.png"));
    //dressBtn->setIcon(QIcon(":/images/icon/dress.png"));
    //moreBtn->setIcon(QIcon(":/images/icon/more.png"));
    m_minBtn->setIcon(QIcon(":/images/icon/min.png"));
    m_setBtn->setIcon(QIcon(":/images/icon/setting.png"));
    /*musicBtn->setIcon(QIcon(":/images/icon/music.png"));
    gameBtn->setIcon(QIcon(":/images/icon/game.png"));
    calenBtn->setIcon(QIcon(":/images/icon/calendar.png"));*/

    reInitBtn();

    //设置按钮样式
    setStyleSheet("QPushButton{border:4px solid black;"
        "background-color:rgb(200,210,255);border-radius: 10px;}"
        "QPushButton::hover{background-color:rgb(170,200,255);}"
        "QPushButton:pressed{background-color:rgb(60,70,200);}");

    //dressWindow = new DressWin;//换装窗口
    //dressWindow->accept(body, ears1, bodyNum, earsNum);

    m_settingWidget = new SettingWidget;//设置窗口
    m_settingWidget->setSize(m_size);//为设置窗口传入size参数

    //musicWindow = new MusicWin;//音乐窗口

    //calenWindow = new QCalendarWidget;//日历窗口
    //calenWindow->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口标题栏
    //calenWindow->setWindowIcon(QIcon(":/images/icon/calendar.png")); //设置窗口图标
    //calenWindow->resize(600, 400);


    //连接按钮信号与对应槽函数
    connect(m_closeBtn, &QPushButton::clicked, this, &Desktop_pets::close);
    //connect(dressBtn, &QPushButton::clicked, this, &Haro::dressBtnPush);
    //connect(moreBtn, &QPushButton::clicked, this, &Haro::moreBtnPush);
    connect(m_minBtn, &QPushButton::clicked, this, &Desktop_pets::min);
    connect(m_setBtn, &QPushButton::clicked, this, &Desktop_pets::setting);
    /*connect(musicBtn, &QPushButton::clicked, this, &Haro::musicBtnPush);
    connect(gameBtn, &QPushButton::clicked, this, &Haro::gameBtnPush);
    connect(calenBtn, &QPushButton::clicked, this, &Haro::calenBtnPush);*/

    m_btnSwitch1 = 0;//初始化按钮显示
    m_btnSwitch2 = 0;
    btnSwitchRole();
}

void Desktop_pets::reInitBtn()
{
    m_btnSize = m_size;

    // if(btnSize > 650)//限制按钮大小
     //    btnSize = 650;
    if (m_btnSize < 300)//限制按钮大小
        m_btnSize = 300;
    //按钮的坐标和大小参数
    int btnX = this->frameGeometry().width() / 2 - m_btnSize * 3 / 5 - 5;
    int btnY = this->frameGeometry().height() / 2 - m_btnSize / 4;
    int btnWidth = m_btnSize / 5;
    int btnHeight = m_btnSize / 8;

    m_setBtn->setGeometry(btnX, btnY, btnWidth, btnHeight);
    m_minBtn->setGeometry(btnX, btnY + m_btnSize / 6, btnWidth, btnHeight);
    m_closeBtn->setGeometry(btnX, btnY + 2 * m_btnSize / 6, btnWidth, btnHeight);
   /* closeBtn->setGeometry(btnX, btnY, btnWidth, btnHeight);
    dressBtn->setGeometry(btnX, btnY + btnSize / 6, btnWidth, btnHeight);
    moreBtn->setGeometry(btnX, btnY + 2 * btnSize / 6, btnWidth, btnHeight);
    minBtn->setGeometry(btnX, btnY + 3 * btnSize / 6, btnWidth, btnHeight);*/

    //setBtn->setGeometry(btnX - btnWidth * 1.2, btnY, btnWidth, btnHeight);
    //musicBtn->setGeometry(btnX - btnWidth * 1.2, btnY + btnSize / 6, btnWidth, btnHeight);
    //gameBtn->setGeometry(btnX - btnWidth * 1.2, btnY + 2 * btnSize / 6, btnWidth, btnHeight);
    //calenBtn->setGeometry(btnX - btnWidth * 1.2, btnY + 3 * btnSize / 6, btnWidth, btnHeight);
    //图标大小
    QSize temp(m_btnSize / 8, m_btnSize / 8);
    m_closeBtn->setIconSize(temp);
    /*dressBtn->setIconSize(temp);
    moreBtn->setIconSize(temp);*/
    m_minBtn->setIconSize(temp);
    m_setBtn->setIconSize(temp);
    /*musicBtn->setIconSize(temp);
    gameBtn->setIconSize(temp);
    calenBtn->setIconSize(temp);*/

}

void Desktop_pets::closePets()
{

    m_settingWidget->close();
    this->close();
}

void Desktop_pets::min()
{
    this->hide();
    //dressWindow->hide();
    //calenWindow->hide();
    m_settingWidget->hide();
    //musicWindow->hide();

    m_btnSwitch1 = 0;
    m_btnSwitch2 = 0;
    btnSwitchRole();
}

void Desktop_pets::setting()
{
    if (m_settingWidget->isHidden()) 
    {
        //移动窗口坐标↓
        m_settingWidget->move(x() + frameGeometry().width() / 2
            - m_btnSize * (m_btnSwitch1 + m_btnSwitch2 + 1.5) / 4 - m_settingWidget->frameGeometry().width(),
            y() + frameGeometry().height() / 2 - m_size / 5
            - m_settingWidget->frameGeometry().height() / 2);

        m_settingWidget->show();
        //calenWindow->hide();
        //musicWindow->hide();
    }
    else
        m_settingWidget->hide();
}

void Desktop_pets::btnSwitchRole()
{
    //根据btnSwitch调整按钮是否显示
    m_closeBtn->setVisible(m_btnSwitch1);
    //dressBtn->setVisible(m_btnSwitch1);
    //moreBtn->setVisible(m_btnSwitch1);
    m_minBtn->setVisible(m_btnSwitch1);
    m_setBtn->setVisible(m_btnSwitch1);
    //musicBtn->setVisible(m_btnSwitch2);
    //gameBtn->setVisible(m_btnSwitch2);
    //calenBtn->setVisible(m_btnSwitch2);
    //移动窗口坐标↓
    //musicWindow->move(x() + frameGeometry().width() / 2
    //    - btnSize * (m_btnSwitch1 + m_btnSwitch2 + 1.5) / 4 - musicWindow->frameGeometry().width(),
    //    y() + frameGeometry().height() / 2 - size / 5
    //    - musicWindow->frameGeometry().height() / 2);
    ////移动窗口坐标↓
    //calenWindow->move(x() + frameGeometry().width() / 2
    //    - btnSize * (m_btnSwitch1 + m_btnSwitch2 + 1.5) / 4 - calenWindow->frameGeometry().width(),
    //    y() + frameGeometry().height() / 2 - size / 5
    //    - calenWindow->frameGeometry().height() / 2);


}

void Desktop_pets::initSystemTray()
{

    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/images/icon/haro_icon.ico"));
    m_systemTray->setToolTip("Hello, I'm a desttop pet.");
    m_systemTray->show();
    connect(m_systemTray, &QSystemTrayIcon::activated, this, &Desktop_pets::systemTrayShow);

}

void Desktop_pets::systemTrayShow()
{

    if (this->isHidden())
        this->show();

}