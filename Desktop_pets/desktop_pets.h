#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_desktop_pets.h"

class Desktop_pets : public QMainWindow
{
    Q_OBJECT

public:
    Desktop_pets(QWidget *parent = Q_NULLPTR);

private:
    Ui::Desktop_petsClass ui;
};
