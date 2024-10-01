#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget* parent) :
    QWidget(parent)
{
    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 50, 50);
    setMask(bmp);
    setWindowOpacity(0.95);//设置透明度
    setStyleSheet("background-color:white;");

    Qt::WindowFlags m_flags = windowFlags();//保持窗口置顶1
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);//保持窗口置顶2

    this->setWindowIcon(QIcon(":/images/icon/setting.png")); //设置窗口图标

}

SettingWidget::~SettingWidget()
{
    
}

void SettingWidget::setSize(int size)
{
    m_desktopPetSize = size;

    QFont ft;
    ft.setPointSize(12);
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::blue);
    m_sizeNum = new QLabel(this);
    m_sizeNum->move(120, 100);
    m_sizeNum->resize(120, 20);
    m_sizeNum->setFont(ft);
    m_sizeNum->setPalette(pa);
    m_sizeNum->setNum(m_desktopPetSize);
    m_sizeNum->show();
}

int SettingWidget::getSize()
{
    return m_desktopPetSize;
}

void SettingWidget::on_sizeSlider_valueChanged(int value)
{
    m_desktopPetSize = value;
    m_sizeNum->setNum(m_desktopPetSize);
}
