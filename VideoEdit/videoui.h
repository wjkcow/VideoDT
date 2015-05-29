#ifndef VIDEOUI_H
#define VIDEOUI_H

#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QPointF>
#include <QPair>
#include <QString>
#include <vector>
#include <opencv2/opencv.hpp>
class Frame;
class VideoUI : public QWidget
{
    Q_OBJECT
    QString name;
    cv::Mat* m_frame;
    QPointF rect_start_point;
    QRect   draw_rect;
    bool   drawable = false;
    bool   draw_started = false;
    std::vector<QPair<QColor, QRect>>  rects;
    VideoUI(VideoUI&&) = delete;
    VideoUI(const VideoUI&) = delete;
    VideoUI & operator=(VideoUI&&) = delete;
    VideoUI & operator=(const VideoUI&) = delete;

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public:
    VideoUI(QWidget* place, QWidget * parent, bool drawable_ = false);
    VideoUI(QWidget* parent = 0);
    void show_frame(Frame* frame, std::vector<QPair<QColor, QRect>> rects);

public slots:
    void show_frame(Frame* frame);
    void start_draw_rect(const QColor);
signals:
    void rect_drawed(const QRect& rect);
    void log(const QString& str);
};

#endif // VIDEOUI_H
