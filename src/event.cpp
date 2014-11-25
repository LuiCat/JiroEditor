#include "event.h"




Event::Event(int _num)
    :num(_num)
    ,eventType(unknown)
    ,parameter_i_1(0)
    ,parameter_i_2(0)
    ,parameter_d(0.0)
    ,parameter_c(0)
{

}

Event::Event(QString str, int _num)
    :Event(_num)
{
    setEventString(str);
}

void Event::setEventString(QString str)
{
    eventString=str;

    QString name=str.section(' ', 0, 0);
    QString para=str.section(' ', 1);
    QStringList list;

    if(name.compare("#START")==0)
    {
        eventType=start;
    }
    else if(name.compare("#END")==0)
    {
        eventType=end;
    }
    else if(name.compare("#HBSCROLL")==0)
    {
        eventType=hbscroll;
    }
    else if(name.compare("#BPMCHANGE")==0)
    {
        eventType=bpmchange;
        parameter_d=parameters.toDouble();
    }
    else if(name.compare("#DELAY")==0)
    {
        eventType=delay;
        parameter_d=parameters.toDouble();
    }
    else if(name.compare("#GOGOSTART")==0)
    {
        eventType=gogostart;
    }
    else if(name.compare("#GOGOEND")==0)
    {
        eventType=gogoend;
    }
    else if(name.compare("#MEASURE")==0)
    {
        list=para.split('/');
        eventType=measure;
        parameter_i_1=list.at(0).toInt();
        parameter_i_2=list.at(1).toInt();
    }
    else if(name.compare("#SCROLL")==0)
    {
        eventType=scroll;
        parameter_d=parameters.toDouble();
    }
    else if(name.compare("#BARLINEON")==0)
    {
        eventType=barlineon;
    }
    else if(name.compare("#BARLINEOFF")==0)
    {
        eventType=barlineoff;
    }
    else
    {
        eventType=unknown;
    }

}

Event::EventType Event::getEventType()
{
    return eventType;
}


QString Event::getEventString() const
{
    return eventString;
}

QString Event::getReformedEventString() const
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
        str<<eventString;
    }
    return buf;
}
