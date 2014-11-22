#include "notify.h"

#include <QDebug>

Notify::Notify()
{
    notifyEventHandle=CreateEvent(0, false, false, 0);
    notifyTimes=0;
}

void Notify::singleNotify()
{
    notifyTimes=1;
    start();
}

void Notify::multipleNotify()
{
    notifyTimes=-1;
    start();
}

void Notify::run()
{
    while(notifyTimes!=0)
    {
        WaitForSingleObject(notifyEventHandle, INFINITE);
        emit notify();
        if(notifyTimes>0)--notifyTimes;
    }
}

HANDLE Notify::getEventHandle() const
{
    return notifyEventHandle;
}
