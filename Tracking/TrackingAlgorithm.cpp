#include "Tracking/TrackingAlgorithm.h"
#include "DecodeSplit/DSPipeline/Utility.h"
#include "Tracking/OpenTLD/src/libopentld/tld/TLD.h"
#include "Tracking/CppMT/CMT.h"
class TLD : public TrackingAlgorithm{
public:
    void initialize(const cv::Mat& mat, QRect rect){
        m_rect = to_cv_rect(rect);
        Mat im_gray;
        cvtColor(mat, im_gray, CV_BGR2GRAY);
        tld.selectObject(im_gray, &m_rect);
    }

    QRect processFrame(const cv::Mat& mat){
        tld.processImage(mat);
        return to_q_rect(*tld.currBB);
    }
private:
    cv::Rect m_rect;
    tld::TLD tld;
};

class CMT : public TrackingAlgorithm{
    void initialize(const cv::Mat& mat, QRect rect){
        Mat im_gray;
        cvtColor(mat, im_gray, CV_BGR2GRAY);
        cmt.initialize(im_gray, to_cv_rect(rect));
    }

    QRect processFrame(const cv::Mat& mat){
        Mat im_gray;
        cvtColor(mat, im_gray, CV_BGR2GRAY);
        cmt.processFrame(im_gray);
        return to_q_rect(cmt.bb_rot.boundingRect());
    }
private:
    cmt::CMT cmt;
};



TrackingAlgorithm* TrackingAlgorithm::factory(const QString& type){
    if(type == QString("TLD")){
        return new TLD;
    } else if (type == QString("CMT")){
        return new CMT;
    } else {
        throw Exception("Error: Unknown tracking algorithm");
    }
}


