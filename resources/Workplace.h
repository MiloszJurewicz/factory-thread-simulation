//
// Created by jupiter on 10.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_WORKPLACE_H
#define FACTORY_THREAD_SIMULATION_WORKPLACE_H

#include <iostream>
#include "../threads/FactoryWorker.h"

using namespace std;
class Tool;
class FactoryWorker;

class Workplace {
public:

    Workplace(int id, const vector<Tool *> &tools);

    mutex _muPartsAccess;

    const vector<Tool *> &getTools() const;

    int getId() const;

    bool isTaken() const;

    void setTaken(bool taken);

    int getTakenBy() const;

    void setTakenBy(int takenBy);

    int getParts() const;

    void setParts(int parts);

private:

    int id;

    int takenBy = -1;

    int parts = 20;

    bool taken;

    vector<Tool*> tools;

};


#endif //FACTORY_THREAD_SIMULATION_WORKPLACE_H

/*
//int id;

bool isTaken;

int parts;

std::string status;

FactoryWorker usedBy = NULL;*/
