#include <QApplication>

#include "View/mainwindow.h"
#include "Data/listcontacts.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
