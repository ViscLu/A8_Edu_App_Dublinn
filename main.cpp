#include "cookmaingameroom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    CookMainGameRoom w(model);
    w.show();
    return a.exec();
}
