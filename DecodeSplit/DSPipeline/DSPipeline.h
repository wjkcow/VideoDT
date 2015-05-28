#ifndef DS_PIPELINE_H
#define DS_PIPELINE_H

#include <string>
#include <vector>
class DSPipeline{
public:
    DSPipeline(const std::string& input_file_,
               const std::string& tmp_path_,
               const std::string& algorithm_,
               const std::string& method_,
               double threshold_,
               int compress_x_,
               int compress_y_);

    
    std::vector<int> run();
    int get_frame_n(){
        return total_frame_n;
    }
private:
    std::string input_file;
    std::string tmp_path;
    std::string algorithm;
    std::string method;
    double threshold;
    int compress_x;
    int compress_y;
    
    int total_frame_n;
    // other information of the file should be added
};

#endif
