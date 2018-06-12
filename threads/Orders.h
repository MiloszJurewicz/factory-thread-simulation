//
// Created by jupiter on 12.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_ORDERS_H
#define FACTORY_THREAD_SIMULATION_ORDERS_H

#include <array>
#include "../resources/ProductStockpille.h"

using namespace std;

class Orders {
public:

    void routine(mutex &_muGui, ProductStockpille * productStockpille);

    const vector<array<int, 3>> &getOrders() const;

    const string &getStatus() const;

private:
    bool running = true;

    int maxOrders = 10;

    int numOfOrders = 0;

    string status;

    int progress;

    int completingOrder;

    void generateOrders(mutex &_muGui, ProductStockpille * productStockpille);

    void checkOrders(mutex &_muGui, ProductStockpille * productStockpille);

    vector<array<int, 3>> orders;
};


#endif //FACTORY_THREAD_SIMULATION_ORDERS_H
