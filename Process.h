#ifndef PROCESS 
#define PROCESS
#include<string>;

class Process {
    private:
        std::string pid_;
        std::string user_;
        std::string cmd_;
        std::string cpuPerc_;
        std::string memory_;
        std::string time_;
    public: 
        Process(string pid)
        {
            this->pid = pid;
            this->user = ProcessParser::getProcUser(pid);
            this->mem = ProcessParser::getVmSize(pid);
            this->cmd = ProcessParser::getCmd(pid);
            this->up_time = ProcessParser::getProcUpTime(pid);
            this->cpu  = ProcessParser::getCpuPercent(pid);
        }
        std::string getPid();
        std::string getUser();
        std::string getCmd();
        std::string getCpuPercent();
        std::string getMemory();
        std::string getTime();
        std::string getPRocess();
        void setPid(std::string pid);
        void setTime(std::string time);
};

#endif