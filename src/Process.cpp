#include "Process.h"
#include "ProcessParser.h"

void Process::setPid(std::string pid){
    Process::pid = pid;
}

std::string Process::getPid() const{
    return Process::pid;
}

std::string Process::getUser() const{
    return Process::user;
}

std::string Process::getCmd() const{
    return Process::cmd;
}

std::string Process::getCpuPercent() const{
    return Process::cpuPerc;
}

std::string Process::getMemory() const{
    return Process::memory;
}

std::string Process::getUpTime() const{
    return Process::upTime;
}

std::string Process::getProcess(){
    if(!ProcessParser::isPidExisting(this->pid)){
        return "";
    }
    this->memory = ProcessParser::getVmSize(this->pid);
    this->upTime = ProcessParser::getProcUpTime(this->pid);
    this->cpuPerc = ProcessParser::getCpuPercent(this->pid);

    return (this->pid + "   "
                    + this->user
                    + "   "
                    + this->memory.substr(0,5)
                    + "     "
                    + this->cpuPerc.substr(0,5)
                    + "     "
                    + this->upTime.substr(0,5)
                    + "    "
                    + this->cmd.substr(0,30)
                    + "...");
}