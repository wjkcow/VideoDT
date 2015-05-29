#ifndef FRAMELIBRARY_H
#define FRAMELIBRARY_H

#include <opencv2/opencv.hpp>
class FrameLibrary
{
public:
    FrameLibrary();
    cv::Mat get(int n);
};

#endif // FRAMELIBRARY_H
