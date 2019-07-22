void ProcessContainer::refreshList(){
    std::vector<std::string> pids = ProcessParser::getPidList();
    this->_list.clear();
    for (auto pid : pids) {
        Process proc(pid);
        this->_list.push_back(proc);
    }
}

std::string ProcessContainer::printList(){
    std::string result="";
    for (auto i : _list) {
        result += i.getProcess();
    }
    return result;
}

std::vector<std::vector<std::string>> ProcessContainer::getList(){  //return type of vector string.
                                                                            //initialize and fetching the values of List
    std::vector<std::vector<std::string>> values;  //a vector of strings called values  
    std::vector<std::string> stringifiedList;
    for (auto i : _list) {
        stringifiedList.push_back(i.getProcess());
    }
    int lastIndex = 0;
    for (int i=0; i<stringifiedList.size();i++){  //the example has size -10 as starting point of iterator??
        if(i %10 == 0 && i > 0){
          std::vector<std::string>  sub(&stringifiedList[i-10], &stringifiedList[i]);
          values.push_back(sub);
          lastIndex = i;
        }
        if(i == (ProcessContainer::_list.size() - 1) && (i-lastIndex)<10){  
            std::vector<std::string> sub(&stringifiedList[lastIndex],&stringifiedList[i+1]);
            values.push_back(sub);
        }
   }
    return values;
}