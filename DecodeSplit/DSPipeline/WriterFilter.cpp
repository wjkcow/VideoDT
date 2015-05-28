#include "WriterFilter.h"

#include "FrameTypes.h"
#include "Utility.h"
using namespace std;
using namespace cv;

std::vector<int> WriterFilter::compression_params = std::vector<int> {CV_IMWRITE_PNG_COMPRESSION, 9};

void* WriterFilter::operator()(void* item){
    Frame* frame = (Frame*) item;
    imwrite(get_path(path, frame->seq), *frame);
    return nullptr;
}


