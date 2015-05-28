#ifndef UTILITY_H
#define UTILITY_H

#include <string>

std::string get_path(const std::string& path_format, int seq);

class Exception{
public:
    Exception(const std::string& msg_):msg{msg_}{}
    const std::string& what(){
        return msg;
    }
private:
    std::string msg;
};

#endif
