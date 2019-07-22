#ifndef PROCESS_CONTAINER
#define PROCESS_CONTAINER
#include "Process.h"
#include <string>
#include <vector>

class ProcessContainer {
    private:
        std::vector<Process>_list;
        
    public:
        ProcessContainer()
        {
            this->refreshList();
        }
        void refreshList();
        std::string printList();
        std::vector<std::vector<std::string>> getList();
};
#endif