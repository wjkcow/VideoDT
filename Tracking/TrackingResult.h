#ifndef TRACKING_RESULT_H
#define TRACKING_RESULT_H
#include <QHash>
#include <QSet>
#include <QListWidget>
#include <vector>
#include <QColor>
#include "Dectector/TrackerInfo.h"
#include "Dectector/TrackingTask.h"
#include "DecodeSplit/DSPipeline/FrameTypes.h"
#include <QRgb>
#include <QObject>
#include "mainwindow.h"
#include "VideoEdit/videoui.h"
#include "types.h"
class TrackingResult : public QObject{
    Q_OBJECT
public:
    TrackingResult(MainWindow* window_, VideoInfo* video_info_):window(window_), video_info(video_info_){};
    void add_result(TrackingTask* task, QHash<int, QRect> &rects);
    void set_list_view(QListWidget* list_view_){
        list_view = list_view_;
        update_list_view();
    }

    void select_tracking_task(const QString&);
    int get_tracker_start(){
        if(selected_task){
            return selected_task->from_frame;
        } else {
            return 0;
        }
    }
    int get_tracker_end(){
        if(selected_task){
            return selected_task->to_frame;
        } else {
            return 0;
        }
    }
    QString get_tracker_name(){
        if(selected_task){
            return selected_task->tracker->name;
        } else {
            return QString();
        }
    }
public slots:
    void set_current_frame(int n){
        current_frame = n;
    }
    void edit_selected();
    void rect_drawed(const QRect& rect);
    void draw_frame_with_rect(Frame* frame);
    void save();
private:
    void update_list_view();
    VideoInfo* video_info;
    MainWindow* window;
    int current_frame;
    QListWidget* list_view;
  //  std::map<TrackerInfo*, QColor> trackers;
    std::vector<TrackingTask> tasks;
    QHash<QRgb, TrackerInfo*> trackers;
    QHash<int, QHash<QRgb, QRect>> data;
    TrackingTask* selected_task = nullptr;
};
#endif

