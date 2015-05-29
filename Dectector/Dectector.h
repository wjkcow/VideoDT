#ifndef DETECTOR_H
#define DETECTOR_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <QRect>
#include "FrameLibrary.h"
class TrackerInfo;
class TrackingTask;
struct VideoSection;


class Detector{
public:


    static std::vector<TrackingTask> generate_task(const std::string& type, FrameLibrary& flib,
                                            const std::vector<VideoSection>& sections,
                                             TrackerInfo* tracker);

private:
    static Detector* factory(const std::string& type);
    virtual bool detect(cv::Mat& frame, QRect& rect) = 0;
    virtual bool need_edit() = 0;
};


#endif // TYPES

