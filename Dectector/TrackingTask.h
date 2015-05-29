#ifndef TRACKING_TASK
#define TRACKING_TASK
#include <QRect>
#include "types.h"

class Tracker;

class TrackingTask : public VideoSection{
public:
    TrackingTask(VideoSection section,Tracker* tracker_, QRect rect_ = QRect(), bool need_edit_ = true):
        tracker(tracker_), VideoSection(section), rect(rect_), need_edit(need_edit_){
    }
    TrackingTask(int from, int to, Tracker* tracker_, QRect rect_ = QRect(), bool need_edit_ = true):
        tracker(tracker_), VideoSection(from, to), rect(rect_), need_edit(need_edit_){
    }

    void change_start_frame(QRect rect_, int from_frame_){
        from_frame = from_frame_;
        rect = rect_;
        need_edit = false;
    }
private:
    Tracker* tracker;
    QRect rect;
    bool  need_edit;
};
#endif // TYPES

