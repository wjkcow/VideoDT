#include "Tracking/TrackingResult.h"
#include "Dectector/TrackerInfo.h"
#include "Dectector/TrackingTask.h"
#include <QColor>
#include <QRgb>
void TrackingResult::add_result(TrackingTask* task, QHash<int, QRect> &rects){
    trackers[task->tracker->color.rgb()] = task->tracker;
  //  trackers[task->tracker] = task->tracker->color;
    for(auto i = rects.constBegin(); i < rects.constEnd(); i++){
        data[i][task->tracker->color.rgb()] = i.value();
    }
}
