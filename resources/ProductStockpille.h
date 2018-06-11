//
// Created by jupiter on 11.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_PRODUCTSTOCKPILLE_H
#define FACTORY_THREAD_SIMULATION_PRODUCTSTOCKPILLE_H

#include <mutex>

using namespace std;

class ProductStockpille {
public:
    ProductStockpille();

    mutex m;

    void addProduct(int workplaceId);

    int getProducts0() const;

    void setProducts0(int products0);

    int getProducts1() const;

    void setProducts1(int products1);

    int getProducts2() const;

    void setProducts2(int products2);

    int getProducts3() const;

    void setProducts3(int products3);

private:

    int products0 = 0;

    int products1 = 0;

    int products2 = 0;

    int products3 = 0;
};


#endif //FACTORY_THREAD_SIMULATION_PRODUCTSTOCKPILLE_H
