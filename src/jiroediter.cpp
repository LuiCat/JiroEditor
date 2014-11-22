#include "jiroediter.h"

#include <QTextCodec>

JiroEditer::JiroEditer(QWidget *parent) :
    QMainWindow(parent)
{
    windowWidth=512;
    windowHeight=384;

    setGeometry(150, 50, windowWidth, windowHeight);
    setMinimumWidth(512);
    setMinimumHeight(384);

    setWindowIcon(QIcon(":/icon2"));
    setWindowTitle("JiroEditer");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));

}
