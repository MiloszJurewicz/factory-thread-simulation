//
// Created by jupiter on 10.06.18.
//

#include "DrawGui.h"
#include <ncurses.h>
#include <mutex>
#include <cmath>
#include "DrawGui.h"

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
}



void drawTool(int toolId, int isUsedBy, std::string status) {
    attron(COLOR_PAIR(2));
    std::string clean = "                              ";
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    std::string msg= "Toold id. " + std::to_string(toolId);

    if(toolId < 4){
        mvprintw(1, collumns/2 + ((toolId % 4) * 20 - sizeof(msg)) - 10, ("Toold id. " + std::to_string(toolId)).c_str());
        if(isUsedBy == -1){
            mvprintw(2, collumns/2 + ((toolId % 4) * 20 - sizeof(msg)) - 10, ("Status: " + status + "").c_str());
        }else{
            mvprintw(2, collumns/2 + ((toolId % 4) * 20 - sizeof(msg)) - 10, ("Status: " + status + "Used by: " +  std::to_string(isUsedBy)).c_str());
        }
    }else if(toolId < 8){
        mvprintw(4, collumns/2 + ((toolId % 4) * 20  - sizeof(msg)) - 10, ("Toold id. " + std::to_string(toolId)).c_str());
        if(isUsedBy == -1){
            mvprintw(5, collumns/2 + ((toolId % 4) * 20 - sizeof(msg)) - 10, ("Status: " + status + "").c_str());
        }else{
            mvprintw(5, collumns/2 + ((toolId % 4) * 20 - sizeof(msg)) - 10, ("Status: " + status + "Used by worker: " +  std::to_string(isUsedBy)).c_str());
        }
    }

    refresh();

}

void drawFactoryWorker(FactoryWorker* factoryWorker) {
    attron(COLOR_PAIR(2));
    std::string clean = "                              ";
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    std::string msg= "Worker id. " + std::to_string(factoryWorker->getId());
    if(factoryWorker->getId() % 2 == 0){
        mvprintw(6 + factoryWorker->getId() * 4, 0 , ("Worker id. " + std::to_string(factoryWorker->getId())).c_str());
        mvprintw(6 + factoryWorker->getId() * 4 + 1, 0 , ("Worker status. " + factoryWorker->getStatus()).c_str());
    } else{
        mvprintw(6 + (factoryWorker->getId() - 1) * 4, collumns - sizeof(msg), ("Worker id. " + std::to_string(factoryWorker->getId())).c_str());
        mvprintw(6 + (factoryWorker->getId() - 1) * 4 + 1, collumns - sizeof(msg), ("Worker id. " + factoryWorker->getStatus()).c_str());
    }

    refresh();
}
