#ifndef WRITER_FILTER_H
#define WRITER_FILTER_H

#include <string>
#include "tbb/pipeline.h"
#include "opencv2/opencv.hpp"

class WriterFilter : public tbb::filter{
public:
    WriterFilter(const std::string& path_):tbb::filter(false),path{path_}{}
    void* operator()(void* item) override;
private:
    static  std::vector<int> compression_params;
    cv::Size resize;
    std::string path;

};
#endif
