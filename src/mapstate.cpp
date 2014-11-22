#include "mapstate.h"

MapState::MapState(double _offset, double _bpm)
    :offset(_offset)
    ,beatOffset(0)
    ,segmentCount(0)
    ,editable(true)
    ,numNote(0)
    ,bpm(_bpm)
    ,scroll(1.0)
    ,measureDiv(4)
    ,measureNum(4)
    ,isGGT(false)
    ,barlineHidden(false)
{

}

void Segment::processEvent(const Event *event, int deltaNum) const
{
    if(!editable)return;
    num+=deltaNum;
    processEvent(event, calcOffset_segment((double)deltaNum/segmentDiv));
    editable=true;
}

void Segment::processEvent(const Event *event, double deltaOffset) const
{
    offset+=deltaOffset;
    beatOffset+=calcBeatOffset(deltaOffset);
    editable=false;
    if(event==0)
        return;
    switch(event->eventType)
    {
    case Event::measure:
        if(event->num==0)
        {
            state->measureDiv=event->parameter_i_2;
            state->measureNum=event->parameter_i_1;
        }
        break;
    case Event::scroll:
        state->scroll=event->parameter_d;
        break;
    case Event::bpmchange:
        state->bpm=event->parameter_d;
        break;
    case Event::delay:
        state->offset+=event->parameter_d;
        break;
    case Event::gogostart:
        state->isGGT=true;
        break;
    case Event::gogoend:
        state->isGGT=false;
        break;
    case Event::barlineoff:
        state->barlineHidden=true;
        break;
    case Event::barlineon:
        state->barlineHidden=false;
        break;
    default:
        break;
    }
}

