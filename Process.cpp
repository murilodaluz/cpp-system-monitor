#include "Process.h"

int Process::getPid(){
    return Process::pid_;
}
std::string Process::getUser(){
    return Process::user_;
}
std::string Process::getCmd(){
    return Process::cmd_;
}
double Process::getCpuPerc(){
    return Process::cpuPerc_;
}
double Process::getMemory(){
    return Process::memory_;
}
std::string Process::getTime(){
    return Process::time_;
}
void Process::setPid(int pid){
    Process::pid_ = pid;
}
void Process::setUser(std::string user){
    Process::user_ = user;
}
void Process::setCmd(std::string cmd){
    Process::cmd_ = cmd;
}
void Process::setCpuPerc(double cpuPerc){
    Process::cpuPerc_ = cpuPerc;
}
void Process::setMemory(double memory){
    Process::memory_ = memory;
}
void Process::setTime(std::string time){
    Process::time_ = time;
}