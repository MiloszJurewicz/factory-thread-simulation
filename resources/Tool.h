//
// Created by Admin on 08.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_TOOL_H
#define FACTORY_THREAD_SIMULATION_TOOL_H

#include <mutex>
#include "../threads/FactoryWorker.h"

using namespace std;

class FactoryWorker;

extern mutex _muGUI;

class Tool {
public:

    Tool(int id);

    std::mutex m;

    int getId() const;

    int getClaimedBy() const;

    void setClaimedBy(int claimedBy);

    const string &getStatus() const;

    void setStatus(const string &status);

private:

    int id;

    int claimedBy;

    string status;
};

#endif //FACTORY_THREAD_SIMULATION_TOOL_H
