#ifndef TRACKING_ALGORITHM
#define TRACKING_ALGORITHM

#include <QString>
#include <QRect>
#include "opencv2/opencv.hpp"

class TrackingAlgorithm{
public:
    static TrackingAlgorithm* factory(const QString& type);
    virtual void initialize(const cv::Mat& mat, QRect rect) = 0;
    virtual QRect processFrame(const cv::Mat& mat) = 0;
protected:
    cv::Rect to_cv_rect(const QRect& rect){
        return cv::Rect(rect.x(), rect.y(), rect.width(), rect.height());
    }
    QRect to_q_rect(const cv::Rect& rect){
        return QRect(rect.x, rect.y, rect.width, rect.height);
    }
};

#endif

