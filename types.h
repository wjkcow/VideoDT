#ifndef TYPES
#define TYPES

#include <string>
#include <sstream>
struct VideoSection{
    VideoSection(const std::string& str){
        std::stringstream ss(str);
        ss >> from_frame >> to_frame;
    }
    std::string to_string(){
        std::stringstream ss;
        ss << from_frame << to_frame;
        return ss.str();
    }
    int from_frame;
    int to_frame;
};

#endif // TYPES

