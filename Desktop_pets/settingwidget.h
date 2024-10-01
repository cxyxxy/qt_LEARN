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

    void setSize(int);//设置size值

    int getSize();//外部获取size值

private slots:


    void on_sizeSlider_valueChanged(int value);//滑动条槽函数

private:

    int m_desktopPetSize;//haro大小参数

    QLabel *m_sizeNum;//显示size值标签
};

#endif //  __DESKTOP_PET_SETTINGWIDGET_H__
