#include "videoui.h"

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QDebug>
#include <QPixmap>
#include <DecodeSplit/DSPipeline/FrameTypes.h>

VideoUI::VideoUI(QWidget* place, QWidget * parent, bool drawable_):VideoUI(place->parentWidget()){
    move(place->pos());
    setFixedWidth(place->width());
    setFixedHeight(place->height());
    drawable = drawable_;
}

VideoUI::VideoUI(QWidget * parent) : QWidget(parent){
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAutoFillBackground(true);
    m_frame = nullptr;
}

void VideoUI::paintEvent(QPaintEvent *){
    if(m_frame){
        QImage img(m_frame->data, m_frame->cols, m_frame->rows, m_frame->step,
                               QImage::Format_RGB888);
//        qDebug() << "paint_Event";
        QPainter p(this);

        p.eraseRect(0,0,img.width(), img.height());
        p.setPen(Qt::blue);
        p.drawImage(0,0,img);

        if(drawable){
            p.drawRect(draw_rect);
        }
        for(int i = 0; i < rects.size(); i++){
            p.setPen(rects[i].first);
            p.drawRect(rects[i].second);
        }
    }

}

void VideoUI::mousePressEvent(QMouseEvent* event){
    qDebug() << name;

     update();
    qDebug() << event->localPos();
    draw_started = true;
    rect_start_point = event->localPos();
}

void VideoUI::mouseMoveEvent(QMouseEvent *event){
    if(draw_started){
        draw_rect.setCoords(rect_start_point.x(), rect_start_point.y(),
                            event->localPos().x(),
                            event->localPos().y());
        update();
    }
    qDebug() << "move" << event->localPos();

}

void VideoUI::mouseReleaseEvent(QMouseEvent* event){
    if(draw_started){
        draw_rect.setCoords(rect_start_point.x(), rect_start_point.y(),
                             event->localPos().x(),
                             event->localPos().y());
        draw_started = false;
        update();

    }
}

void VideoUI::show_frame(Frame* frame){
 //   QImage img(frame->data, frame->cols, frame->rows, frame->step,
 //                                      QImage::Format_RGB888);
    rects.clear();
    draw_rect.setCoords(0,0,0,0);
    delete m_frame;
    m_frame = frame;
    qDebug() << "show_frame";
  //  repaint();
    update();
}

void VideoUI::show_frame(Frame* frame, std::vector<QPair<QColor, QRect>> rects_){
 //   QImage img(frame->data, frame->cols, frame->rows, frame->step,
 //                                      QImage::Format_RGB888);
    rects = rects_;
    draw_rect.setCoords(0,0,0,0);
    delete m_frame;
    m_frame = frame;
    qDebug() << "show_frame";
  //  repaint();
    update();
}

void VideoUI::start_draw_rect(const QColor){


}
