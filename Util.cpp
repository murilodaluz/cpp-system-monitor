#include "Util.h"
#include <string>
#include <vector>
using namespace std;

string Util::convertToTime(long int input_seconds){
    long minutes = input_seconds / 60;
    long hours = minutes / 60;
    long seconds = int(input_seconds % 60);
    minutes = int(minutes % 60);
    string result = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    return result;
}

// Contruindo a string para retornar a porcentagem
// 50 barras representando a extensão 0 - 100 %
// Ou seja: cada 2% é uma barra(|)
string Util::getProgressBar(string percent){
    string result = "0% ";
    int _size = 50;
    int boundaries = (stof(percent) / 100) * _size;

    for (int i = 0; i < _size; ++i){
        if (i < boundaries){
            result += "|";
        }
        else{
            result += " ";
        }
    }

    result += " " + percent.substr(0, 5) + " /100%";
    return result;
}

// // wrapper for creating streams
// ifstream Util::getStream(string path){
//     ifstream stream(path);
//     if (!stream){
//         throw runtime_error("Non - existing PID");
//     }
//     return stream;
// }

std::string Util::getStream(std::string path, std::ifstream& stream){   //returns a Stream object of type ifstream
    try
    {
        stream.open (path, std::ifstream::in);  //attempt to open stream
        if (!stream && !stream.is_open()){  //if stream is false (can't open)
            stream.close();  //close the stream  
            throw std::runtime_error("Non - existing PID");   //throw a runtime error that states "Non - existing PID"
        }
        return path;        
    }     
    catch (...){        
        std::cout << path << "\n";        
        }
    
}

vector<string> Util::getValuesLineFromPath(string path){
    std::string line;
    std::ifstream stream;     
    Util::getStream(Path::basePath() + pid + Path::statPath(), stream);
    std::getline(stream, line);
    string str = line;
    std::istringstream buf(str);  
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values (beg, end);
    return values;
}