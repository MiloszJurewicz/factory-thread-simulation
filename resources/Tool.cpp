//
// Created by Admin on 08.06.2018.
//

#include "Tool.h"
#include "../gui/DrawGui.h"

Tool::Tool(int id) {
    this->id = id;
    this->status = "In toolshop";
    this->factoryWorker = NULL;
}

int Tool::getId() const {
    return id;
}

void Tool::setFactoryWorker(FactoryWorker *factoryWorker) {
    Tool::factoryWorker = factoryWorker;
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

