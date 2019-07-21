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

string Process::getProcess(){
    this->mem = ProcessParser::getVmSize(this->pid);
    this->up_time = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->mem.substr(0,5)
                    + "     "
                    + this->cpu.substr(0,5)
                    + "     "
                    + this->up_time.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}