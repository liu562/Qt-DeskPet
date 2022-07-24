#include "mainscene.h"
#include<QSplashScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/new/prefix2/whitecat/shime1.png"));
    MainScene w;
    w.show();
    return a.exec();
}
