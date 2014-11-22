#include "mapstate.h"

MapState::MapState(double _offset=0.0, double _bpm=120.0)
    :offset(_offset)
    ,beatOffset(0)
    ,segmentCount(0)
    ,editable(true)
    ,num(0)
    ,bpm(_bpm)
    ,scroll(1.0)
    ,measureDiv(4)
    ,measureNum(4)
    ,isGGT(false)
    ,barlineHidden(false)
{

}
