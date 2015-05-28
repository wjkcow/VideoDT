#include "SplitFilter.h"
#include "Utility.h"
#include "FrameTypes.h"
#include "PHAFilter.h"
#include "HistFilter.h"

using namespace std;

void* SplitFilter::operator()(void* item){
    Frame* frame = (Frame*) item;
    frame_eva[frame->seq] = evaluate_frame_pair(frame);
    return item;
}

vector<int> SplitFilter::get_key_frames(){
    vector<int> key_frames;
    key_frames.push_back(0);
    for (int i = 0; i < sz; ++i) {
       // cout << i << ":" << frame_eva[i]  << endl;
        if (scene_threshold(frame_eva[i])) {
            if (i - key_frames.back() > 10) {
                key_frames.push_back(i);
            } else {
                key_frames.back() = i;
            }
        }
    }
    return key_frames;
}

shared_ptr<SplitFilter> SplitFilter::factory(const string& type,
                                const string& method,
                                int    n_frame,
                                double threshold){
    if (type == "pha") {
        return make_shared<PHAFilter>(n_frame, threshold);
    } if (type == "hist") {
        if (method == "Correlation") {
            if(threshold == -1.){
                threshold = 0.8;
            }
            return make_shared<HistFilter>(n_frame, threshold,
                                           CV_COMP_CORREL);
        } else if(method == "Chi-Square"){
            if(threshold == -1.){
                threshold = 10;
            }
            return make_shared<HistFilter>(n_frame, threshold,
                                           CV_COMP_CHISQR);
        } else if(method == "Intersection"){
            if(threshold == -1.){
                threshold = 10;
            }
            return make_shared<HistFilter>(n_frame, threshold,
                                           CV_COMP_INTERSECT);
        } else if(method == "Bhattacharyya distance"){
            if(threshold == -1.){
                threshold = 0.5;
            }
            return make_shared<HistFilter>(n_frame, threshold,
                                           CV_COMP_BHATTACHARYYA);
        } else {
            throw Exception("Unknown type of method for hist filter: " + method);
        }
    } else {
        throw Exception("Unknow type of Spliter");
    }
};


