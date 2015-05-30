#include "Tracking/Tracking.h"
#include "Dectector/TrackingTask.h"
#include <QFuture>
#include <QHash>
#include <QRect>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include "FrameLibrary.h"
#include "Tracking/CppMT/CMT.h"
#include "opencv2/opencv.hpp"
#include "Tracking/TrackingResult.h"
#include "types.h"



TrackingWorker::TrackingWorker(TrackingTask task,const QString& path_,Tracking* tracking_, TrackingResult* result_) : m_task(task),
    path(path_), tracking(tracking_), result(result_){
        connect(&m_future_watcher, SIGNAL(finished()), this, SLOT(task_done()));
    }

void TrackingWorker::run(){
        m_future = QtConcurrent::run(this, &TrackingWorker::parallel_task_run);
        m_future_watcher.setFuture(m_future);
}

void TrackingWorker::task_done(){
        result->add_result(&m_task, results);
        tracking->job_done(this);

}
void TrackingWorker::parallel_task_run(){
        cmt::CMT cmt;

        FrameLibrary flib(path);
        m_task.rect;
        results[m_task.from_frame] = m_task.rect;
        // initialize
        Mat im;
        Mat im_gray;
        flib.get(m_task.from_frame, im);
        cvtColor(im, im_gray, CV_BGR2GRAY);
        cmt.initialize(im_gray, to_cv_rect(m_task.rect));
        // run
        for(int i = m_task.from_frame + 1; i < m_task.to_frame; i++){
              flib.get(i, im);
              cvtColor(im, im_gray, CV_BGR2GRAY);
              cmt.processFrame(im_gray);
              results[i] = to_q_rect(cmt.bb_rot.boundingRect());
        }

}

void Tracking::run(){
    for(int i = 0; i < tasks.size(); i++){
        TrackingWorker* new_worker = new TrackingWorker(tasks[i],
                                                        video_info->tmp_path +
                                                        video_info->tmp_file_fmt,
                                                        this,
                                                        tresult);
        unfinshed_jobs.insert(new_worker);
        new_worker->run();
    }
    if(!tasks.size()){
        emit all_done();
    }
}

void Tracking::job_done(TrackingWorker *worker){
    unfinshed_jobs.erase(unfinshed_jobs.find(worker));
    delete worker;
    if(!unfinshed_jobs.size()){
        emit all_done();
    }
}
