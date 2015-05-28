#ifndef DECODESPLITSTAGE_H
#define DECODESPLITSTAGE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <string>
#include <QFuture>
#include <QFutureWatcher>
#include "DecodeSplit/DecodeSplitResult.h"
#include "mainwindow.h"

class DecodeSplitStage : public QObject
{
    Q_OBJECT
public:
    DecodeSplitStage(MainWindow* window_);


    void set_video_file(const QString& input_file_){input_file = input_file_;}
    void set_tmp_path(const QString& tmp_path_){tmp_path = tmp_path_;}
    void set_output_file(const QString& output_file_){output_file = output_file_;}
signals:
    void handle_result(DecodeSplitResult* result);
public slots:
    void run();

    void receive_result(){
        window->log("Algorithm done, result is received");
        handle_result(result);
    }
    void set_hist(){
        window->log("Scene spliting algorithm is setting to hist compare");
    }
    void set_pha(){
        window->log("Scene spliting algorithm is setting to PHA");
    }
    void set_method(QString str){
        method = str;
        window->log("Set method to " + str);
    }
    void set_threshold(double threshold_){
        threshold = threshold_;
        window->log((QString("The thresold of algorithm is set to ") + QString::number(threshold)));
    }
    void set_width(int x){
        compress_x = x;
        window->log(QString("The width is set to ") + QString::number(x));
    }
    void set_height(int y){
        compress_y = y;
        window->log(QString("The height is set to ") + QString::number(y));
    }
private:
    void run_thread();
    QString input_file;
    QString tmp_path;
    QString output_file;
    QString algorithm = "hist";
    QString method = "Correlation";
    double threshold = 0.8;
    int compress_x = 640;
    int compress_y = 320;
    DecodeSplitResult* result;
    int total_frame_n;
    MainWindow* window;
    QFuture<void> m_future;
    QFutureWatcher<void> m_future_watcher;
};

#endif // DECODESPLITSTAGE_H
