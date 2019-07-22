#include "Process.h"

int Process::getPid(){
    return Process::pid;
}
std::string Process::getUser(){
    return Process::user;
}
std::string Process::getCmd(){
    return Process::cmd;
}
double Process::getCpuPerc(){
    return Process::cpuPerc;
}
double Process::getMemory(){
    return Process::memory;
}
std::string Process::getTime(){
    return Process::time;
}
void Process::setPid(int pid){
    Process::pid = pid;
}

string Process::getProcess(){
    this->mem = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpu = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->mem.substr(0,5)
                    + "     "
                    + this->cpu.substr(0,5)
                    + "     "
                    + this->upTime.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}