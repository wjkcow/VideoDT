#include "HistFilter.h"


double HistFilter::evaluate_frame_pair(Frame* frame){
    if(frame->prev_frame){
        return cv::compareHist(hist(*frame), hist(*frame->prev_frame), method);
    } else if(greater_is_similar) {
        return threshold + 1;
    } else {
        return threshold - 1;
    }
}

bool HistFilter::scene_threshold(double eva){
    if (greater_is_similar) {
        return eva < threshold;
    } else {
        return eva > threshold;
    }
}

cv::Mat HistFilter::hist(const cv::Mat& f){
    cv::Mat hsv;
    cvtColor(f, hsv, cv::COLOR_BGR2HSV);
    
    
    int h_bins = 50; int s_bins = 60;
    int histSize[] = {h_bins, s_bins };
    
    // hue varies from 0 to 179, saturation from 0 to 255
    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    
    const float* ranges[] = { h_ranges, s_ranges };
    
    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };
    
    
    /// Histograms
    cv::MatND hist;
    
    calcHist( &hsv, 1, channels, cv::Mat(), hist, 2, histSize, ranges, true, false );
    return hist;

}