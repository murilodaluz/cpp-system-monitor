#ifndef PROCESS 
#define PROCESS
#include<string>
#include"ProcessParser.h"

class Process {
    private:
        std::string pid;
        std::string user;
        std::string cmd;
        std::string cpuPerc;
        std::string memory;
        std::string upTime;
    public: 
        Process(std::string pid){
            this->pid = pid;
            this->user = ProcessParser::getProcUser(pid);
            this->memory = ProcessParser::getVmSize(pid);
            this->cmd = ProcessParser::getCmd(pid);
            this->upTime = ProcessParser::getProcUpTime(pid);
            this->cpuPerc  = ProcessParser::getCpuPercent(pid);
        }
        void setPid(std::string pid);
        std::string getPid() const;
        std::string getUser() const;
        std::string getCmd() const;
        std::string getCpuPercent() const;
        std::string getMemory() const;
        std::string getUpTime() const;
        std::string getProcess();
};

#endif