//
// Created by jupiter on 10.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_DRAWGUI_H
#define FACTORY_THREAD_SIMULATION_DRAWGUI_H

#include "../resources/Tool.h"
#include "../threads/FactoryWorker.h"

void initGui();
void drawSeparators();
void drawTool(Tool* t);
//void drawFactoryWorker(FactoryWorker* factoryWorker);
void drawWorkplace();
#endif //FACTORY_THREAD_SIMULATION_DRAWGUI_H
