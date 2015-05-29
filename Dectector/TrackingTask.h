#ifndef TRACKING_TASK
#define TRACKING_TASK
#include <QRect>
#include <QString>
#include "types.h"

class TrackerInfo;

class TrackingTask : public VideoSection{
public:
    TrackingTask(VideoSection section,TrackerInfo* tracker_, QRect rect_ = QRect(), bool need_edit_ = true):
        tracker(tracker_), VideoSection(section), rect(rect_), need_edit(need_edit_){
    }
    TrackingTask(int from, int to, TrackerInfo* tracker_, QRect rect_ = QRect(), bool need_edit_ = true):
        tracker(tracker_), VideoSection(from, to), rect(rect_), need_edit(need_edit_){
    }

    QString to_qstring();
    void change_start_frame(QRect rect_, int from_frame_){
        from_frame = from_frame_;
        rect = rect_;
        need_edit = false;
    }
    TrackerInfo* tracker;
    QRect rect;
    bool  need_edit;
};
#endif // TYPES

