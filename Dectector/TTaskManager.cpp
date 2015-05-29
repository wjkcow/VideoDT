#include "TTaskManager.h"
#include "Dectector/Dectector.h"
#include "Dectector/Tracker.h"
#include "FrameLibrary.h"
#include <vector>
#include <QColor>
#include <QDebug>
#include <QMessageBox>

QColor color_set[] = {Qt::green, Qt::blue, Qt::red,
                      Qt::cyan, Qt::magenta, Qt::yellow};
int    color_cur_idx = 0;
int    color_set_size = 6;

void TTaskManager::add_tracker(const QString& dectector_type,
                  const QString& tracker_name){

    Tracker* new_tracker = new Tracker(tracker_name, color_set[color_cur_idx]);

//    qDebug() << (video_info->tmp_path + video_info->tmp_file_fmt) ;
    if(!tracker_name.size() || trackers_name.count(tracker_name)){
        QMessageBox msgBox;
        msgBox.setText("Invalid name");
        msgBox.exec();
        return;
    }
    trackers_name.insert(tracker_name, new_tracker);
    color_cur_idx = (color_cur_idx + 1) % color_set_size;

    FrameLibrary flib(video_info->tmp_path + video_info->tmp_file_fmt);

    auto new_tasks = Detector::generate_task(dectector_type.toStdString(), flib, scenes, new_tracker);

    for(int i = 0; i < new_tasks.size(); i++){
        candidate_tasks.push_back(new_tasks[i]);
    }
    update_list_view();
}

void TTaskManager::update_list_view(){
    if(!list_view){
        return;
    }
    list_view->clear();
    for(int i = 0; i < candidate_tasks.size(); i++){
        list_view->addItem(candidate_tasks[i].to_qstring());
    }
}
