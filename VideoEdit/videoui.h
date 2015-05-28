#ifndef VIDEOUI_H
#define VIDEOUI_H

#include <QImage>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <QPointF>

#include <QString>
#include <opencv2/opencv.hpp>
class VideoUI : public QWidget
{
    Q_OBJECT
    QString name;
    cv::Mat* m_frame;
    QPointF rect_start_point;
    QRect   draw_rect;
    bool   draw_started = false;
    VideoUI(VideoUI&&) = delete;
    VideoUI(const VideoUI&) = delete;
    VideoUI & operator=(VideoUI&&) = delete;
    VideoUI & operator=(const VideoUI&) = delete;

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
public:
    VideoUI(QWidget* place, QWidget * parent);
    VideoUI(QWidget* parent = 0);
public slots:
    void show_frame(cv::Mat* frame);
    void start_draw_rect(const QColor);
signals:
    void rect_drawed(const QRect& rect);
    void log(const QString& str);
};

#endif // VIDEOUI_H
