#include "Dectector/Dectector.h"
#include "Dectector/TrackingTask.h"
#include "DecodeSplit/DSPipeline/Utility.h"
#include "types.h"
#include "FrameLibrary.h"
using namespace std;

class ManualDectector : public Detector{
    bool detect(cv::Mat&, QRect&) override{return true;}
    bool need_edit() override{return true;}
};

Detector* Detector::factory(const std::string& type){
    if(type == "manual"){
        return new ManualDectector;
    } else {
        throw Exception("Exception: Unknown dectector");
    }
}
std::vector<TrackingTask> Detector::generate_task(const std::string& type,
                                                   FrameLibrary& flib,
                                                   const std::vector<VideoSection>& sections,
                                                    TrackerInfo* tracker){
    Detector* detector = factory(type);
    vector<TrackingTask> ret;
    cv::Mat frame;
    for(int i = 0; i < sections.size(); i++){
        QRect rect;
        for(int frame_n = sections[i].from_frame; frame_n < sections[i].to_frame; ++ frame_n){
            flib.get(frame_n, frame);
            if(detector->detect(frame, rect)){
                ret.push_back(TrackingTask(frame_n, sections[i].to_frame, tracker,
                                           rect, detector->need_edit()));
                break;
            }
        }
    }

    delete detector;
    return ret;
}

