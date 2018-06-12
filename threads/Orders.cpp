//
// Created by jupiter on 12.06.18.
//

#include <random>
#include "Orders.h"
#include "../gui/DrawGui.h"
#include <thread>

//using namespace std;




void Orders::generateOrders(mutex &_muGui) {

    status = "generating orders";
    int eatingTime = 3 + (rand() % (4 - 3 + 1));
    for(int i = 0; i < eatingTime * REFRESHESINSECOND; i++){
        std::this_thread::sleep_for(REFRESHRATE);

        _muGui.lock();
        progress = std::floor(float(i) / float(eatingTime * REFRESHESINSECOND) * 100 )  ;
            drawOrders(this);
        _muGui.unlock();
    }


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

        drawOrders(this);
    }

}

void Orders::routine(mutex &_muGui, ProductStockpille * productStockpille) {

    status = "Starting work";
    _muGui.lock();
        drawOrders(this);
    _muGui.unlock();
    while(running){
        generateOrders(_muGui);

        checkOrders(_muGui, productStockpille);
    }

    status = "going home";
    _muGui.lock();
        drawOrders(this);
    _muGui.unlock();

}

void Orders::checkOrders(mutex &_muGui, ProductStockpille * productStockpille) {

    status = "completing orders";


    int product0 = 0;
    int product1 = 0;
    int product2 = 0;
    int product3 = 0;

    for(int i = 0; i < orders.size(); i++){

        std::this_thread::sleep_for(REFRESHRATE);

        _muGui.lock();
            progress = std::floor(float(i) / float(orders.size()) * 100 )  ;
            drawOrders(this);
        _muGui.unlock();

        product0 = 0;
        product1 = 0;
        product2 = 0;
        product3 = 0;

        for(int j = 0; j < orders.at(i).size(); j++){
            if(orders.at(i).at(j) == 0 ){
                product0++;
            }else if(orders.at(i).at(j) == 1 ){
                product1++;
            }else if(orders.at(i).at(j) == 2 ){
                product2++;
            }else if(orders.at(i).at(j) == 3 ){
                product3++;
            }
        }

        if(productStockpille->getProducts0() >= product0 && productStockpille->getProducts1() >= product1
           && productStockpille->getProducts2() >= product2 && productStockpille->getProducts3() >= product3){

            completingOrder = i;
            status = "Packing order: " + to_string(completingOrder);

            int eatingTime = 3 + (rand() % (10 - 3 + 1));
            for(int z = 0; z < eatingTime * REFRESHESINSECOND; z++){
                std::this_thread::sleep_for(REFRESHRATE);

                _muGui.lock();
                progress = std::floor(float(z) / float(eatingTime * REFRESHESINSECOND) * 100 )  ;
                drawOrders(this);
                _muGui.unlock();
            }

            productStockpille->m.lock();
                productStockpille->setProducts0(productStockpille ->getProducts0() - product0);
                productStockpille->setProducts1(productStockpille ->getProducts1() - product1);
                productStockpille->setProducts2(productStockpille ->getProducts2() - product2);
                productStockpille->setProducts3(productStockpille ->getProducts3() - product3);
            productStockpille->m.unlock();



            orders.erase(orders.begin() + i);

            _muGui.lock();
                drawProductStockPile(productStockpille);
                drawOrders(this);
            _muGui.unlock();

            completingOrder = 0;
        }
    }
}

const vector<array<int, 3>> &Orders::getOrders() const {
    return orders;
}

const string &Orders::getStatus() const {
    return status;
}

void Orders::setRunning(bool running) {
    Orders::running = running;
}
