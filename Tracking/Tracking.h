#ifndef TRACKING_H
#define TRACKING_H
#include <QObject>
#include "Tracking/TrackingResult.h"
class TrackingWorker;
class VideoInfo;
class Tracking : public QObject{
    Q_OBJECT
public:
    Tracking(std::vector<TrackingTask>& tasks_, VideoInfo* video_info_){
        tasks = tasks_;
        video_info = video_info_;
        tresult = new TrackingResult;
    }
    TrackingResult* result(){
        return tresult;
    }
    void run();
    void job_done(TrackingWorker* worker);
signals:
    void all_done();
public slots:
    void some_job_is_done();
private:
    void run_task();
    VideoInfo* video_info;
    std::vector<TrackingTask> tasks;
    QSet<TrackingWorker*> unfinshed_jobs;
    TrackingResult* tresult;
};


#endif

