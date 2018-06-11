//
// Created by jupiter on 12.06.18.
//

#include <random>
#include "Orders.h"
#include "../gui/DrawGui.h"
#include <array>
#include <iostream>

//using namespace std;




void Orders::generateOrders(mutex &_muGui, ProductStockpille * productStockpille) {
    if(orders.size() == maxOrders){
        return;
    }else{
        random_device r;
        seed_seq seed{r(), r(),r(), r(),r(), r(),r(), r()};
        mt19937 eng{seed};

        uniform_int_distribution<>dist (0,3);
        //cout << dist(eng);
        array<int, 3> order = {dist(eng), dist(eng), dist(eng)};

        orders.push_back(order);

        drawOrders(orders);
    }

}

void Orders::routine(mutex &_muGui, ProductStockpille * productStockpille) {
    while(running){
        generateOrders(_muGui, productStockpille);

        checkOrders(_muGui, productStockpille);
    }



}

void Orders::checkOrders(mutex &_muGui, ProductStockpille * productStockpille) {

    int product0 = 0;
    int product1 = 0;
    int product2 = 0;
    int product3 = 0;

    for(int i = 0; i < orders.size(); i++){

        product0 = 0;
        product1 = 0;
        product2 = 0;
        product3 = 0;

        for(int j = 0; j < orders.at(i).size(); j++){
            if(j == 0 ){
                product0++;
            }else if(j == 1 ){
                product1++;
            }else if(j == 2 ){
                product2++;
            }else if(j == 3 ){
                product3++;
            }
        }


        if(productStockpille->getProducts0() > product0 && productStockpille->getProducts1() > product1
           && productStockpille->getProducts2() > product2 && productStockpille->getProducts3() > product3){
            productStockpille->m.lock();
                productStockpille->setProducts0(productStockpille ->getProducts0() - product0);
                productStockpille->setProducts0(productStockpille ->getProducts1() - product1);
                productStockpille->setProducts0(productStockpille ->getProducts2() - product2);
                productStockpille->setProducts0(productStockpille ->getProducts3() - product3);
            productStockpille->m.unlock();
        }
    }
}
