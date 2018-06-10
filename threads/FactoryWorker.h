//
// Created by Admin on 06.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
#define FACTORY_THREAD_SIMULATION_FACTORYWORKER_H


#include <vector>
#include "../resources/Tool.h"

class FactoryWorker {
public:
    explicit FactoryWorker(int id);
    virtual ~FactoryWorker();

private:
    int id;
    bool isRunning;
    std::string status;

    void routine(std::vector<Tool>);
    void eatSandwich();
    void work();
};


#endif //FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
