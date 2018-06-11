//
// Created by jupiter on 10.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_DRAWGUI_H
#define FACTORY_THREAD_SIMULATION_DRAWGUI_H

#include "../resources/Tool.h"
#include "../threads/FactoryWorker.h"
#include "../threads/Courier.h"
#include "../resources/PartsStorage.h"

class Courier;

void initGui();
void drawSeparators();
void drawTool(Tool* t);
void drawFactoryWorker(FactoryWorker* factoryWorker);
void drawWorkplace(Workplace * w);
void drawCourier(Courier * courier);
void drawPartsStorage(PartsStorage * partStorage);
void drawProductStockPile(ProductStockpille * productStockpille);
void drawOrders(vector<array<int, 3>> orders);
#endif //FACTORY_THREAD_SIMULATION_DRAWGUI_H
