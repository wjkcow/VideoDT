#include "Tracking/TrackingResult.h"
#include "Dectector/TrackerInfo.h"
#include "Dectector/TrackingTask.h"
#include <QColor>
#include <QDebug>
#include <QRgb>
void TrackingResult::add_result(TrackingTask* task, QHash<int, QRect> &rects){
    tasks.push_back(*task);
    trackers[task->tracker->color.rgb()] = task->tracker;
  //  trackers[task->tracker] = task->tracker->color;
    for(auto i = rects.constBegin(); i != rects.constEnd(); i++){
        data[i.key()][task->tracker->color.rgb()] = i.value();
    }
}

void TrackingResult::update_list_view(){
    if(!list_view){
        return;
    }
    list_view->clear();
    for(int i = 0; i < tasks.size(); i++){
        list_view->addItem(tasks[i].to_qstring());
    }
    for(auto i = data.begin(); i != data.end(); i++){
        for(auto j = i.value().begin(); j != i.value().end(); j ++){
            qDebug() << i.key() << " " << j.value() <<" " << j.key();
        }
    }
}
