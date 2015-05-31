#include "Tracking/Tracking.h"
#include "Dectector/TrackingTask.h"
#include <QFuture>
#include <QHash>
#include <QRect>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentRun>
#include <QFutureWatcher>
#include <QDebug>
#include "FrameLibrary.h"
#include "Tracking/CppMT/CMT.h"
#include "opencv2/opencv.hpp"
#include "Tracking/TrackingResult.h"
#include "Tracking/TrackingAlgorithm.h"
#include "types.h"



TrackingWorker::TrackingWorker(TrackingTask task,const QString& path_,Tracking* tracking_, TrackingResult* result_, const QString& type_) : m_task(task),
    path(path_), tracking(tracking_), result(result_), type(type_){
        connect(&m_future_watcher, SIGNAL(finished()), this, SLOT(task_done()));
    }

void TrackingWorker::run(){
        qDebug() << "Tracker"  << m_task.tracker->name << " started with " << m_task.rect ;

        m_future = QtConcurrent::run(this, &TrackingWorker::parallel_task_run);
        m_future_watcher.setFuture(m_future);
}

void TrackingWorker::task_done(){
        result->add_result(&m_task, results);
        tracking->job_done(this);

}
void TrackingWorker::parallel_task_run(){
        TrackingAlgorithm* ta = TrackingAlgorithm::factory(type);
    //    qDebug() << path;
        FrameLibrary flib(path);
        m_task.rect;
        results[m_task.from_frame] = m_task.rect;
        // initialize
        Mat im0;
        flib.get(m_task.from_frame, im0);
        ta->initialize(im0, m_task.rect);
     //   cv::imwrite("/Users/wjkcow/Desktop/tmp/i.png",im_gray(to_cv_rect(m_task.rect)));

        // run
        //int j = 0;
        for(int i = m_task.from_frame; i < m_task.to_frame; i++){
              Mat im;
              flib.get(i, im);
              results[i] = ta->processFrame(im);
         //     cmt.processFrame(im_gray);
            //  cv::Mat submat = im_gray(cmt.bb_rot.boundingRect());
            //  cv::imwrite("/Users/wjkcow/Desktop/tmp/" + QString::number(j++).toStdString() + ".png",im);
            //  results[i] = to_q_rect(cmt.bb_rot.boundingRect());

        }

}

void Tracking::run(){
    for(int i = 0; i < tasks.size(); i++){
        TrackingWorker* new_worker = new TrackingWorker(tasks[i],
                                                        video_info->tmp_path +
                                                        video_info->tmp_file_fmt,
                                                        this,
                                                        tresult, type);
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
