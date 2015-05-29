#include "Dectector/TrackingTask.h"
#include "Dectector/Tracker.h"

QString TrackingTask::to_qstring(){
    return VideoSection::to_qstring() + "  " + tracker->name;
}
