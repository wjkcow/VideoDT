#ifndef PHA_FILTER_H
#define PHA_FILTER_H
#include "SplitFilter.h"
#include "FrameTypes.h"

int diff(unsigned, unsigned);

// PHAFilter is a parallel fiter for tbb pipeline
// it will calculate the pha of each frame and put it into the right place of
// the vector
class PHAFilter : public SplitFilter{
public:
    PHAFilter(int n_frame, double threshold_):SplitFilter{n_frame}, threshold{threshold_}{};

protected:
    double evaluate_frame_pair(Frame* frame) override;
    bool  scene_threshold(double eva) override;

private:
    double threshold = 10;
    
    unsigned calc_pha(const cv::Mat& src);
    int diff(unsigned left, unsigned right);};

#endif