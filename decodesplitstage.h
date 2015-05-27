#ifndef DECODESPLITSTAGE_H
#define DECODESPLITSTAGE_H

#include <QObject>
#include <QString>
#include "mainwindow.h"
#include "decodesplitresult.h"

class DecodeSplitStage : QObject
{
    Q_OBJECT
public:
    DecodeSplitStage(MainWindow* window_);
    bool run();
    DecodeSplitResult*  get_result(){
        return result;
    }
public slots:
    void receive_result(DecodeSplitResult* result_){
        result = result_;
    };
private:
    QString input_file;
    QString tmp_path;
    QString output_file;
    QString algorithm;
    QString method;
    double threshold;
    int compress_x;
    int compress_y;
    MainWindow* window;
    DecodeSplitResult* result;
};

#endif // DECODESPLITSTAGE_H
