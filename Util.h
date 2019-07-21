#ifndef UTIL
#define UTIL

#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>

// Classic helper functions
class Util{
public:
    static std::string convertToTime(long int input_seconds);
    static std::string getProgressBar(std::string percent);
    static std::ifstream getStream(std::string path);
    static std::vector<string> Util::getValuesLineFromPath(string path);
};
#endif