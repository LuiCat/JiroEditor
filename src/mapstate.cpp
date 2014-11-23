#include "mapstate.h"

MapState::MapState(double _offset, double _bpm)
    :offset(_offset)
    ,beatOffset(0)
    ,editable(true)
    ,segmentCount(0)
    ,numNote(0)
    ,segmentDiv(1)
    ,bpm(_bpm)
    ,scroll(1.0)
    ,measureDiv(4)
    ,measureNum(4)
    ,isGGT(false)
    ,barlineHidden(false)
{

}

double MapState::getCurrentTime() const
{
    return offset;
}

double MapState::getCurrentBeat() const
{
    return beatOffset;
}

void MapState::processEvent(const Event *event)
{
    if(event==0)
        return;
    switch(event->eventType)
    {
    case Event::measure:
        if(event->num==0)
        {
            measureDiv=event->parameter_i_2;
            measureNum=event->parameter_i_1;
        }
        break;
    case Event::scroll:
        scroll=event->parameter_d;
        break;
    case Event::bpmchange:
        bpm=event->parameter_d;
        break;
    case Event::delay:
        offset+=event->parameter_d;
        break;
    case Event::gogostart:
        isGGT=true;
        break;
    case Event::gogoend:
        isGGT=false;
        break;
    case Event::barlineoff:
        barlineHidden=true;
        break;
    case Event::barlineon:
        barlineHidden=false;
        break;
    default:
        break;
    }
}

void MapState::processEvent(const Event *event, int deltaNum)
{
    if(!editable)return;
    numNote+=deltaNum;
    double deltaSegment=(double)deltaNum/segmentDiv;
    offset+=calcOffset_segment(deltaSegment);
    beatOffset+=getTotalBeats()*deltaSegment;
    processEvent(event);
}

void MapState::processEvent(const Event *event, double deltaOffset)
{
    offset+=deltaOffset;
    beatOffset+=calcBeatOffset(deltaOffset);
    editable=false;
    processEvent(event);
}

