#include "FrameLibrary.h"
#include "DecodeSplit/DSPipeline/Utility.h"

FrameLibrary::FrameLibrary(const QString& tmp_path_): tmp_path(tmp_path_)
{

}

void FrameLibrary::get(int n, cv::Mat& mat){
    mat = cv::imread(get_path(tmp_path.toStdString(), n));
}
