//
// Created by Admin on 08.06.2018.
//

#include "Tool.h"
#include "../gui/DrawGui.h"

Tool::Tool(int id) {
    this->id = id;
    this->status = "In toolshop";
    this->factoryWorker = NULL;

    drawTool(this);
}

int Tool::getId() const {
    return id;
}

void Tool::setFactoryWorker(FactoryWorker *factoryWorker) {
    Tool::factoryWorker = factoryWorker;

    _muGUI.lock();
    if(this->factoryWorker == NULL){
        status = "In toolshop";
        drawTool(this);

    }else{
        status = "Taken by: " + this->factoryWorker->getId();
        drawTool(this);
    }
    _muGUI.unlock();
}

FactoryWorker *Tool::getFactoryWorker() const {
    return factoryWorker;
}

const string &Tool::getStatus() const {
    return status;
}

void Tool::setStatus(const string &status) {
    Tool::status = status;
}

