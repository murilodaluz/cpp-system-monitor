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
        Process(std::string pid, std::string user, std::string cmd, std::string cpuPerc, std::string memory, std::string time){
            pid_ = pid;
            user_ = user;
            cmd_ = cmd;
            cpuPerc_ = cpuPerc;
            memory_ = memory;
            time_ = time;
        }
        std::string getPid();
        std::string getUser();
        std::string getCmd();
        std::string getCpuPercent();
        std::string getMemory();
        std::string getTime();
        void setPid(std::string pid);
        void setUser(std::string user);
        void setCmd(std::string cmd);
        void setCpuPerc(std::string cpuPerc);
        void setMemory(std::string memory);
        void setTime(std::string time);
};

#endif