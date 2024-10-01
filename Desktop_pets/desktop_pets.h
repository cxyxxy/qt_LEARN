#ifndef __DESKTOP_PET_H__
#define __DESKTOP_PET_H__

#include <QtWidgets/QMainWindow>
#include <QStyleOption>
#include <QPoint>
#include <QBitmap>
#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QPen>
#include<QMouseEvent>
#include<QtGlobal>
#include <QLabel>
#include<QPoint>
#include<QTimer>
#include<QPushButton>
#include<QCalendarWidget>
#include<QFile>
#include<QDataStream>
#include<QSystemTrayIcon>
#include<QPixmap>


#include "ui_desktop_pets.h"
#include "settingwidget.h"

class Desktop_pets : public QMainWindow
{
    Q_OBJECT

public:
    Desktop_pets(QWidget *parent = Q_NULLPTR);
    ~Desktop_pets();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void imageLoad();//各部位图片载入
    void eyesMovementLoad();//眼部动作载入
    void specialMovementLoad();//特殊动作事件
    inline void imageSet(QLabel* image, QPixmap map);//设置各部位图片
    void eyesMovement();//眼部动作表情
    void specialMovement();//特殊动作事件
    void saveData();//存储数据
    void initBtn();//初始化按钮
    void reInitBtn();//修改大小时再次初始化按钮
    void closePets();//点击关闭按钮事件
    void min();//点击最小化按钮事件
    void setting();//点击设置按钮事件
    void btnSwitchRole();//根据btnSwitch切换按钮状态
    void initSystemTray();//初始化系统托盘
    void systemTrayShow();//点击系统托盘事件

private:
    Ui::Desktop_petsClass ui;

    //实现窗口拖拽
    bool m_bPressed;
    QPoint m_mouseStartPoint;
    QPoint m_windowTopLeftPoint;

    int m_size;//体型大小
    int m_bodyNum, m_earsNum;//身体和耳朵对应装扮序号
    QTimer* m_timer;//定时器:定时触发动作
    std::vector<QPixmap> m_body;//身体部位对应图片容器
    std::vector<QPixmap> m_earsLeft;//左耳朵对应图片容器
    std::vector<QPixmap> m_earsRight;//右耳朵对应图片容器
    QPixmap m_eyes, m_stripe;//眼睛和眼部遮罩
    int m_face;//表情序号
    int m_faceSum;//表情数量
    std::vector<int> m_faceNum;//每个表情对应帧数与起始位置
    std::vector<QPixmap> m_movement;//表情图片容器
    int m_specialMove;//特殊动作序号
    std::vector<QPixmap> m_specialMovement;//特殊动作图片容器
    //各部件对应标签
    QLabel* m_bodyImage;
    QLabel* m_earsImage;
    QLabel* m_eyesImage;
    QLabel* m_stripeImage;
    int m_btnSwitch1, m_btnSwitch2;//菜单按钮显示开关
    int m_btnSize;//按钮大小
    QPushButton* m_closeBtn;//关闭按钮
    //QPushButton* dressBtn;//换装按钮
    //QPushButton* moreBtn;//展开更多按钮
    QPushButton* m_minBtn;//最小化按钮
    QPushButton* m_setBtn;//设置按钮
    QSystemTrayIcon* m_systemTray;//系统托盘

    SettingWidget* m_settingWidget;//设置窗口指针

};


#endif // __DESKTOP_PET_H__