//
// Created by Admin on 08.06.2018.
//

#include "Tool.h"
#include "../gui/DrawGui.h"

Tool::Tool(int id) {
    this->id = id;
    this->status = "In toolshop";

    drawTool(this);
}

int Tool::getId() const {
    return id;
}


const string &Tool::getStatus() const {
    return status;
}

void Tool::setStatus(const string &status) {
    Tool::status = status;
}

int Tool::getClaimedBy() const {
    return claimedBy;
}

void Tool::setClaimedBy(int claimedBy) {
    Tool::claimedBy = claimedBy;
}

