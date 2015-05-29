#ifndef TRACKING_TASK_MANAGER_H
#define TRACKING_TASK_MANAGER_H
#include <vector>
#include <QString>
#include <QListWidget>
#include <QHash>
#include "types.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "Dectector/Dectector.h"
#include "Dectector/TrackingTask.h"
class Tracker;
class TTaskManager{
public:
    TTaskManager(DecodeSplitResult* ds_result):scenes(ds_result->get_data()),
        video_info(ds_result->video_info){
    }
    void add_tracker(const QString& dectector_type, const QString& tracker_name);
    void set_list_view(QListWidget* widget){list_view = widget;}
    void update_list_view();
private:
    std::vector<VideoSection> scenes;
    std::vector<TrackingTask> candidate_tasks;
    QListWidget* list_view;
    VideoInfo* video_info;
    QHash<QString, Tracker*> trackers_name;

};


#endif // TYPES

