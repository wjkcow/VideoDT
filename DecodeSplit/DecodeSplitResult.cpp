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
    for(int i = 0; i < data_.size(); i++){
        qDebug() << data_[i].to_qstring();
    }
}

void DecodeSplitResult::update_list_view(){
    list_view->clear();
    for(int i = 0; i < data_.size(); i++){
        list_view->addItem(data_[i].to_qstring());
    }
}
