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

class Desktop_pets : public QMainWindow
{
    Q_OBJECT

public:
    Desktop_pets(QWidget *parent = Q_NULLPTR);


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


};


#endif // __DESKTOP_PET_H__