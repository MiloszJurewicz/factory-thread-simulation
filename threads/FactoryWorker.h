//
// Created by Admin on 06.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
#define FACTORY_THREAD_SIMULATION_FACTORYWORKER_H


#include <vector>
#include "../resources/Tool.h"

using std::mutex;

class FactoryWorker {
public:
    explicit FactoryWorker(int id);

    virtual ~FactoryWorker();

    void routine(std::mutex & _muGui);

    int getId() const;

    void setId(int id);

    bool isIsRunning() const;

    void setIsRunning(bool isRunning);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

private:
    int id;

    bool isRunning;

    std::string status;

    void eatSandwich(mutex & _muGui);

    void work(mutex & _muGui);
};


#endif //FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
