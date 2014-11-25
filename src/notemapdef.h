#ifndef NOTEMAPPRIVATE_H
#define NOTEMAPPRIVATE_H

#include <QList>

class NoteMap;

class Segment;

class Note;
class Event;

class NoteInfo;
class EventInfo;

class MapState;

typedef QList<Segment>::Iterator ISegment;
typedef QList<Note>::Iterator INote;
typedef QList<Event>::Iterator IEvent;
typedef QList<NoteInfo>::Iterator INoteInfo;
typedef QList<EventInfo>::Iterator IEventInfo;

typedef QList<Segment>::ConstIterator ICSegment;
typedef QList<Note>::ConstIterator ICNote;
typedef QList<Event>::ConstIterator ICEvent;
typedef QList<NoteInfo>::ConstIterator ICNoteInfo;
typedef QList<EventInfo>::ConstIterator ICEventInfo;


#endif // NOTEMAPPRIVATE_H
