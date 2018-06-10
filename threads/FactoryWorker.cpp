//
// Created by Admin on 06.06.2018.
//

#include <iostream>
#include <thread>
#include "FactoryWorker.h"
#include "../gui/DrawGui.h"

using std::mutex;
std::chrono::milliseconds refreshRate(200);

FactoryWorker::FactoryWorker(int id) {
    this->id = id;
    this->isRunning = true;
    this->status = "limbo";
}

FactoryWorker::~FactoryWorker() {
    try{
        std::terminate();
    }catch(std::exception& e){

    }
}

void FactoryWorker::routine(mutex & _muGui) {
    status = "Time to work";

    _muGui.lock();
    //drawFactoryWorker(this);
    _muGui.unlock();

    while(isRunning){
        eatSandwich(_muGui);
        work(_muGui);
    }
}

void FactoryWorker::eatSandwich(mutex & _muGui) {
    this->status = "I'm on a break";

    _muGui.lock();
    //drawFactoryWorker(this);
    _muGui.unlock();

}

void FactoryWorker::work(mutex & _muGui) {
    this->status = "Getting tools";

    _muGui.lock();
    //drawFactoryWorker(this);
    _muGui.unlock();
}

int FactoryWorker::getId() const {
    return id;
}

void FactoryWorker::setId(int id) {
    FactoryWorker::id = id;
}

bool FactoryWorker::isIsRunning() const {
    return isRunning;
}

void FactoryWorker::setIsRunning(bool isRunning) {
    FactoryWorker::isRunning = isRunning;
}

const std::string &FactoryWorker::getStatus() const {
    return status;
}

void FactoryWorker::setStatus(const std::string &status) {
    FactoryWorker::status = status;
}

