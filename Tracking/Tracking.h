#ifndef TRACKING_H
#define TRACKING_H
#include <QObject>
#include <QFuture>
#include <QHash>
#include <QFutureWatcher>
#include <QRect>
#include "opencv2/opencv.hpp"
#include "Tracking/TrackingResult.h"
#include "Dectector/TrackingTask.h"

class VideoInfo;
class Tracking;
class TrackingWorker : QObject{
    Q_OBJECT
public:
    TrackingWorker(TrackingTask task,const QString& path_,Tracking* tracking_, TrackingResult* result_);
    void run();
public slots:
    void task_done();
private:
    void parallel_task_run();
    cv::Rect to_cv_rect(const QRect& rect){
        return cv::Rect(rect.x(), rect.y(), rect.width(), rect.height());
    }
    QRect to_q_rect(const cv::Rect& rect){
        return QRect(rect.x, rect.y, rect.width, rect.height);
    }
    TrackingTask m_task;
    QString path;
    Tracking* tracking;
    TrackingResult* result;
    QHash<int, QRect> results;
    QFuture<void> m_future;
    QFutureWatcher<void> m_future_watcher;
};
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

private:
    void run_task();
    VideoInfo* video_info;
    std::vector<TrackingTask> tasks;
    QSet<TrackingWorker*> unfinshed_jobs;
    TrackingResult* tresult;
};


#endif

