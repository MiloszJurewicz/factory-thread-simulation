#include <iostream>
#include <thread>
#include "threads/FactoryWorker.h"
#include "resources/Tool.h"

const static int NUMOFWORKERS = 4;
const static int NUMOFTOOLS = NUMOFWORKERS * 2;

int main() {

    //creating proper amount of tools
    std::vector< std::unique_ptr<Tool> > tools(NUMOFWORKERS);
    for(int i = 0 ; i < NUMOFTOOLS; i++){
        auto t1 = std::unique_ptr<Tool>(new Tool(i));
        tools[i] = move(t1);
    }

    //creating
    return 0;
}