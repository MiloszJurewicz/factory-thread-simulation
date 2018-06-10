//
// Created by Admin on 08.06.2018.
//

#include "Tool.h"
#include "../gui/DrawGui.h"

Tool::Tool(int id) {
    this->id = id;
    this->isBeingUsed = false;
    this->status = "In toolshop";
    this->factoryWorker = NULL;

    drawTool(this);
}

int Tool::getId() const {
    return id;
}

void Tool::setId(int id) {
    Tool::id = id;
}

bool Tool::isIsBeingUsed() const {
    return isBeingUsed;
}

void Tool::setIsBeingUsed(bool isBeingUsed) {
    Tool::isBeingUsed = isBeingUsed;
}

const std::string &Tool::getStatus() const {
    return status;
}

void Tool::setStatus(const std::string &status) {
    Tool::status = status;
}

FactoryWorker *Tool::getFactoryWorker() const {
    return factoryWorker;
}

void Tool::setFactoryWorker(FactoryWorker *factoryWorker) {
    Tool::factoryWorker = factoryWorker;
}
