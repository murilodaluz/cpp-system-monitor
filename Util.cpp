#include "Util.h"
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

// wrapper for creating streams
ifstream Util::getStream(string path){
    ifstream stream(path);
    if (!stream){
        throw runtime_error("Non - existing PID");
    }
    return stream;
}

vector<string> Util::getValuesLineFromPath(string path){
    string line;
    getline(Util::getStream(path), line);
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);
    return values;
}