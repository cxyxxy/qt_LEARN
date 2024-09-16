#include "qtwidgetsapplication1.h"
#include "stdafx.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setFixedSize(2000, 1500);

    learn_timer_widget = new QWidget();
    learn_timer_widget->setFixedSize(1000, 750);
    learn_timer_widget->setStyleSheet("background-color:rgb(35, 169, 242);");
    learn_timer_widget->hide();
    learn_timer_pushbutton = new QPushButton(this);
    learn_timer_pushbutton->setGeometry(30, 0, 100, 50);
    learn_timer_pushbutton->setText(QString::fromLocal8Bit("¶¨Ê±Æ÷"));
    connect(learn_timer_pushbutton, &QPushButton::clicked, learn_timer_widget, &QWidget::show);

    //
}
