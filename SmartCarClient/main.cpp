#include "animation.h"
#include <QApplication>
#include "network.h"
#include "handledata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    animation w;

    Network::getNetPtr()->initNetwork();
    //HandleData h;
    w.show();
    w.initAll();
    return a.exec();
}
