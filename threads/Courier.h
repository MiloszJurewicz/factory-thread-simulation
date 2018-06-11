//
// Created by jupiter on 11.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_COURIER_H
#define FACTORY_THREAD_SIMULATION_COURIER_H

#include "../gui/DrawGui.h"

using namespace std;

class PartsStorage;

class Courier {

public:

    explicit Courier(int id);

    void routine(vector<Workplace*> workplaces, mutex & _muGui, PartsStorage * partsStorage);

    int getId() const;

    const string &getStatus() const;

    int getProgress() const;

    int getCurrentWorkplace() const;

private:
    int id;

    bool running;

    string status;

    int progress = 0;

    int currentWorkplace;

    int workplacesAmount;

    int partsDelivered = 10;

    void stockUp(mutex &_muGui, PartsStorage * partsStorage);

    void deliverParts(vector<Workplace*> workplaces, mutex &_muGui);

    void breakTime(mutex &_muGui);
};


#endif //FACTORY_THREAD_SIMULATION_COURIER_H
