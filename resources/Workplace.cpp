//
// Created by jupiter on 10.06.18.
//

#include "Workplace.h"

Workplace::Workplace(int id) : id(id) {
    this->status = "free";
    this->isTaken = false;
    this->parts = 50;
}

int Workplace::getId() const {
    return id;
}

void Workplace::setId(int id) {
    Workplace::id = id;
}

bool Workplace::isIsTaken() const {
    return isTaken;
}

void Workplace::setIsTaken(bool isTaken) {
    Workplace::isTaken = isTaken;
}

const std::string &Workplace::getStatus() const {
    return status;
}

void Workplace::setStatus(const std::string &status) {
    Workplace::status = status;
}

int Workplace::getParts() const {
    return parts;
}

void Workplace::setParts(int parts) {
    Workplace::parts = parts;
}





