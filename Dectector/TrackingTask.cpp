#include "Dectector/TrackingTask.h"
#include "Dectector/TrackerInfo.h"

QString TrackingTask::to_qstring(){
    return VideoSection::to_qstring() + "  " + tracker->name;
}
