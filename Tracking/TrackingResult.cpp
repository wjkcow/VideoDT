#include "Tracking/TrackingResult.h"
#include "Dectector/TrackerInfo.h"
#include "Dectector/TrackingTask.h"
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QRgb>
void TrackingResult::add_result(TrackingTask* task, QHash<int, QRect> &rects){
    tasks.push_back(*task);
    trackers[task->tracker->color.rgb()] = task->tracker;
  //  trackers[task->tracker] = task->tracker->color;
    for(auto i = rects.constBegin(); i != rects.constEnd(); i++){
        data[i.key()][task->tracker->color.rgb()] = i.value();
    }
}

void TrackingResult::update_list_view(){
    if(!list_view){
        return;
    }
    list_view->clear();
    for(int i = 0; i < tasks.size(); i++){
        list_view->addItem(tasks[i].to_qstring());
    }
    for(auto i = data.begin(); i != data.end(); i++){
        for(auto j = i.value().begin(); j != i.value().end(); j ++){
            qDebug() << i.key() << " " << j.value() <<" " << j.key();
        }
    }
}

void TrackingResult::select_tracking_task(const QString &str){
    for(int i = 0; i < tasks.size(); i++){
        if(tasks[i].to_qstring() == str){
            selected_task = &tasks[i];
        }
    }
}

void TrackingResult::edit_selected(){
    if(!selected_task){
        QMessageBox msgBox;
        msgBox.setText("Select a tracker first");
        msgBox.exec();
        return;
    }
    window->rt_draw_start();
    window->get_result_ui()->start_draw_rect(selected_task->tracker->color);
}

void TrackingResult::rect_drawed(const QRect &rect){
    window->rt_draw_end();

}

void TrackingResult::draw_frame_with_rect(Frame* frame){
    if(data.count(frame->seq)){
        QHash<QRgb, QRect> rects;
        for(auto i = data[frame->seq].begin(); i != data[frame->seq].end(); i++){
            int x = i.value().x();
            int y = i.value().y();
            int width = i.value().width();
            int height = i.value().height();
            x = double(x) *window->get_result_ui()->width()/ video_info->compress_x ;
            y = double(y) *window->get_result_ui()->height() / video_info->compress_y;
            width =  double(width) *window->get_result_ui()->width() / video_info->compress_x ;
            height = double(height) * window->get_result_ui()->height() / video_info->compress_y;
            rects.insert(i.key(), QRect(x,y,width, height));
        }

        window->get_result_ui()->show_frame(frame, rects);
    } else {
        window->get_result_ui()->show_frame(frame);
    }
}

void TrackingResult::save(){

}
