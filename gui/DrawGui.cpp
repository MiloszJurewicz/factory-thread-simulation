
//
// Created by jupiter on 10.06.18.
//

#include "DrawGui.h"
#include <ncurses.h>
#include <cmath>
#include <thread>

int RIGHTTABLEWIDTH;

void initGui(){

    srand(static_cast<unsigned int>(time(nullptr)));
    initscr();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);

    attron(A_BOLD);
    attron(COLOR_PAIR(1));

    int rows = 0, collumns = 0;
    char projectTitle[] = "Factory";

    getmaxyx( stdscr, rows, collumns);
    mvprintw(0,(collumns / 2) - sizeof(projectTitle) / 2, projectTitle);
    refresh();

    drawSeparators();
}

void drawSeparators(){
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;
    getmaxyx(stdscr, rows, collumns);

    RIGHTTABLEWIDTH = sizeof(" Factory worker id:      ");

    for(int i = 0; i < rows;i++){
        mvprintw(i, collumns - RIGHTTABLEWIDTH, "|");
    }

    for(int i = 0; i < collumns - RIGHTTABLEWIDTH;i++){
        mvprintw(1, i, "=");
    }

    for(int i = 0; i < collumns - RIGHTTABLEWIDTH;i++){
        mvprintw(10, i, "=");
    }

    for(int i = 0; i < collumns - RIGHTTABLEWIDTH;i++){
        mvprintw(rows - 10, i, "=");
    }
    for(int i = 0; i < collumns - RIGHTTABLEWIDTH;i++){
        mvprintw(rows - 4, i, "=");
    }
    refresh();
}


void drawTool(Tool* t) {
    attron(COLOR_PAIR(2));
    std::string clean = "                              ";
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    std::string msg= "Toold id. " + std::to_string(t->getId());
    std::string blanks(("Status: " + t->getStatus()).size(), ' ');

    if(t->getId() < 5){
        mvprintw(2, 0 + sizeof(msg) * t->getId(), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(3, 0 + sizeof(msg) * t->getId(), blanks.c_str());
        mvprintw(3, 0 + sizeof(msg) * t->getId(), ("Status: " + t->getStatus()).c_str());
    }else if(t->getId() < 10){
        mvprintw(5, 0 + sizeof(msg) * (t->getId() - 5), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 5), blanks.c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 5), ("Status: " + t->getStatus()).c_str());
    }else{
        mvprintw(8, 0 + sizeof(msg) * (t->getId() - 10), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(9, 0 + sizeof(msg) * (t->getId() - 10), blanks.c_str());
        mvprintw(9, 0 + sizeof(msg) * (t->getId() - 10), ("Status: " + t->getStatus()).c_str());
    }
    refresh();
}

void drawWorkplace(Workplace * w){
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    string msg= "Workplace id: " + std::to_string(w->getId());
    string msgfree=  "Free        ";
    string msgtaken= "Taken by: " + std::to_string(w->getTakenBy());
    string msgParts= "Parts: " + std::to_string(w->getParts());

    string clean = "Parts:   ";
    if(w->getId() % 2 == 0){
        mvprintw(12 + w->getId() * 3, 0 , msg.c_str());
        if(w->getTakenBy() == -1){
            mvprintw(13 + w->getId() * 3, 0 , msgfree.c_str());
            mvprintw(14 + w->getId() * 3, 0 , clean.c_str());
            mvprintw(14 + w->getId() * 3, 0 , msgParts.c_str());
        }else{
            mvprintw(13 + w->getId() * 3, 0 , msgtaken.c_str());
            mvprintw(14 + w->getId() * 3, 0 , clean.c_str());
            mvprintw(14 + w->getId() * 3, 0 , msgParts.c_str());
        }
    }else{
        mvprintw(12 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ") , msg.c_str());
        if(w->getTakenBy() == -1){
            mvprintw(13 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgfree.c_str());
            mvprintw(14 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , clean.c_str());
            mvprintw(14 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgParts.c_str());
        }else{
            mvprintw(13 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgtaken.c_str());
            mvprintw(14 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , clean.c_str());
            mvprintw(14 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgParts.c_str());
        }
    }
    refresh();
}


void drawFactoryWorker(FactoryWorker* factoryWorker) {
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);

    std::string title = "Worker id. " + std::to_string(factoryWorker->getId());
    std::string status = "-" + factoryWorker->getStatus();
    std::string clean = "                       ";

    mvprintw(5 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), title.c_str());
    if(factoryWorker->getStatus() == "working" || factoryWorker->getStatus() == "Eating sandwich"){
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), clean.c_str());
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), (status + ": " + to_string(factoryWorker->getProgress())).c_str());
    }else{
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), clean.c_str());
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), status.c_str());
    }
    refresh();
}

