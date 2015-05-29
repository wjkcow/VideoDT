#include "TTaskManager.h"
#include "Dectector/Dectector.h"
#include <QColor>
#include "Dectector/Tracker.h"
QColor color_set[] = {Qt::green, Qt::blue, Qt::red,
                      Qt::cyan, Qt::magenta, Qt::yellow};
int    color_cur_idx = 0;
int    color_set_size = 6;

void TTaskManager(const QString& dectector_type,
                  const QString& tracker_name){
    Tracker* new_tracker = new Tracker(tracker_name, color_set[color_cur_idx]);
    color_cur_idx = (color_cur_idx + 1) % color_set_size;


}
