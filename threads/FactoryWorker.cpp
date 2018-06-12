//
// Created by Admin on 06.06.2018.
//

#include <iostream>
#include <thread>
#include <cmath>
#include "FactoryWorker.h"
#include "../gui/DrawGui.h"
#include "../resources/ProductStockpille.h"

using namespace std;

FactoryWorker::FactoryWorker(int id) : id(id) {
    running = true;
}

FactoryWorker::~FactoryWorker() {
    try{
        std::terminate();
    }catch(std::exception& e){
        e.what();
    }
}

void FactoryWorker::routine(vector<Workplace *> workplaces, mutex & _muGui, ProductStockpille * productStockpille) {
    //starting work
    status = "Starting work";

    _muGui.lock();
    drawFactoryWorker(this);
    _muGui.unlock();

    while(running){
        _muGui.lock();
            workplace = lookForWorkplace(workplaces);
            if(workplace != nullptr){
                workplace->setTakenBy(id);
                drawWorkplace(workplace);
            }

        _muGui.unlock();

        if(workplace != nullptr){

            work(_muGui, productStockpille );

            eatSandwich(_muGui);

        }else{
            eatSandwich(_muGui);
        }
    }

    status = "going home";

    _muGui.lock();
    drawFactoryWorker(this);
    _muGui.unlock();
}

Workplace* FactoryWorker::lookForWorkplace(vector<Workplace *> workplaces) {

    status = "Looking for workplace";

    drawFactoryWorker(this);

    vector<Workplace*> freeWorkplaces;
    for (int i = 0; i < workplaces.size(); i++){
        if(!workplaces.at(i)->isTaken()){
            freeWorkplaces.push_back(workplaces[i]);
        }
    }
    if(freeWorkplaces.size() == 0){
        return nullptr;
    }else{
        int c = rand() % freeWorkplaces.size() + 0;
        freeWorkplaces.at(c)->setTaken(true);
        return freeWorkplaces.at(c);
    }
}

void FactoryWorker::work(mutex &_muGui, ProductStockpille * productStockpille) {
    
    status = "Getting tools";
    
    _muGui.lock();     
        drawFactoryWorker(this);
    _muGui.unlock();

    //Ensures there are no deadlocks
    lock(workplace->getTools().at(0)->m, workplace->getTools().at(1)->m, workplace->getTools().at(2)->m);

    //Draw pick up tool
    lock_guard<mutex> a(workplace->getTools().at(0)->m, adopt_lock);

        workplace->getTools().at(0)->setClaimedBy(id);
        workplace->getTools().at(0)->setStatus("Claimed by: " + to_string(id));
    
        _muGui.lock();
            drawTool(workplace->getTools().at(0));
        _muGui.unlock();
    lock_guard<mutex> b(workplace->getTools().at(1)->m, adopt_lock);

        workplace->getTools().at(1)->setClaimedBy(id);
        workplace->getTools().at(1)->setStatus("Claimed by: " + to_string(id));

        _muGui.lock();
            drawTool(workplace->getTools().at(1));
        _muGui.unlock();    
    
    lock_guard<mutex> c(workplace->getTools().at(2)->m, adopt_lock);

        workplace->getTools().at(2)->setClaimedBy(id);
        workplace->getTools().at(2)->setStatus("Claimed by: " + to_string(id));
    
        _muGui.lock();
            drawTool(workplace->getTools().at(2));
        _muGui.unlock();

    status = "working";
    int partsPerProduct = 10;

    for(int i = 0; i < partsPerProduct; i++){

        if(workplace->getParts() == 0){
            status = "Waiting";
            _muGui.lock();
            drawFactoryWorker(this);
            _muGui.unlock();
            while(workplace->getParts() == 0){
                this_thread::sleep_for(REFRESHRATE * 5);
                if(!running){
                    //if programs ends skip adding products since you didnt finish
                    goto  stop;
                }

            }
        }else{
            this_thread::sleep_for(REFRESHRATE);
            progress =  floor(float(i) / float(partsPerProduct) * 100 );

            workplace->_muPartsAccess.lock();
            workplace->setParts(workplace->getParts() - 1);
            workplace->_muPartsAccess.unlock();

            _muGui.lock();
            drawWorkplace(workplace);
            drawFactoryWorker(this);
            _muGui.unlock();
        }

    }

    productStockpille->m.lock();
        productStockpille->addProduct(workplace->getId());
    productStockpille->m.unlock();
    _muGui.lock();
        drawProductStockPile(productStockpille);
    _muGui.unlock();
    //if programs ends skip adding products since you didnt finish
    stop:

    //freeing up resources
    workplace->setTaken(false);
    workplace->setTakenBy(-1);

    drawWorkplace(this->workplace);
    for(int i = 0; i < 3; i++){
        workplace->getTools().at(i)->setClaimedBy(id);
        workplace->getTools().at(i)->setStatus("In toolshop   ");

        //and drawing it
        _muGui.lock();
        drawTool(workplace->getTools().at(i));
        _muGui.unlock();
    }
    workplace = nullptr;
}

void FactoryWorker::eatSandwich(mutex &_muGui) {
    status = "Eating sandwich";
    int eatingTime = 3 + (rand() % /*static_cast<int>*/(5 - 3 + 1));


    for(int i = 0; i < eatingTime * REFRESHESINSECOND; i++){
        std::this_thread::sleep_for(REFRESHRATE);

        _muGui.lock();
        progress = std::floor(float(i) / float(eatingTime * REFRESHESINSECOND) * 100 )  ;
        drawFactoryWorker(this);
        _muGui.unlock();
    }
}

int FactoryWorker::getId() const {
    return id;
}

const string &FactoryWorker::getStatus() const {
    return status;
}

int FactoryWorker::getProgress() const {
    return progress;
}

void FactoryWorker::setRunning(bool running) {
    FactoryWorker::running = running;
}









