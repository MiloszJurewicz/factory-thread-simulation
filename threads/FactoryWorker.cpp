//
// Created by Admin on 06.06.2018.
//

#include <iostream>
#include <thread>
#include <cmath>
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

    _muGui.lock();
    //drawFactoryWorker(this);
    _muGui.unlock();

    while(running){
        _muGui.lock();
            workplace = lookForWorkplace(workplaces);
            if(workplace != nullptr){
                workplace->setTakenBy(id);
                drawWorkplace(workplace);
            }

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

void FactoryWorker::work(mutex &_muGui) {

    _muGui.lock();
    status = "Getting tools";
    //Draw Worker
    drawFactoryWorker(this);
    _muGui.unlock();

    //Ensures there are no deadlocks
    lock(workplace->getTools().at(0)->m, workplace->getTools().at(1)->m, workplace->getTools().at(2)->m);

    //Draw pick up tool
    lock_guard<mutex> a(workplace->getTools().at(0)->m, adopt_lock);
    //setting each tools parameters
    workplace->getTools().at(0)->setClaimedBy(id);
    workplace->getTools().at(0)->setStatus("Claimed by: " + to_string(id));
    //and drawing it
    drawTool(workplace->getTools().at(0));

    lock_guard<mutex> b(workplace->getTools().at(1)->m, adopt_lock);
    //setting each tools parameters
    workplace->getTools().at(1)->setClaimedBy(id);
    workplace->getTools().at(1)->setStatus("Claimed by: " + to_string(id));
    //and drawing it
    drawTool(workplace->getTools().at(1));

    lock_guard<mutex> c(workplace->getTools().at(2)->m, adopt_lock);
    //setting each tools parameters
    workplace->getTools().at(2)->setClaimedBy(id);
    workplace->getTools().at(2)->setStatus("Claimed by: " + to_string(id));
    //and drawing it
    drawTool(workplace->getTools().at(2));

    status = "working";
    progress = 0;
    int workingTime = 3 + (rand() % (6 - 3 + 1));
    for(int i = 0; i < workingTime * REFRESHESINSECOND; i++){
        this_thread::sleep_for(REFRESHRATE);

        progress =  floorf(float(i) / float(workingTime * REFRESHESINSECOND) * 100 ) ;

        _muGui.lock();
        drawFactoryWorker(this);
        _muGui.unlock();
    }

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
    int meditateTime = 3 + (rand() % /*static_cast<int>*/(5 - 3 + 1));


    for(int i = 0; i < meditateTime * REFRESHESINSECOND; i++){
        std::this_thread::sleep_for(REFRESHRATE);

        _muGui.lock();
        drawFactoryWorker(this);
        _muGui.unlock();
    }

}

const string &FactoryWorker::getStatus() const {
    return status;
}

float FactoryWorker::getProgress() const {
    return progress;
}









