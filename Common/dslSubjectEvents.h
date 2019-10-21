#ifndef dslSubjectEventsH
#define dslSubjectEventsH
//---------------------------------------------------------------------------

namespace dsl
{

//The following events are events happening to a subject.
//The subject may emit any of these events to any observers using the
//notifyObserver pattern

enum SubjectEvent
{
    Ping                          = -1,
    SubjectBeingDestroyed         = 0,
    UpdatePosition                = 1,
//    const int UpdateDirection               = 2;
    UpdateOrientation             = 3,
//    const int UpdateVisualProperties        = 4;
    UpdateColor                   = 5,
    UpdateDimensionalProperties   = 6,
//    const int RemovedFromExplorer           = 7;
    UpdateRepresentation          = 8,
    UpdateTree			          = 9,

    UpdateCoreData                = 10,
    UpdateVisibility              = 11,
    UpdateSelectedProperties      = 12
};


}
#endif

