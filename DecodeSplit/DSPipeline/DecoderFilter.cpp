#include "DecoderFilter.h"
#include <cstdio>
#include <iostream>
#include "Utility.h"

using namespace std;
using namespace cv;


void* DecoderFilter::operator()(void* item){
    Frame* mybuffer = buffer + next_buffer;
    next_buffer = (next_buffer + 1) % n_buffer;
    mybuffer->seq = seq++;
    mybuffer->prev_frame = last_frame;
    last_frame = mybuffer;
    if(read_frame(*mybuffer)){
        return mybuffer;
    } else {
        return nullptr;
    }
}

VideoDecoderFilter::VideoDecoderFilter(const string& videofile, int start_seq):
DecoderFilter(start_seq) {
    cap.open(videofile);
    if (!cap.isOpened()) {
        cerr << "File cannot open" << endl;
        throw exception();
    }
}

VideoDecoderFilter::~VideoDecoderFilter(){
    cap.release();
}

bool VideoDecoderFilter::read_frame(Frame& frame){
    // if the frame is not sequential, jump to the frame
    if (frame.seq != lastseq++) {
        lastseq = frame.seq;
        cap.set(CV_CAP_PROP_POS_FRAMES, frame.seq);
    }
    
    if (cap.grab()) {
        cap.retrieve(frame);
        return true;
    } else {
        return false;
    }
}

ImageDecoderFilter::ImageDecoderFilter(const std::string& imagefile,
                                       int start_seq): DecoderFilter(start_seq)
{}

bool ImageDecoderFilter::read_frame(Frame& frame){
    frame.Mat::operator=(imread(get_path(path_format_str, frame.seq)));
    return frame.Mat::data != NULL;
}