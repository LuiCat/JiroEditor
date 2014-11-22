#ifndef NOTIFY_H
#define NOTIFY_H

#include <QThread>

#include <windows.h>

class Notify : public QThread
{
    Q_OBJECT
    HANDLE notifyEventHandle;
    int notifyTimes;
public:
    HANDLE getEventHandle() const;
    Notify();
    void singleNotify();
    void multipleNotify();
protected:
    void run();
signals:
    void notify();
};

#endif // NOTIFY_H
