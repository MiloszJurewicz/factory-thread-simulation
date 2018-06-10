//
// Created by Admin on 08.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_TOOL_H
#define FACTORY_THREAD_SIMULATION_TOOL_H

#include <mutex>
#include "../threads/FactoryWorker.h"

using namespace std;

class FactoryWorker;

class Tool {
public:

    Tool(int id);

    std::mutex m;

    int getId() const;

    void setFactoryWorker(FactoryWorker *factoryWorker);

    FactoryWorker *getFactoryWorker() const;

    const string &getStatus() const;

    void setStatus(const string &status);

private:

    int id;

    string status;

    FactoryWorker* factoryWorker = NULL;
};

#endif //FACTORY_THREAD_SIMULATION_TOOL_H
