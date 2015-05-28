#include "PHAFilter.h"
#include <bitset>


double PHAFilter::evaluate_frame_pair(Frame* frame){
    if (!frame->prev_frame) {
        return 0;
    }
    return diff(calc_pha(*frame), calc_pha(*frame->prev_frame));
}
bool  PHAFilter::scene_threshold(double eva){
    return eva > threshold;
}

unsigned PHAFilter::calc_pha(const cv::Mat& src){
    unsigned pha = 0;
    cv::Mat img;
    cv::resize(src, img, cv::Size{8,8});
    cv::cvtColor(img, img, CV_BGR2GRAY);
    uchar *pData;
    for(int i=0;i<img.rows;i++)
    {
        pData = img.ptr<uchar>(i);
        for(int j=0;j<img.cols;j++)
        {
            pData[j]=pData[j]/4;
        }
    }
    
    int average = mean(img).val[0];
    
    cv::Mat mask = (img>=(uchar)average);
    
    for(int i=0;i<mask.rows;i++)
    {
        pData = mask.ptr<uchar>(i);
        for(int j=0;j<mask.cols;j++)
        {
            if(pData[j])
                pha |= 1 << (i * mask.rows + j);
                }
    }
    return pha;
}

int PHAFilter::diff(unsigned left, unsigned right){
    return static_cast<int>(std::bitset<64>(left ^ right).count());
}
