#ifndef FRAMELIBRARY_H
#define FRAMELIBRARY_H

#include <opencv2/opencv.hpp>
#include <QString>
class FrameLibrary
{
public:
    FrameLibrary(const QString& tmp_path);
    void get(int n, cv::Mat& frames);
private:
    QString tmp_path;
};

#endif // FRAMELIBRARY_H
