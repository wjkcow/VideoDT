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
#include "mainwindow.h"
struct VideoInfo;
class Tracking;
class TrackingWorker : QObject{
    Q_OBJECT
public:
    TrackingWorker(TrackingTask task,const QString& path_,Tracking* tracking_, TrackingResult* result_,
                   const QString& type_);
    void run();
public slots:
    void task_done();
private:
    void parallel_task_run();
    TrackingTask m_task;
    QString path;
    Tracking* tracking;
    TrackingResult* result;
    QHash<int, QRect> results;
    QFuture<void> m_future;
    QFutureWatcher<void> m_future_watcher;
    QString type;
};
class Tracking : public QObject{
    Q_OBJECT
public:
    Tracking(const std::vector<TrackingTask>& tasks_, VideoInfo* video_info_, MainWindow* window_,
             const QString& type_){
        tasks = tasks_;
        video_info = video_info_;
        tresult = new TrackingResult(window_, video_info_);
        window = window_;
        type = type_;
    }
    TrackingResult* get_result(){
        return tresult;
    }
    void run();
    void job_done(TrackingWorker* worker);
signals:
    void all_done();

private:
    MainWindow* window;
    void run_task();
    VideoInfo* video_info;
    std::vector<TrackingTask> tasks;
    QSet<TrackingWorker*> unfinshed_jobs;
    TrackingResult* tresult;
    QString type;
};


#endif

