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

void Segment::insertNote(MapState &state, Note::NoteType type)
{
    if(!state.editable||state.numNote<0||state.numNote>=)
        return;

    Note note;
    note.noteType=type;
    note.num=state.numNote;


}

void Segment::insertEvent(MapState &state, Note::NoteType type)
{

}

void Segment::insertNote(const Note& note)
{
    notes.removeOne(note);
    if(note.noteType==Note::none)return;
    INote iter=notes.begin();
    while(iter!=notes.end() && note>*iter)++iter;
    notes.insert(iter, note);
}

void Segment::insertEvent(const Event& event)
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
    MapState state=segmentState;
    int prevNum=0;
    for(ICEvent iter=events.cbegin(); iter!=events.cend() && iter->num<=0; ++iter)
    {
        state.processEvent(&*iter, iter->num-prevNum);
        prevNum=iter->num;
    }
    return state;
}

MapState Segment::getEndState() const
{
    MapState state=segmentState;
    int prevNum=0;

    for(IEvent iter=events.begin(); iter!=events.end(); ++iter)
    {
        state.processEvent(&state, &*iter, iter->num-prevNum);
        prevNum=iter->num;
    }

    state.processEvent(&state, 0, segmentDiv-prevNum);

    return state;
}

void Segment::findNearestState(MapState &state, bool front)
{

}

int Segment::incStateNoteNum(MapState &state, int deltaNum)
{
    return 0;
}

void Segment::getNoteEventInfo(QList<NoteInfo> &noteList, QList<EventInfo> &eventList)
{

}

void Segment::getNoteEventInfo(QList<NoteInfo> &noteList, QList<EventInfo> &eventList, const MapState &endState)
{

}
