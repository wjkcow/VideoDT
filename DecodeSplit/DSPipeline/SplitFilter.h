#ifndef SPLIT_FILTER_H
#define SPLIT_FILTER_H
#include <vector>
#include <string>
#include <memory>
#include "tbb/pipeline.h"

class Frame;

class SplitFilter : public tbb::filter{
public:
    SplitFilter(int n_frame):filter(false), sz{n_frame},
                            frame_eva{new double[n_frame]}{}
    virtual ~SplitFilter(){delete[] frame_eva;}
    
    void* operator()(void* item) override;
    
    std::vector<int> get_key_frames();
    
    static std::shared_ptr<SplitFilter> factory(const std::string& type,
                                                const std::string& method,
                                                int    n_frame,
                                                double threshold = -1.);
protected:
    virtual double evaluate_frame_pair(Frame* frame) = 0;
    virtual bool scene_threshold(double) = 0;
private:
    int sz;
    double* frame_eva;
};

#endif
