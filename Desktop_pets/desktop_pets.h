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
    void imageLoad();//����λͼƬ����
    void eyesMovementLoad();//�۲���������
    void specialMovementLoad();//���⶯���¼�
    inline void imageSet(QLabel* image, QPixmap map);//���ø���λͼƬ
    void eyesMovement();//�۲���������
    void specialMovement();//���⶯���¼�
    void saveData();//�洢����
    void initBtn();//��ʼ����ť
    void reInitBtn();//�޸Ĵ�Сʱ�ٴγ�ʼ����ť
    void closePets();//����رհ�ť�¼�
    void min();//�����С����ť�¼�
    void setting();//������ð�ť�¼�
    void btnSwitchRole();//����btnSwitch�л���ť״̬
    void initSystemTray();//��ʼ��ϵͳ����
    void systemTrayShow();//���ϵͳ�����¼�

private:
    Ui::Desktop_petsClass ui;

    //ʵ�ִ�����ק
    bool m_bPressed;
    QPoint m_mouseStartPoint;
    QPoint m_windowTopLeftPoint;

    int m_size;//���ʹ�С
    int m_bodyNum, m_earsNum;//����Ͷ����Ӧװ�����
    QTimer* m_timer;//��ʱ��:��ʱ��������
    std::vector<QPixmap> m_body;//���岿λ��ӦͼƬ����
    std::vector<QPixmap> m_earsLeft;//������ӦͼƬ����
    std::vector<QPixmap> m_earsRight;//�Ҷ����ӦͼƬ����
    QPixmap m_eyes, m_stripe;//�۾����۲�����
    int m_face;//�������
    int m_faceSum;//��������
    std::vector<int> m_faceNum;//ÿ�������Ӧ֡������ʼλ��
    std::vector<QPixmap> m_movement;//����ͼƬ����
    int m_specialMove;//���⶯�����
    std::vector<QPixmap> m_specialMovement;//���⶯��ͼƬ����
    //��������Ӧ��ǩ
    QLabel* m_bodyImage;
    QLabel* m_earsImage;
    QLabel* m_eyesImage;
    QLabel* m_stripeImage;
    int m_btnSwitch1, m_btnSwitch2;//�˵���ť��ʾ����
    int m_btnSize;//��ť��С
    QPushButton* m_closeBtn;//�رհ�ť
    //QPushButton* dressBtn;//��װ��ť
    //QPushButton* moreBtn;//չ�����ఴť
    QPushButton* m_minBtn;//��С����ť
    QPushButton* m_setBtn;//���ð�ť
    QSystemTrayIcon* m_systemTray;//ϵͳ����

    SettingWidget* m_settingWidget;//���ô���ָ��

};


#endif // __DESKTOP_PET_H__