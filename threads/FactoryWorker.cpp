//
// Created by Admin on 06.06.2018.
//

#include <iostream>
#include <thread>
#include "FactoryWorker.h"
#include "../gui/DrawGui.h"

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

int FactoryWorker::getId() const {
    return id;
}

void FactoryWorker::routine(vector<Workplace *> workplaces, mutex & _muGui) {
    //starting work
    status = "Starting work";


    while(running){
        _muGui.lock();
        workplace = lookForWorkplace(workplaces);
        _muGui.unlock();

        if(workplace != NULL){

            work(_muGui);

            eatSandwich(_muGui);

        }else{
            eatSandwich(_muGui);
        }
    }


}

Workplace* FactoryWorker::lookForWorkplace(vector<Workplace *> workplaces) {

    vector<Workplace*> freeWorkplaces;
    for (int i = 0; i < workplaces.size(); i++){
        if(!workplaces.at(i)->isTaken()){
            freeWorkplaces.push_back(workplaces[i]);
        }
    }
    if(freeWorkplaces.size() == 0){
        return NULL;
    }else{
        int c = rand() % freeWorkplaces.size() + 0;
        freeWorkplaces.at(c)->setTaken(true);
        return freeWorkplaces.at(c);
    }


}

void FactoryWorker::work(mutex &_muGui) {

    status = "Getting tools";
    //Draw Worker

    //Ensures there are no deadlocks
    lock(workplace->getTools().at(0)->m, workplace->getTools().at(1)->m, workplace->getTools().at(2)->m);

    //Draw pick up tool
    lock_guard<mutex> a(workplace->getTools().at(0)->m, adopt_lock);
    workplace->getTools().at(0)->setFactoryWorker(this);

    lock_guard<mutex> b(workplace->getTools().at(1)->m, adopt_lock);
    workplace->getTools().at(1)->setFactoryWorker(this);

    lock_guard<mutex> c(workplace->getTools().at(2)->m, adopt_lock);
    workplace->getTools().at(2)->setFactoryWorker(this);

    status = "working";
    int workingTime = 3 + (rand() % (6 - 3 + 1));
    for(int i = 0; i < workingTime * REFRESHESINSECOND; i++){
        this_thread::sleep_for(REFRESHRATE);

    }
    workplace->setTaken(false);

    //cout << "Factoryworker: " << id << "done" << endl;
}

void FactoryWorker::eatSandwich(mutex &_muGui) {
    status = "meditating";
    int meditateTime = 3 + (rand() % /*static_cast<int>*/(5 - 3 + 1));

    for(int i = 0; i < meditateTime * REFRESHESINSECOND; i++){
        std::this_thread::sleep_for(REFRESHRATE);
    }
}









