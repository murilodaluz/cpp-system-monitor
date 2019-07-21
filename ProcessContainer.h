#ifndef PROCESS_CONTAINER
#define PROCESS_CONTAINER
#include "Process.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class ProcessContainer {
    public:
        ProcessContainer()
        {
            this->refreshList();
        }
        void refreshList();
        string printList();
        vector<string> getList();

    private:
        vector<Process>_list;
};
#endif