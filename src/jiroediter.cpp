#include "jiroediter.h"

#include <QTextCodec>
#include <QKeyEvent>

JiroEditer::JiroEditer(QWidget *parent) :
    QMainWindow(parent)
{
    settings=new QSettings("config.ini", QSettings::IniFormat);
    settings->beginGroup("JiroEditer");

    bool flag1=true, flag2=true;
    windowWidth=settings->value("windowwidth").toInt(&flag1);
    windowHeight=settings->value("windowheight").toInt(&flag2);

    if(!flag1||!flag2)
    {
        windowWidth=0;
        windowHeight=0;
    }
    if(windowWidth<512)windowWidth=512;
    if(windowHeight<384)windowHeight=384;

    setGeometry(150, 50, windowWidth, windowHeight);
    setMinimumWidth(512);
    setMinimumHeight(384);

    setWindowIcon(QIcon(":/icon2"));
    setWindowTitle("JiroEditer");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));

}

void JiroEditer::closeEvent(QCloseEvent *e)
{
    windowWidth=width();
    windowHeight=height();
    settings->setValue("windowwidth", windowWidth);
    settings->setValue("windowheight", windowHeight);
    QMainWindow::closeEvent(e);
}

void JiroEditer::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
#ifdef _DEBUG
    case Qt::Key_Escape:
        exit(0);
#endif
    default:
        QMainWindow::keyPressEvent(e);
    }
}

void JiroEditer::resizeEvent(QResizeEvent *e)
{
    windowWidth=width();
    windowHeight=height();
    QMainWindow::resizeEvent(e);
}
