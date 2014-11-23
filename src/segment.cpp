#include "segment.h"

Segment::Segment()
{
    clear();
}

void Segment::clear()
{
    segmentDiv=0;
    notes.clear();
    events.clear();
}

int Segment::getSegmentDiv() const
{
    return segmentDiv;
}

void Segment::setSegmentDiv(int div)
{
    segmentDiv=div;
    if(segmentDiv<1)segmentDiv=1;
}

void Segment::setSegmentDivChange(int delta)
{
    segmentDiv+=delta;
    if(segmentDiv<1)segmentDiv=1;
}

void Segment::setSegmentDivMultiply(int times)
{
    if(times<1)return;
    segmentDiv*=times;
    for(INote iter=notes.begin(); iter!=notes.end(); ++iter)
    {
        iter->num*=times;
    }
}

void Segment::setSegmentDivDivide(int times)
{
    if(times<2 || times>segmentDiv || segmentDiv%times!=0)return;
    segmentDiv/=times;
    for(INote iter=notes.begin(); iter!=notes.end();)
    {
        if(iter->num%times==0)
        {
            iter->num/=times;
            ++iter;
        }
        else
        {
            iter=notes.erase(iter);
        }
    }
}

void Segment::appendNote(const Note& note)
{
    notes.append(note);
}

void Segment::appendEvent(const Event& event)
{
    events.append(event);
}

void Segment::addNote(const Note& note)
{
    notes.removeOne(note);
    if(note.noteType==Note::none)return;
    INote iter=notes.begin();
    while(iter!=notes.end() && note>*iter)++iter;
    notes.insert(iter, note);
}

void Segment::addEvent(const Event& event)
{
    IEvent iter=events.begin();
    while(iter!=events.end() && !(event<*iter))++iter;
    events.insert(iter, event);
}

void Segment::setBeginState(const MapState &state)
{
    beginState=state;
}

const MapState &Segment::getBeginState() const
{
    return beginState;
}

MapState Segment::getNoteBeginState() const
{
    return MapState();
}

MapState Segment::getEndState() const
{
    return MapState();
}

void Segment::getNoteEventInfo(QList<NoteInfo> &noteList, QList<EventInfo> &eventList, const MapState &endState)
{

}

int Segment::incStateNoteNum(MapState *state, int deltaNum) const
{
    return 0;
}
