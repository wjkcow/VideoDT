#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H
#include <QObject>
#include <QImage>
#include <QString>
#include <QBasicTimer>
#include <QSize>
#include <opencv2/opencv.hpp>
#include <string>

//Q_DECLARE_METATYPE(cv::Mat);

class VideoCapture : public QObject
{
    Q_OBJECT
    int frame_n;
    int total_frame_n;
    QBasicTimer m_timer;
    cv::VideoCapture* m_videoCapture;
public:
    VideoCapture(int w_, int h_,QObject* parent = 0) : QObject(parent){
        w = w_;
        h = h_;
    }

public slots:
    void load(QString video_path);
    void play();
    void pause();
    void jump_to_frame(int frame_n_);
    void next_frame();
    void pre_frame();
    void resize(QSize sz){
        w = sz.width();
        h = sz.height();
    }

signals:
    void frame_ready(cv::Mat *frame);
    void fail_open_file();

private:
    void capture_fire_frame();
    void timerEvent(QTimerEvent* ev);
    int w;
    int h;

};

#endif // VIDEOCAPTURE_H
