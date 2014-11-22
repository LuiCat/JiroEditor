class MapState;

#ifndef MAPSTATE_H
#define MAPSTATE_H

#include <QList>

#include "notemap.h"
#include "note.h"

class MapState
{
public:

    NoteMap* map;

    QList<QList<Note>>::Iterator iterSegment;

    double offset;
    double beatOffset;

    int segmentCount;

    bool editable;
    int numNote;

    double bpm;
    double scroll;

    int measureDiv;
    int measureNum;

    bool isGGT;
    bool barlineHidden;


    MapState(double _offset=0.0, double _bpm=120.0);




};

#endif // MAPSTATE_H
