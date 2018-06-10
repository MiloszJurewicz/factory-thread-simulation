//
// Created by Admin on 06.06.2018.
//

#include <iostream>
#include <thread>
#include "FactoryWorker.h"

std::chrono::milliseconds refreshRate(200);

FactoryWorker::FactoryWorker(int id) {
    this->id = id;
    isRunning = false;
    status = "limbo";
}

FactoryWorker::~FactoryWorker() {
    try{
        std::terminate();
    }catch(std::exception& e){

    }
}

void FactoryWorker::routine(std::vector<Tool>) {
    //draw Factory worker

    while(isRunning){

    }
}

void FactoryWorker::eatSandwich() {
    status = "I'm on a break";

    std::this_thread::sleep_for(refreshRate);
}

void FactoryWorker::work() {
    status = "Getting tools";


}


