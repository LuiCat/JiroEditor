class MapState;

#ifndef MAPSTATE_H
#define MAPSTATE_H

#include <QList>

#include "notemap.h"
#include "note.h"

class MapState
{
public:

    explicit MapState(QObject *parent = 0);

    NoteMap* map;

    QList<QList<Note>>::Iterator iterSegment;
    QList<Note>::Iterator iterNote;

    double offset;
    double beatOffset;

    int segmentCount;

    bool editable;
    int num;

    double bpm;
    double scroll;

    int measureDiv;
    int measureNum;

    bool isGGT;
    bool barlineHidden;


};

#endif // MAPSTATE_H
