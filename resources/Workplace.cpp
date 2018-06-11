//
// Created by jupiter on 10.06.18.
//

#include "Workplace.h"
#include "../gui/DrawGui.h"

using namespace std;

Workplace::Workplace(int id, const vector<Tool *> &tools) : id(id), tools(tools) {
    this->taken = false;

    drawWorkplace(this);
}

int Workplace::getId() const {
    return id;
}

const vector<Tool *> &Workplace::getTools() const {
    return tools;
}

bool Workplace::isTaken() const {
    return taken;
}

void Workplace::setTaken(bool taken) {
    Workplace::taken = taken;
}

int Workplace::getTakenBy() const {
    return takenBy;
}

void Workplace::setTakenBy(int takenBy) {
    Workplace::takenBy = takenBy;
}
