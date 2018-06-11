//
// Created by jupiter on 11.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_PARTSSTORAGE_H
#define FACTORY_THREAD_SIMULATION_PARTSSTORAGE_H

#include <mutex>

using namespace std;

class PartsStorage {
public:

    PartsStorage();

    mutex m;

    int getParts() const;

    void setParts(int parts);

private:
    int parts = 50000;
};


#endif //FACTORY_THREAD_SIMULATION_PARTSSTORAGE_H
