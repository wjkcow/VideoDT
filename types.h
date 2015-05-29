#ifndef TYPES
#define TYPES
#include <QString>
#include <string>
#include <sstream>
struct VideoSection{
    VideoSection(){}
    VideoSection(const std::string& str){
        std::stringstream ss(str);
        ss >> from_frame >> to_frame;
    }
    VideoSection(int from_frame_, int to_frame_):
        from_frame(from_frame_), to_frame(to_frame_){
    }
    VideoSection(const VideoSection& other):VideoSection(other.from_frame, other.to_frame){

    }
    std::string to_string(){
        std::stringstream ss;
        ss << from_frame << "  " <<to_frame;
        return ss.str();
    }
    QString to_qstring(){
        return QString(to_string().c_str());
    }
    int from_frame = 0;
    int to_frame = 0;
};

struct VideoInfo{
    QString input_file;
    QString tmp_path;
    QString tmp_file_fmt =  QString("/%06d.png");
    int compress_x = 640;
    int compress_y = 320;
    int total_frame_n;
};
#endif // TYPES

