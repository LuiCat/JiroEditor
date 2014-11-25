#ifndef SEGMENT_H
#define SEGMENT_H

#include <QList>

#include "notemapdef.h"

#include "mapstate.h"
#include "event.h"
#include "note.h"

class Segment
{
public:

    friend class NoteMap;
    friend class MapState;

    Segment();

    void clear();

    int getSegmentDiv() const;
    void setSegmentDiv(int div);
    void setSegmentDivChange(int delta);
    void setSegmentDivMultiply(int times);
    void setSegmentDivDivide(int times);

    void appendNote(const Note& note);
    void appendEvent(const Event& event);

    void insertNote(const Note& note);
    void insertEvent(const Event& event);

    void insertNote(MapState& state, Note::NoteType type);
    void insertEvent(MapState& state, Note::NoteType type);

    void setBeginState(const MapState& state);
    const MapState& getBeginState() const;
    MapState getNoteBeginState() const;
    MapState getEndState() const;

    void findNearestState(MapState& state, bool front);
    int incStateNoteNum(MapState& state, int deltaNum);
    int decStateNoteNum(MapState& state, int deltaNum);

    void getNoteEventInfo(QList<NoteInfo>& noteList, QList<EventInfo>& eventList);
    void getNoteEventInfo(QList<NoteInfo>& noteList, QList<EventInfo>& eventList, const MapState& endState);

protected:

    int segmentDiv;

    QList<Note> notes;
    QList<Event> events;

    MapState beginState;

};

#endif // SEGMENT_H
