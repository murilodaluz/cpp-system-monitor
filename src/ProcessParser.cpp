#include "ProcessParser.h"
#include "Util.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

bool ProcessParser::isPidExisting(std::string pid){
    std::vector<std::string> pids = ProcessParser::getPidList();
    for(auto i : pids){
        if (i == pid)
        return true;
    }
    return false;
}

std::string ProcessParser::getVmSize(std::string pid){
    std::string line;
    // Valor de referencia
    std::string name = "VmData";
    float result;
    std::ifstream stream;
    Util::getStream(Path::basePath() + pid + Path::statusPath(), stream);    
    while (getline(stream, line)){
        // Buscando linha por linha
        if (line.compare(0, name.size(), name) == 0){
            // Dividindo a linha em partes
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            //Convertendo kB -> GB
            result = (stof(values[1]) / float(1024 * 1024));
            break;
        }
    }
    return to_string(result);
}

string ProcessParser::getCpuPercent(std::string pid){
    float result;
    std::vector<std::string> values = Util::getValuesLineFromPath(Path::basePath() + pid + "/" + Path::statPath());
    float utime = stof(ProcessParser::getProcUpTime(pid));
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);
    return to_string(result);
}

string ProcessParser::getProcUpTime(std::string pid){
    //Traz o vetor contendo os valores da linha que foi lida.
    std::vector<std::string> values = Util::getValuesLineFromPath(Path::basePath() + pid + "/" + Path::statPath());
    // Using sysconf to get clock ticks of the host machine
    return to_string(float(stof(values[13]) / sysconf(_SC_CLK_TCK)));
}

long int ProcessParser::getSysUpTime(){
    std::vector<std::string> values = Util::getValuesLineFromPath(Path::basePath() + Path::upTimePath());
    return stoi(values[0]);
}

std::string ProcessParser::getProcUser(std::string pid){
    std::string line;
    std::string name = "Uid:";
    std::string result = "";
    
    std::ifstream stream;  //delclare a stream    
    //Fill stream with a valid stream
    Util::getStream(Path::basePath() + pid + Path::statusPath(), stream);
    // Pegar UID do usuario
    while (std::getline(stream, line)){
        if (line.compare(0, name.size(), name) == 0){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result = values[1];
            break;
        }
    }
    Util::getStream("/etc/passwd", stream);
    name = ("x:" + result);
    // Buscando o nome do usuario selecionado
    while (std::getline(stream, line)){
        if (line.find(name) != std::string::npos){
            result = line.substr(0, line.find(":"));
            return result;
        }
    }
    return "";
}

std::vector<std::string> ProcessParser::getPidList(){
    DIR *dir;
    std::vector<std::string> container;
    if (!(dir = opendir("/proc")))
        throw std::runtime_error(std::strerror(errno));
    // Percorrer todos o conteudo da pasta '/proc' e veirificar se é um diretorio
    // e se todos os caracteres são só numeros.
    while (dirent *dirp = readdir(dir)){
        // Verificando se não é um diretório.
        if (dirp->d_type != DT_DIR)
            // se não for, segue para o proximo
            continue;
        // Verificando se todos os caracteres são numeros
        if (all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), [](char c) { return std::isdigit(c); })){
            container.push_back(dirp->d_name);
        }
    }
    // Fechar o que se abre :)
    if (closedir(dir))
        throw std::runtime_error(std::strerror(errno));
    return container;
}

std::string ProcessParser::getCmd(std::string pid){
    std::string line;
    ifstream stream;
    Util::getStream(Path::basePath() + pid + Path::cmdPath(), stream);
    std::getline(stream, line);
    return line;
}

int ProcessParser::getNumberOfCores(){
    // Get the number of host cpu cores
    std::string line;
    std::string name = "cpu cores";
    ifstream stream;
    Util::getStream((Path::basePath() + "cpuinfo"), stream);
    while (std::getline(stream, line)){
        if (line.compare(0, name.size(), name) == 0){
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            return stoi(values[3]);
        }
    }
    return 0;
}

std::vector<std::string> ProcessParser::getSysCpuPercent(std::string coreNumber){
    // It is possible to use this method for selection of data for overall cpu or every core.
    // when nothing is passed "cpu" line is read
    // when, for example "0" is passed  -> "cpu0" -> data for first core is read
    std::string line;
    std::string name = "cpu" + coreNumber;
    ifstream stream;
    Util::getStream((Path::basePath() + Path::statPath()), stream);
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            // set of cpu data active and idle times;
            return values;
        }
    }
    return (std::vector<std::string>());
}

