#ifndef HIST_FILTER_H
#define HIST_FILTER_H

#include "SplitFilter.h"
#include "opencv2/opencv.hpp"
#include "FrameTypes.h"

class HistFilter : public SplitFilter{
public:
    HistFilter(int n_frame, double threshold_,
               int method_ = CV_COMP_CORREL):
               SplitFilter{n_frame}, threshold{threshold_},
               method(method_)
                {
                    if(method == CV_COMP_CORREL || method == CV_COMP_INTERSECT){
                        greater_is_similar  = true;
                    } else {
                        greater_is_similar  = false;
                    }
                };
    
protected:
    double evaluate_frame_pair(Frame* frame) override;
    bool   scene_threshold(double) override;

private:
    cv::Mat hist(const cv::Mat& f);
    int method;
    double threshold;
    bool greater_is_similar;
};

#endif 
