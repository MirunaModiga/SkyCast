//#include "qpushbutton.h"
#include "skycast.h"

#include <QApplication>
#include "tcpclient.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//obiectul aplicatiei

    tcpclient::getInstance().start("192.168.114.224",2002);
    SkyCast w;
    w.show();
    w.resize(900,600);
    return a.exec();
}