float getSysActiveCpuTime(std::vector<std::string> values){
    return (stof(values[S_USER]) +
            stof(values[S_NICE]) +
            stof(values[S_SYSTEM]) +
            stof(values[S_IRQ]) +
            stof(values[S_SOFTIRQ]) +
            stof(values[S_STEAL]) +
            stof(values[S_GUEST]) +
            stof(values[S_GUEST_NICE]));
}

float getSysIdleCpuTime(std::vector<std::string>values){
    return (stof(values[S_IDLE]) + stof(values[S_IOWAIT]));
}

std::string ProcessParser::printCpuStats(std::vector<std::string> values1, std::vector<std::string> values2){
/*
Because CPU stats can be calculated only if you take measures in two different time,
this function has two parameters: two vectors of relevant values.
We use a formula to calculate overall activity of processor.
*/
    float activeTime = getSysActiveCpuTime(values2) - getSysActiveCpuTime(values1);
    float idleTime = getSysIdleCpuTime(values2) - getSysIdleCpuTime(values1);
    float totalTime = activeTime + idleTime;
    float result = 100.0*(activeTime / totalTime);
    return to_string(result);
}

float ProcessParser::getSysRamPercent(){
    std::string line;
    std::string name1 = "MemAvailable:";
    std::string name2 = "MemFree:";
    std::string name3 = "Buffers:";

    std::string value;
    ifstream stream;
    Util::getStream((Path::basePath() + Path::memInfoPath()), stream);
    float total_mem = 0;
    float free_mem = 0;
    float buffers = 0;
    while (std::getline(stream, line)) {
        if (total_mem != 0 && free_mem != 0)
            break;
        if (line.compare(0, name1.size(), name1) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            total_mem = stof(values[1]);
        }
        if (line.compare(0, name2.size(), name2) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            free_mem = stof(values[1]);
        }
        if (line.compare(0, name3.size(), name3) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            buffers = stof(values[1]);
        }
    }
    //calculating usage:
    return float(100.0*(1-(free_mem/(total_mem-buffers))));
}

std::string ProcessParser::getSysKernelVersion(){
    std::string line;
    std::string name = "Linux version ";
    ifstream stream;
    Util::getStream((Path::basePath() + Path::versionPath()), stream);
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            return values[2];
        }
    }
    return "";
}

std::string ProcessParser::getOSName(){
    std::string line;
    std::string name = "PRETTY_NAME=";

    ifstream stream;
    Util::getStream(("/etc/os-release"), stream);

    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
              std::size_t found = line.find("=");
              found++;
              std::string result = line.substr(found);
              result.erase(std::remove(result.begin(), result.end(), '"'), result.end());
              return result;
        }
    }
    return "";

}

int ProcessParser::getTotalThreads(){
    std::string line;
    int result = 0;
    std::string name = "Threads:";
    std::vector<std::string>_list = ProcessParser::getPidList();
    for (std::size_t i=0 ; i < _list.size();i++) {
        std::string pid = _list[i];
        //getting every process and reading their number of their threads
        ifstream stream;
        Util::getStream((Path::basePath() + pid + Path::statusPath()), stream);
        while (std::getline(stream, line)) {
            if (line.compare(0, name.size(), name) == 0) {
                std::istringstream buf(line);
                std::istream_iterator<std::string> beg(buf), end;
                std::vector<std::string> values(beg, end);
                result += stoi(values[1]);
                break;
            }
        }
    }
    return result;
}

int ProcessParser::getTotalNumberOfProcesses(){
    std::string line;
    int result = 0;
    std::string name = "processes";
    ifstream stream;
    Util::getStream((Path::basePath() + Path::statPath()), stream);
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result += stoi(values[1]);
            break;
        }
    }
    return result;
}

int ProcessParser::getNumberOfRunningProcesses(){
    std::string line;
    int result = 0;
    std::string name = "procs_running";
    ifstream stream;
    Util::getStream((Path::basePath() + Path::statPath()), stream);
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(), name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<std::string> beg(buf), end;
            std::vector<std::string> values(beg, end);
            result += stoi(values[1]);
            break;
        }
    }
    return result;
}