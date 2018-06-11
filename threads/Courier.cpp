//
// Created by jupiter on 11.06.18.
//

#include <thread>
#include <cmath>
#include "Courier.h"

using namespace std;

Courier::Courier(int id) : id(id) {
    running = true;
}

void Courier::routine(vector<Workplace*> workplaces, mutex &_muGui, PartsStorage * partsStorage) {
    status = "Starting work";

    _muGui.lock();
        drawCourier(this);
    _muGui.unlock();

    workplacesAmount = workplaces.size();

    while(running){

        stockUp(_muGui, partsStorage);

        deliverParts(workplaces, _muGui);
        
        breakTime(_muGui);
    }
}

void Courier::stockUp(mutex &_muGui, PartsStorage * partsStorage) {
    status = "stocking up";

    int stockingTime = 3 + (rand() % (5 - 3 + 1));

    partsStorage->m.lock();
    for(int i = 0; i < stockingTime * REFRESHESINSECOND; i++){
        std::this_thread::sleep_for(REFRESHRATE);
        progress =  floor(float(i) / float(stockingTime * REFRESHESINSECOND) * 100 );

        _muGui.lock();
            drawCourier(this);
        _muGui.unlock();
    }
    partsStorage->setParts(partsStorage->getParts() - workplacesAmount * partsDelivered);
    _muGui.lock();
        drawPartsStorage(partsStorage);
    _muGui.unlock();
    partsStorage->m.unlock();
    progress = 0;
}

void Courier::deliverParts(vector<Workplace*> workplaces, mutex &_muGui) {
    status = "delivering parts";

    for(int i = 0; i < workplaces.size(); i++){
        currentWorkplace = workplaces.at(i)->getId();
        if(workplaces.at(i)->getParts() < 50){
            for(int j = 0; j < partsDelivered; j++){
                std::this_thread::sleep_for(REFRESHRATE);
                progress = floor(float(j) / float(partsDelivered) * 100);
                _muGui.lock();
                    drawCourier(this);
                _muGui.unlock();

                workplaces.at(i)->_muPartsAccess.lock();
                    workplaces.at(i)->setParts(workplaces.at(i)->getParts() + 1);
                workplaces.at(i)->_muPartsAccess.unlock();

                _muGui.lock();
                drawWorkplace(workplaces.at(i));
                _muGui.unlock();
            }
        }


        /*int eatingTime = 3 + (rand() % (3 - 3 + 1));
        for(int j = 0; j < eatingTime * REFRESHESINSECOND; j++){
            std::this_thread::sleep_for(REFRESHRATE);
            progress = floor(float(j) / float(eatingTime * REFRESHESINSECOND) * 100 );
            _muGui.lock();
                drawCourier(this);
            _muGui.unlock();
        }

        workplaces.at(i)->_muPartsAccess.lock();
            workplaces.at(i)->setParts(workplaces.at(i)->getParts() + 10);
        workplaces.at(i)->_muPartsAccess.unlock();

        _muGui.lock();
            drawWorkplace(workplaces.at(i));
        _muGui.unlock();*/
    }

    currentWorkplace = -1;
}

void Courier::breakTime(mutex &_muGui) {
    status = "sandwich time";
    int breakTime = 3 + (rand() % (3 - 3 + 1));
    for(int j = 0; j < breakTime * REFRESHESINSECOND; j++){
        std::this_thread::sleep_for(REFRESHRATE);
        progress = floor(float(j) / float(breakTime * REFRESHESINSECOND) * 100 );
        _muGui.lock();
            drawCourier(this);
        _muGui.unlock();
       }
}

int Courier::getId() const {
   return id;
}

const string &Courier::getStatus() const {
   return status;
}

int Courier::getProgress() const {
   return progress;
}

int Courier::getCurrentWorkplace() const {
   return currentWorkplace;
}


