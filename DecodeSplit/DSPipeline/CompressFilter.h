#ifndef COMPRESS_FILTER_H
#define COMPRESS_FILTER_H

#include <string>
#include "tbb/pipeline.h"
#include "opencv2/opencv.hpp"

class CompressFilter : public tbb::filter{
public:
    CompressFilter(int size_x, int size_y):tbb::filter(false), resize{size_x, size_y}{}
    void* operator()(void* item) override;
private:
    static  std::vector<int> compression_params;
    cv::Size resize;
};
#endif
