//
// Created by jupiter on 11.06.18.
//

#include <iostream>
#include "ProductStockpille.h"
#include "../gui/DrawGui.h"

using namespace std;

ProductStockpille::ProductStockpille() {
    drawProductStockPile(this);
}

void ProductStockpille::addProduct(int workplaceId) {
    if(workplaceId % 4 == 0 ){
        products0++;
    }else if(workplaceId % 4 == 1 ){
        products1++;
    }else if(workplaceId % 4 == 2 ){
        products2++;
    }else if(workplaceId % 4 == 3 ){
        products3++;
    }else{
        cout << "shouldnt be here" << endl;
    }
}

int ProductStockpille::getProducts0() const {
    return products0;
}

void ProductStockpille::setProducts0(int products0) {
    ProductStockpille::products0 = products0;
}

int ProductStockpille::getProducts1() const {
    return products1;
}

void ProductStockpille::setProducts1(int products1) {
    ProductStockpille::products1 = products1;
}

int ProductStockpille::getProducts2() const {
    return products2;
}

void ProductStockpille::setProducts2(int products2) {
    ProductStockpille::products2 = products2;
}

int ProductStockpille::getProducts3() const {
    return products3;
}

void ProductStockpille::setProducts3(int products3) {
    ProductStockpille::products3 = products3;
}

