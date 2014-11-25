#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QTextStream>

#include "notemapdef.h"

class Event
{
public:

    friend class NoteMap;
    friend class MapState;

    enum EventType {unknown, start, end, hbscroll,
                    bpmchange, delay, measure, scroll,
                    gogostart, gogoend, barlineon, barlineoff};

    inline bool operator<(const Event& event) const
    {
        return num<event.num;
    }
    inline bool operator==(const Event& event) const
    {
        return num==event.num;
    }
    inline bool operator>(const Event& event) const
    {
        return num>event.num;
    }

    Event(int num=0);
    Event(QString str, int num=0);

    void setEventString(QString str);
    QString getEventString() const;
    QString getReformedEventString() const;

    EventType getEventType();

protected:

    int num;
    QString eventString;
    EventType eventType;
    int parameter_i_1, parameter_i_2;
    double parameter_d;
    char parameter_c;

};

struct EventInfo
{
    double beatOffset;
    double beatDistanceOffset;
    double scroll;
    bool isBarline;
    int segmentCount;
    int div;
    int num;
    Event *event;
};

#endif // EVENT_H
