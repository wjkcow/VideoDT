#ifndef FRAME_H
#define FRAME_H
#include <bitset>
#include "opencv2/opencv.hpp"

class Frame : public cv::Mat{
public:
    Frame(){}
    
    Frame(const Frame&) = delete;
    Frame(Frame&&) = delete;
    Frame& operator=(const Frame&) = delete;
    Frame& operator=(Frame&&) = delete;
    
    Frame* prev_frame = nullptr;
    int seq;
};

#endif
