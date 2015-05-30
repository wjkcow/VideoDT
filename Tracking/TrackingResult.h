#ifndef TRACKING_RESULT_H
#define TRACKING_RESULT_H
#include <QHash>
#include <QSet>
#include <QListWidget>
#include <vector>
#include <QColor>
#include "Dectector/TrackerInfo.h"
#include <QRgb>


class TrackingResult{
public:
    void add_result(TrackingTask* task, QHash<int, QRect> &rects);
    void set_list_view(QListWidget* list_view_){
        list_view = list_view_;
        update_list_view();
    }

    void select_tracking_task(const QString&);
    int get_tracker_start();
    int get_tracker_end();
    QString get_tracker_name();
public slots:
    void edit_selected();
    void rect_drawed(const QRect& rect);
    void draw_frame_with_rect(Frame* frame);
    void save();
private:
    void update_list_view();

    QListWidget* list_view;
  //  std::map<TrackerInfo*, QColor> trackers;
    std::vector<TrackingTask> tasks;
    QHash<QRgb, TrackerInfo*> trackers;
    QHash<int, QHash<QRgb, QRect>> data;
};
#endif

