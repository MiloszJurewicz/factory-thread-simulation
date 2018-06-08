//
// Created by Admin on 06.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
#define FACTORY_THREAD_SIMULATION_FACTORYWORKER_H



class FactoryWorker {
public:
    FactoryWorker();
private:
    int id;
    bool isWorking;
    std::string status;
};


#endif //FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
