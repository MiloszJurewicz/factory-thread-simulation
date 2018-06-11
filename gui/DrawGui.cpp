
//
// Created by jupiter on 10.06.18.
//

#include "DrawGui.h"
#include <ncurses.h>
#include <cmath>
#include <thread>

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

    for(int i = 0; i < rows;i++){
        mvprintw(i, collumns - sizeof(" Factory worker id: "), "|");
    }

    for(int i = 0; i < collumns - sizeof(" Factory worker id: ");i++){
        mvprintw(1, i, "=");
    }

    for(int i = 0; i < collumns - sizeof(" Factory worker id: ");i++){
        mvprintw(10, i, "=");
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

    if(t->getId() < 6){
        mvprintw(2, 0 + sizeof(msg) * t->getId(), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(3, 0 + sizeof(msg) * t->getId(), blanks.c_str());
        //this_thread::sleep_for(REFRESHRATE * 5) ;
        mvprintw(3, 0 + sizeof(msg) * t->getId(), ("Status: " + t->getStatus()).c_str());
        //this_thread::sleep_for(REFRESHRATE) ;


    }else if(t->getId() < 12){
        mvprintw(5, 0 + sizeof(msg) * (t->getId() - 6), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 6), blanks.c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 6), ("Status: " + t->getStatus()).c_str());
        //this_thread::sleep_for(REFRESHRATE * 5) ;
    }

    refresh();

}

/*
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

void drawWorkplace() {

}
*/
