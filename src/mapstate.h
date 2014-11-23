#ifndef MAPSTATE_H
#define MAPSTATE_H

#include <QList>

#include "notemapprivate.h"

#include "event.h"
#include "note.h"


class MapState
{
public:

    friend class NoteMap;
    friend class Segment;

    MapState(double _offset=0.0, double _bpm=120.0);

    double getCurrentTime() const;
    double getCurrentBeat() const;

    inline double calcOffset_segment(double deltaSegment)
    {
        return calcOffset_beat(deltaSegment*getTotalBeats());
    }

    inline double calcOffset_beat(double deltaBeat)
    {
        return deltaBeat/bpm*60;
    }

    inline double calcDeltaSegment_offset(double deltaOffset)
    {
        return calcBeatOffset(deltaOffset)/getTotalBeats();
    }

    inline double calcDeltaSegment_beat(double deltaBeat)
    {
        return deltaBeat/getTotalBeats();
    }

    inline double calcBeatOffset(double deltaOffset)
    {
        return deltaOffset/60*bpm;
    }

    inline double getTotalBeats()
    {
        return (double)measureNum*4/measureDiv;
    }

protected:

    void processEvent(const Event *event);
    void processEvent(const Event *event, int deltaNum);
    void processEvent(const Event *event, double deltaOffset);

    NoteMap* map;

    QList<Segment>::Iterator iterSegment;

    double offset;
    double beatOffset;

    bool editable;

    int segmentCount;

    int numNote;
    int segmentDiv;

    double bpm;
    double scroll;

    int measureDiv;
    int measureNum;

    bool isGGT;
    bool barlineHidden;


};

#endif // MAPSTATE_H
