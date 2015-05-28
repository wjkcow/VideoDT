#include "decodesplitresult.h"
#include "types.h"

DecodeSplitResult::DecodeSplitResult(VideoInfo* video_info_, const std::vector<int>& key_frames)
{
    video_info = video_info_;
    for(int i = 0; i < key_frames.size(); ++ i){
        if(i + 1 < key_frames.size()){
            data_.push_back(VideoSection(key_frames[i], key_frames[i + 1] - 1));
        } else {
            data_.push_back(VideoSection(key_frames[i], video_info->total_frame_n));
        }
    }
}

void DecodeSplitResult::update_list_view(){
    list_view->clear();
    for(int i = 0; i < data_.size(); i++){
        list_view->addItem(data_[i].to_qstring());
    }
}

void DecodeSplitResult::set_current_frame(int n){
    qDebug() << "cur_frame is set";
    current_frame = n;
}
void DecodeSplitResult::set_scence_start(){
    new_section_to_add.from_frame = current_frame;
}
void DecodeSplitResult::set_scene_end(){
    new_section_to_add.to_frame = current_frame;
}
void DecodeSplitResult::add_scene(){
    qDebug() << "new scene added";
    add_section(new_section_to_add);
    update_list_view();
}
void DecodeSplitResult::remove_selected_section(){
    qDebug() << "selected scene deleted";
    delete_section(selected);
    update_list_view();
}
