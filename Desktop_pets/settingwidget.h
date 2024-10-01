#ifndef  __DESKTOP_PET_SETTINGWIDGET_H__
#define  __DESKTOP_PET_SETTINGWIDGET_H__

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QIcon>

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    void setSize(int);//����sizeֵ

    int getSize();//�ⲿ��ȡsizeֵ

private slots:


    void on_sizeSlider_valueChanged(int value);//�������ۺ���

private:

    int m_desktopPetSize;//haro��С����

    QLabel *m_sizeNum;//��ʾsizeֵ��ǩ
};

#endif //  __DESKTOP_PET_SETTINGWIDGET_H__
