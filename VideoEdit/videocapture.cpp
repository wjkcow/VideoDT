#include "videocapture.h"
#include <QTimerEvent>
#include <string>
#include <QDebug>
#include <DecodeSplit/DSPipeline/FrameTypes.h>
void VideoCapture::load(QString video_path){
    m_videoCapture = new cv::VideoCapture;

    m_videoCapture->open(video_path.toStdString());
    if (!m_videoCapture->isOpened()) {
        emit fail_open_file();
    } else {
        total_frame_n = m_videoCapture->get(CV_CAP_PROP_FRAME_COUNT);
        frame_n = 0;
        next_frame();
    }
}

void VideoCapture::play(){
    qDebug() << "play called";
    m_timer.start(30, this);
}

void VideoCapture::pause(){
    qDebug() << "pause called";

    m_timer.stop();
}

void VideoCapture::jump_to_frame(int frame_n_){
    qDebug() << "jump to frame called, jump to" << frame_n_;

    m_timer.stop();
    int next_frame_n = frame_n_ + 1;
    if(next_frame_n > 0 && next_frame_n < total_frame_n){
        frame_n = next_frame_n;
        m_videoCapture->set(CV_CAP_PROP_POS_FRAMES, frame_n);
        capture_fire_frame();
    }
}

void VideoCapture::next_frame(){
    qDebug() << "next frame called";
    frame_n ++;
    if(frame_n > 0 && frame_n < total_frame_n){
        capture_fire_frame();
    } else if(frame_n < 0){ frame_n = 0;}
      else if(frame_n >= total_frame_n) {frame_n = total_frame_n - 1;}
}

void VideoCapture::pre_frame(){
    qDebug() << "prev frame called";
    m_timer.stop();
    frame_n -= 1;
    if(frame_n > 0 && frame_n < total_frame_n){
        m_videoCapture->set(CV_CAP_PROP_POS_FRAMES, frame_n);
        capture_fire_frame();
    } else if(frame_n <= 0){ frame_n = 1;}
      else if(frame_n >= total_frame_n) {frame_n = total_frame_n - 1;}
}

void VideoCapture::capture_fire_frame(){
    Frame* frame = new Frame;
   // cv::Mat* frame = new cv::Mat;
    qDebug() << "capture" ;

    if(m_videoCapture->grab()){
        m_videoCapture->retrieve(*frame);
        cv::resize(*frame, *frame, cv::Size(w,h));
        cv::cvtColor(*frame, *frame, CV_BGR2RGB);
       // QImage img(frame->data, frame->cols, frame->rows, frame->step,
     //                              QImage::Format_RGB888);
        //Q_ASSERT(image.constBits() == frame.data);
        frame->seq = frame_n - 1;
        qDebug() << "capture done" << frame->seq;

        emit new_frame_fired(frame_n - 1);
        emit frame_ready(frame);
    } else {
        qDebug() << "fail to read" ;
        m_timer.stop();
    }
}

void VideoCapture::timerEvent(QTimerEvent *ev){
    qDebug() << "timer out" ;
    if(ev->timerId() != m_timer.timerId()){
        return;
    }
    next_frame();
}

