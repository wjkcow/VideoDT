#ifndef TRACKING_TASK_MANAGER_H
#define TRACKING_TASK_MANAGER_H
#include <vector>
#include <QString>
#include "types.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "Dectector/Dectector.h"
#include "Dectector/TrackingTask.h"

class TTaskManager{
public:
    TTaskManager(DecodeSplitResult* ds_result):scenes(ds_result->get_data()){
    }
    void add_tracker(const QString& dectector_type, const QString& tracker_name);
private:
    std::vector<VideoSection> scenes;
    std::vector<TrackingTask> tasks;
};


#endif // TYPES

