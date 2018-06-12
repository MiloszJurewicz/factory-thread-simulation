//
// Created by Admin on 06.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
#define FACTORY_THREAD_SIMULATION_FACTORYWORKER_H


#include <vector>
#include "../resources/Tool.h"
#include "../resources/Workplace.h"
#include "../resources/ProductStockpille.h"

using namespace std;

class Workplace;
extern const int NUMOFWORKERS;
extern const int REFRESHESINSECOND;
extern const std::chrono::milliseconds REFRESHRATE;

class FactoryWorker {
public:

    explicit FactoryWorker(int id);

    virtual ~FactoryWorker();

    void routine(vector<Workplace*> workplaces, mutex & _muGui, ProductStockpille * productStockpille);

    int getId() const;

    const string &getStatus() const;

    int getProgress() const;

    void setRunning(bool running);

private:

    int id;

    string status;

    bool running;

    int progress = 0;

    Workplace *workplace = nullptr;

    void eatSandwich(mutex & _muGui);

    void work(mutex & _muGui, ProductStockpille * productStockpille);

    Workplace *lookForWorkplace(vector<Workplace *> workplaces);

};


#endif //FACTORY_THREAD_SIMULATION_FACTORYWORKER_H
