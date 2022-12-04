#include "mainwindow.h"

#include <QApplication>
#include <qstylefactory.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setStyle(QStyleFactory::create("WindowsXP"));
    return a.exec();
}
