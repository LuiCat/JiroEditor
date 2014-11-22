#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QTextStream>

struct Event
{
    int num;
    enum EventType {unknown, bpmchange, delay,
                    gogostart, gogoend, measure, scroll,
                    barlineon, barlineoff }
               eventType;
    int parameter_i_1, parameter_i_2;
    double parameter_d;
    char parameter_c;

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

    inline QString getEventString()
    {
        QString buf="";
        QTextStream str(&buf);
        switch(eventType){
        case Event::bpmchange:
            str<<"#BPMCHANGE "<<parameter_d;
            break;
        case Event::gogostart:
            str<<"#GOGOSTART";
            break;
        case Event::gogoend:
            str<<"#GOGOEND";
            break;
        case Event::measure:
            str<<"#MEASURE "<<parameter_i_1<<"/"<<parameter_i_2;
            break;
        case Event::scroll:
            str<<"#SCROLL "<<parameter_d;
            break;
        case Event::barlineon:
            str<<"#BARLINEON";
            break;
        case Event::barlineoff:
            str<<"#BARLINEOFF";
            break;
        default:
            break;
        }
        return buf;
    }

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
