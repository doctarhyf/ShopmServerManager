#include "widget.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("K9Soft");
    QCoreApplication::setOrganizationDomain("k9soft.com");
    QCoreApplication::setApplicationName("Shopm Server Manager");


    Widget w;
    w.show();

    return a.exec();
}
