#include "DecodeSplit/DecodeSplitStage.h"
#include <QtCore>
#include <QDebug>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentRun>
#include "DecodeSplit/DSPipeline/Utility.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "DSPipeline/DSPipeline.h"

DecodeSplitStage::DecodeSplitStage(MainWindow* window_): window(window_){
    connect(&m_future_watcher, SIGNAL(finished()),
            this, SLOT(receive_result()));
}

void DecodeSplitStage::run(){
    if(!input_file.size() || !tmp_path.size() || !output_file.size()){
        window->log("Error: please set files and paths");
        return;
    } else {

        m_future = QtConcurrent::run(this, &DecodeSplitStage::run_thread);
        m_future_watcher.setFuture(m_future);
    }

}


void DecodeSplitStage::run_thread(){
    DSPipeline pipeline(input_file.toStdString(),
                        tmp_path.toStdString(),
                        algorithm.toStdString(),
                        method.toStdString(),
                        threshold, compress_x, compress_y);
    qDebug() << "algorithm start" ;
    try{    std::vector<int> resul = pipeline.run();
        qDebug() << "done" ;
        for(int i =0; i <resul.size(); i++)
            qDebug()<< resul[i] << " ";
        } catch(Exception& e){
             qDebug() << e.what().c_str();
        }catch(...){
        qDebug() << "run faile" ;
    }


}
