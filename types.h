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
    std::string to_string(){
        std::stringstream ss;
        ss << from_frame << to_frame;
        return ss.str();
    }
    QString to_qstring(){
        return QString(to_string().c_str());
    }
    int from_frame;
    int to_frame;
};

struct VideoInfo{
    QString tmp_path;
    QString output_file;
    QString tmp_file_fmt =  QString("/%06d.png");
    int compress_x = 640;
    int compress_y = 320;
    int total_frame_n;
};
#endif // TYPES

