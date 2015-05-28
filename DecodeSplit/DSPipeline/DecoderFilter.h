#ifndef DECODER_FILTER_H
#define DECODER_FILTER_H

#include <string>
#include "tbb/pipeline.h"
#include "opencv2/opencv.hpp"
#include "FrameTypes.h"

class DecoderFilter : public tbb::filter{
public:
    DecoderFilter(int start_seq): tbb::filter(true){}
    virtual ~DecoderFilter(){}
    void* operator()(void* item) override;
    static size_t get_pipeline_n(){
        return n_buffer - 1;
    }
protected:
    virtual bool read_frame(Frame& frame) = 0;
private:
    static const size_t n_buffer = 16;
    int seq = 0;
    int next_buffer = 0;
    Frame buffer[n_buffer];
    Frame* last_frame = nullptr;
};

class VideoDecoderFilter : public DecoderFilter{
public:
    VideoDecoderFilter(const std::string& videofile, int start_seq = 0);
    ~VideoDecoderFilter();
protected:
    bool read_frame(Frame& frame) override;
private:
    cv::VideoCapture cap;
    int lastseq = 0;
};

class ImageDecoderFilter : public DecoderFilter{
public:
    ImageDecoderFilter(const std::string& imagefile, int start_seq);
protected:
    bool read_frame(Frame& frame) override;
private:
    std::string path_format_str;
};


#endif
