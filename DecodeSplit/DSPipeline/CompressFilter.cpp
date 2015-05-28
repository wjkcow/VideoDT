#include "CompressFilter.h"

#include "FrameTypes.h"
#include "Utility.h"
using namespace std;
using namespace cv;

std::vector<int> CompressFilter::compression_params = std::vector<int> {CV_IMWRITE_PNG_COMPRESSION, 9};

void* CompressFilter::operator()(void* item){
    Frame* frame = (Frame*) item;
    cv::resize(*frame, *frame, resize);
    return frame;
}


