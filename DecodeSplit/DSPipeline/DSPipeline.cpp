#include "DSPipeline.h"

#include "DecoderFilter.h"
#include "WriterFilter.h"
#include "SplitFilter.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/pipeline.h"
#include "opencv2/opencv.hpp"
using namespace std;

DSPipeline::DSPipeline(const std::string& input_file_,
                       const std::string& tmp_path_,
                       const std::string& algorithm_,
                       const std::string& method_,
                       double threshold_,
                       int compress_x_,
                       int compress_y_) : input_file{input_file_},
tmp_path{tmp_path_},algorithm{algorithm_}, method{method_},
threshold{threshold_}, compress_x{compress_x_}, compress_y{compress_y_} {
    cv::VideoCapture vcap(input_file);
    total_frame_n = static_cast<int>(vcap.get(CV_CAP_PROP_FRAME_COUNT));
    vcap.release();
    
}


std::vector<int> DSPipeline::run(){
    tbb::task_scheduler_init init;
    tbb::pipeline pipeline;
    VideoDecoderFilter decoder(input_file);
    pipeline.add_filter(decoder);
    shared_ptr<SplitFilter> splitter = SplitFilter::factory(algorithm, method, total_frame_n);
    pipeline.add_filter(*splitter);

    WriterFilter writer("/Users/wjkcow/Desktop/ims/im%05d.png",8,8);
    pipeline.add_filter(writer);
    pipeline.run(VideoDecoderFilter::get_pipeline_n());
    pipeline.clear();
    return splitter->get_key_frames();
}
