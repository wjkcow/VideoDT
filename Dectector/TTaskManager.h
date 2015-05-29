#ifndef TRACKING_TASK_MANAGER_H
#define TRACKING_TASK_MANAGER_H
#include <vector>
#include <QString>
#include <QListWidget>
#include <QHash>
#include <QObject>
#include "mainwindow.h"
#include "types.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "Dectector/Dectector.h"
#include "Dectector/TrackingTask.h"
class Tracker;
class Frame;
class VideoUI;
class TTaskManager : public QObject{
    Q_OBJECT
public:
    TTaskManager(DecodeSplitResult* ds_result, VideoUI* vui_, MainWindow* window_):window(window_),scenes(ds_result->get_data()),
        video_info(ds_result->video_info), vui(vui_){
    }
    void add_tracker(const QString& dectector_type, const QString& tracker_name);
    void set_ctask_list_view(QListWidget* widget){ctask_list_view = widget;}
    void update_ctask_list_view();
    void set_task_list_view(QListWidget* widget){task_list_view = widget;}
    void update_task_list_view();
    int  get_tracker_start();
    int  get_tracker_end();
    QString get_tracker_name();
    void select_ctracking_task(const QString&);
public slots:
    void set_current_frame(int n){current_frame = n;}
    void draw_frame_with_rect(Frame* frame);
    void edit_selected();
    void rect_drawed(const QRect& rect);
    void set_end_frame_to_selected();
    void add_to_task();
    void remove_selected_task();

private:
    int current_frame;
    MainWindow* window;
    std::vector<VideoSection> scenes;
    std::vector<TrackingTask> candidate_tasks;
    std::vector<TrackingTask> tasks;

    QListWidget* ctask_list_view;
    QListWidget* task_list_view;

    VideoInfo* video_info;
    VideoUI* vui;
    QHash<QString, Tracker*> trackers_name;
    int selected_ctask_idx = -1;



};


#endif // TYPES

