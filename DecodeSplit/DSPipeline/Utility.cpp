#include "Utility.h"

using namespace std;

const int path_buffer_length_n = 1024;

string get_path(const string& path_format, int seq){
    char buffer[path_buffer_length_n];
    sprintf(buffer, path_format.c_str(), seq);
    return string(buffer);
}