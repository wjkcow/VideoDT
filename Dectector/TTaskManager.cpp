#include "TTaskManager.h"
#include "Dectector/Dectector.h"
#include "Dectector/TrackerInfo.h"
#include "FrameLibrary.h"
#include <vector>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QRgb>
#include "VideoEdit/videoui.h"
#include "DecodeSplit/DSPipeline/FrameTypes.h"
QColor color_set[] = {Qt::green, Qt::blue, Qt::red,
                      Qt::cyan, Qt::magenta, Qt::yellow};
int    color_cur_idx = 0;
int    color_set_size = 6;

void TTaskManager::add_tracker(const QString& dectector_type,
                  const QString& tracker_name){

    TrackerInfo* new_tracker = new TrackerInfo(tracker_name, color_set[color_cur_idx]);

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
    update_ctask_list_view();
}

void TTaskManager::update_ctask_list_view(){
    if(!ctask_list_view){
        return;
    }
    ctask_list_view->clear();
    for(int i = 0; i < candidate_tasks.size(); i++){
        ctask_list_view->addItem(candidate_tasks[i].to_qstring());
    }
}
void TTaskManager::update_task_list_view(){
    if(!task_list_view){
        return;
    }
    task_list_view->clear();
    for(int i = 0; i < tasks.size(); i++){
        task_list_view->addItem(tasks[i].to_qstring());
    }
}

void TTaskManager::draw_frame_with_rect(Frame* frame){
   // std::vector<QPair<QColor, QRect>> rects;
 //   rects.push_back(QPair<QColor,QRect>(Qt::green, QRect(10,10,50,50)));
    QHash<QRgb, QRect>rects;
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        if(frame->seq == task.from_frame && !task.need_edit){
     //       rects.push_back(QPair<QColor,QRect>(task.tracker->color, task.rect));
            rects[task.tracker->color.rgb()] = task.rect;
            vui->show_frame(frame, rects);
            return;
        }
    }

    vui->show_frame(frame);

}

void TTaskManager::select_ctracking_task(const QString& str){
    for(int i = 0; i < candidate_tasks.size(); i++){
        if(str == candidate_tasks[i].to_qstring()){
            selected_ctask_idx = i;
        }
    }
}

void TTaskManager::remove_selected_task(){
   auto selected = task_list_view->selectedItems();
   for(int i = 0; i < selected.size(); i ++){
       for(int j = 0; j < tasks.size(); j++){
           if(selected[i]->text() == tasks[j].to_qstring()){
                tasks.erase(tasks.begin() + j);
           }
       }
   }
   update_task_list_view();
}
void TTaskManager::edit_selected(){
    qDebug() << "Nothing is selected" <<  selected_ctask_idx;

    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        task.from_frame = current_frame;
        window->te_draw_start();
        vui->start_draw_rect(task.tracker->color);
        update_ctask_list_view();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Select a candidate task first");
        msgBox.exec();
        return;
    }
}
void TTaskManager::rect_drawed(const QRect& rect){
    qDebug() << "rect received";
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        task.need_edit = false;
        int x,y,height, width;
        rect.getRect(&x,&y,&width,&height);
       // qDebug() << "new rect " << rect ;
        // x width
        x = double(x) * video_info->compress_x / vui->width();
        y = double(y) * video_info->compress_y / vui->height();
        width =  double(width) * video_info->compress_x / vui->width();
        height = double(height) * video_info->compress_y / vui->height();
        task.rect = QRect(x,y,width, height);
        qDebug() << "new rect set to task " << task.rect ;
    }
    window->te_draw_end();
}
void TTaskManager::set_end_frame_to_selected(){
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        task.to_frame = current_frame;
        update_ctask_list_view();
    }
}

void TTaskManager::add_to_task(){
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        if(task.need_edit){
            QMessageBox msgBox;
            msgBox.setText("You must edit this task");
            msgBox.exec();
            return;
        }
        tasks.push_back(task);
        update_task_list_view();
    }
}

int TTaskManager::get_tracker_start(){
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        return task.from_frame;
    }
    return 0;
}
int TTaskManager::get_tracker_end(){
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        return task.to_frame;
    }
    return 0;
}
QString TTaskManager::get_tracker_name(){
    if(selected_ctask_idx >= 0 && selected_ctask_idx < candidate_tasks.size()){
        TrackingTask& task = candidate_tasks[selected_ctask_idx];
        return task.tracker->name;
    }
    return QString();
}
