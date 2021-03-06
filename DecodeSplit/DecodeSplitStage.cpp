#include "DecodeSplit/DecodeSplitStage.h"
#include <QtCore>
#include <QDebug>
#include <QtConcurrent/QtConcurrentMap>
#include <QtConcurrent/QtConcurrentRun>
#include "DecodeSplit/DSPipeline/Utility.h"
#include "DecodeSplit/DecodeSplitResult.h"
#include "DSPipeline/DSPipeline.h"

DecodeSplitStage::DecodeSplitStage(MainWindow* window_): window(window_){
    video_info = new VideoInfo;
    connect(&m_future_watcher, SIGNAL(finished()),
            this, SLOT(receive_result()));
}

void DecodeSplitStage::run(){
    if(!video_info->input_file.size() || !video_info->tmp_path.size()){
        window->log("Error: please set files and paths");
        return;
    } else {
        window->log("Scene splitting started");

        m_future = QtConcurrent::run(this, &DecodeSplitStage::run_thread);
        m_future_watcher.setFuture(m_future);
        window->disable_left_panel();
    }

}


void DecodeSplitStage::run_thread(){
    DSPipeline pipeline(video_info->input_file.toStdString(),
                        (video_info->tmp_path + video_info->tmp_file_fmt).toStdString(),
                        algorithm.toStdString(),
                        method.toStdString(),
                        threshold, video_info->compress_x, video_info->compress_y);
    result = nullptr;
    try{
        video_info->total_frame_n = pipeline.get_frame_n();
        std::vector<int> key_frames = pipeline.run();
        qDebug() << pipeline.get_frame_n() << " frame_number " ;
        result = new DecodeSplitResult(video_info, key_frames);
        result->moveToThread(QApplication::instance()->thread());
    } catch(Exception& e){
             qDebug() << e.what().c_str();
             window->enable_left_panel();

    }catch(...){
        qDebug() << "run fail cause of unknown exception" ;
    }


}
