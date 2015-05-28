#ifndef DECODESPLITRESULT_H
#define DECODESPLITRESULT_H

#include <vector>
#include <algorithm>
#include <cassert>
#include "types.h"

class DecodeSplitResult
{
public:
    DecodeSplitResult(const std::vector<int>& key_frames);
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
    void modify_section(VideoSection vs_from, VideoSection vs_to){
        auto ite = std::lower_bound(data_.begin(), data_.end(), vs_from, [](const VideoSection& vs_l,
                                    const VideoSection& vs_r){
            return vs_l.from_frame < vs_r.from_frame;
        });
        if(ite->from_frame != vs_to.from_frame || ite->to_frame != vs_to.from_frame){
            assert(0);
        }
        data_.erase(ite);
        add_section(vs_to);
    }
private:
    std::vector<VideoSection> data_;

};

#endif // DECODESPLITRESULT_H
