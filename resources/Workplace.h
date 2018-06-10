//
// Created by jupiter on 10.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_WORKPLACE_H
#define FACTORY_THREAD_SIMULATION_WORKPLACE_H

#include <iostream>
#include "../threads/FactoryWorker.h"

class Workplace {
public:

    Workplace(int id);

    int getId() const;

    void setId(int id);

    bool isIsTaken() const;

    void setIsTaken(bool isTaken);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    int getParts() const;

    void setParts(int parts);

    int getUsedBy() const;

    void setUsedBy(int usedBy);

private:

    int id;

    bool isTaken;

    int parts;

    std::string status;
};


#endif //FACTORY_THREAD_SIMULATION_WORKPLACE_H

/*
//int id;

bool isTaken;

int parts;

std::string status;

FactoryWorker usedBy = NULL;*/