void drawCourier(Courier *courier) {
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;
    int offset = 12;
    string title = "Courier id: " + to_string(courier->getId());
    string status = courier->getStatus() + ": " + to_string(courier->getProgress()) + " p";
    string workplace = "To workplace: " + to_string(courier->getCurrentWorkplace());
    string clean((courier->getStatus() + "         ").size(), ' ');
    string tmp = "To Workplace    ";
    string clean2(tmp.size(), ' ');
    getmaxyx(stdscr, rows, collumns);
    if(courier->getStatus() == "delivering parts"){
        if(courier->getId() % 2 == 0){
            mvprintw(rows/2 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, title.c_str());
            mvprintw(rows/2 + 1 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, clean.c_str());
            mvprintw(rows/2 + 1 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, status.c_str());
            mvprintw(rows/2 + 2 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, clean2.c_str());
            mvprintw(rows/2 + 2 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, workplace.c_str());
        }else{
            mvprintw(rows/2 + (courier->getId() - 1) * 4, collumns/2  + offset, title.c_str());
            mvprintw(rows/2 + 1 + (courier->getId() - 1) * 4, collumns/2  + offset, clean.c_str());
            mvprintw(rows/2 + 1 + (courier->getId() - 1) * 4, collumns/2  + offset, status.c_str());
            mvprintw(rows/2 + 2 + (courier->getId() - 1) * 4, collumns/2  + offset, clean2.c_str());
            mvprintw(rows/2 + 2 + (courier->getId() - 1) * 4, collumns/2  + offset, workplace.c_str());
        }
    }else{
        if(courier->getId() % 2 == 0){
            mvprintw(rows/2 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, title.c_str());
            mvprintw(rows/2 + 1 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, clean.c_str());
            mvprintw(rows/2 + 1 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, status.c_str());
            mvprintw(rows/2 + 2 + courier->getId() * 4, collumns/2 - sizeof(title) - offset, clean2.c_str());
        } else{
            mvprintw(rows/2 + (courier->getId() - 1) * 4, collumns/2  + offset, title.c_str());
            mvprintw(rows/2 + 1 + (courier->getId() - 1) * 4, collumns/2  + offset, clean.c_str());
            mvprintw(rows/2 + 1 + (courier->getId() - 1) * 4, collumns/2  + offset, status.c_str());
            mvprintw(rows/2 + 2 + (courier->getId() - 1) * 4, collumns/2  + offset, clean2.c_str());
        }
    }


    refresh();
}

void drawPartsStorage(PartsStorage *partStorage) {
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;

    string title = "Main part storage";
    getmaxyx(stdscr, rows, collumns);
    mvprintw(rows/2, collumns/2 - sizeof(title)/2, title.c_str());
    mvprintw(rows/2 + 1, collumns/2 - sizeof("Parts: " + to_string(partStorage->getParts()))/2, ("Parts: " + to_string(partStorage->getParts())).c_str());
    refresh();
}

void drawProductStockPile(ProductStockpille *productStockpille) {
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;

    string title = "Main part storage";
    string productA = "Product 0: " + to_string(productStockpille->getProducts0());
    string productB = "Product 1: " + to_string(productStockpille->getProducts1());
    string productC = "Product 2: " + to_string(productStockpille->getProducts2());
    string productD = "Product 3: " + to_string(productStockpille->getProducts3());

    getmaxyx(stdscr, rows, collumns);

    mvprintw(rows - 8, collumns/2 - sizeof(title)/2, title.c_str());
    mvprintw(rows - 7, collumns/2 - sizeof(productA) - 5, productA.c_str());
    mvprintw(rows - 7, collumns/2 + 5, productB.c_str());
    mvprintw(rows - 5, collumns/2 - sizeof(productB) - 5, productC.c_str());
    mvprintw(rows - 5, collumns/2 + 5, productD.c_str());

    refresh();
}

void drawOrders(vector<array<int, 3>> orders){
    attron(COLOR_PAIR(2));
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    string ordersNames = "Orders: ";
    string clean(RIGHTTABLEWIDTH, ' ');

    for(int i = 0;i < orders.size();i++){

        for(int j = 0; j < 3; j++){
            ordersNames += to_string(orders.at(i).at(j)) + "," ;
        }

        ordersNames += " ; " ;
    }
    mvprintw(rows - 3, 0, clean.c_str());
    mvprintw(rows - 3, 0, ordersNames.c_str());
}


