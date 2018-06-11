//
// Created by jupiter on 11.06.18.
//

#include "PartsStorage.h"
#include "../gui/DrawGui.h"

PartsStorage::PartsStorage() {
    drawPartsStorage(this);
}

int PartsStorage::getParts() const {
    return parts;
}

void PartsStorage::setParts(int parts) {
    PartsStorage::parts = parts;
}
