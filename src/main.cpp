#include <QApplication>

#include "jiroediter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    JiroEditer jiro;

    jiro.show();

    return a.exec();
}
