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
    void add_result(TrackingTask* task,QHash<int, QRect> &rects);
    void set_list_view(QListWidget* list_view_){

    }
private:
    void update_list_view();

    QListWidget* list_view;
  //  std::map<TrackerInfo*, QColor> trackers;
    QHash<QRgb, TrackerInfo*> trackers;
    QHash<int, QHash<QRgb, QRect>> data;
};
#endif

