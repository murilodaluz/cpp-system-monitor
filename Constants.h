#ifndef CONSTANTS_PATH
#define CONSTANTS_PATH

#include <string>

using namespace std;

enum CPUStates {
    S_USER = 1,  //setting this equal to 1 means that:
	S_NICE,      //this = 2,
	S_SYSTEM,     //this = 3,
	S_IDLE,        //this = 4,
	S_IOWAIT,      // and so on....
    S_IRQ,
    S_SOFTIRQ,
    S_STEAL,
    S_GUEST,
    S_GUEST_NICE
};

class Path {
    public:
        static string basePath() {
            return "/proc/";
        }
        static string cmdPath(){
            return "/cmdline";
        }
        static string statusPath(){
            return "/status";
        }
        static string statPath(){
            return "/stat";
        }
        static string upTimePath(){
            return "uptime";
        }
        static string memInfoPath(){
            return "meminfo";
        }
        static string versionPath(){
            return "version";
        }
};

#endif // CONSTANTS_PATH