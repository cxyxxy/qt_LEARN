#include "desktop_pets.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Desktop_pets w;
    w.show();
    return a.exec();
}
