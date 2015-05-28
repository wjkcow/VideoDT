#ifndef DECODESPLITRESULT_H
#define DECODESPLITRESULT_H
#include <QObject>
#include <vector>
#include <algorithm>
#include <cassert>
#include "types.h"

class DecodeSplitResult : public QObject
{
    Q_OBJECT
public:
    DecodeSplitResult(VideoInfo* video_info_, const std::vector<int>& key_frames );
    const std::vector<VideoSection>& get_data(){
        return data_;
    }
    void add_section(VideoSection vs_section){
        auto ite = std::lower_bound(data_.begin(), data_.end(), vs_section, [](const VideoSection& vs_l,
                                    const VideoSection& vs_r){
            return vs_l.from_frame < vs_r.from_frame;
        });
        data_.insert(ite, vs_section);

    }
    void delete_section(VideoSection vs){
        auto ite = std::lower_bound(data_.begin(), data_.end(), vs, [](const VideoSection& vs_l,
                                    const VideoSection& vs_r){
            return vs_l.from_frame < vs_r.from_frame;
        });
        if(ite->from_frame != vs.from_frame || ite->to_frame != vs.from_frame){
            assert(0);
        }
        data_.erase(ite);
    }
    void select_scene(VideoSection section){
        selected = section;
    }
    int get_scene_start(){
        return selected.from_frame;
    }
    int get_scene_end(){
        return selected.to_frame;
    }


public slots:
    void set_current_frame(int n){
        current_frame = n;
    }
    void set_scence_start(){
        new_section_to_add.from_frame = current_frame;
    }
    void set_scene_end(){
        new_section_to_add.to_frame = current_frame;
    }
    void add_scene(){
        add_section(new_section_to_add);
    }
private:
    std::vector<VideoSection> data_;
    VideoInfo* video_info;
    VideoSection selected;
    int current_frame;
    VideoSection new_section_to_add;
};

#endif // DECODESPLITRESULT_H
