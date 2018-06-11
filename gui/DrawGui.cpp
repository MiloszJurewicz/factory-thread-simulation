
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
    }else if(t->getId() < 15){
        mvprintw(5, 0 + sizeof(msg) * (t->getId() - 10), ("Toold id. " + std::to_string(t->getId())).c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 10), blanks.c_str());
        mvprintw(6, 0 + sizeof(msg) * (t->getId() - 10), ("Status: " + t->getStatus()).c_str());
    }

    refresh();

}

void drawWorkplace(Workplace * w){
    attron(COLOR_PAIR(2));
    std::string clean = "                              ";
    int rows = 0, collumns = 0;

    getmaxyx(stdscr, rows, collumns);
    std::string msg= "Workplace id: " + std::to_string(w->getId());
    std::string msgfree=  "Free        ";
    std::string msgtaken= "taken by: " + std::to_string(w->getTakenBy());
    if(w->getId() % 2 == 0){
        mvprintw(12 + w->getId() * 3, 0 , msg.c_str());
        if(w->getTakenBy() == -1){
            mvprintw(13 + w->getId() * 3, 0 , msgfree.c_str());
        }else{
            mvprintw(13 + w->getId() * 3, 0 , msgtaken.c_str());
        }

    }else{
        mvprintw(12 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ") , msg.c_str());
        if(w->getTakenBy() == -1){
            mvprintw(13 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgfree.c_str());
        }else{
            mvprintw(13 + (w->getId() - 1) * 3, collumns - RIGHTTABLEWIDTH - sizeof(" Workplace id:      ")  , msgtaken.c_str());
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
    if(factoryWorker->getStatus() == "working"){
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), clean.c_str());
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), (status + ": " + to_string(factoryWorker->getProgress())).c_str());
    }else{

        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), clean.c_str());
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), status.c_str());

    }

    /*if(factoryWorker->getStatus() == "Eating sandwich" || factoryWorker->getStatus() == "Looking for workplace" || factoryWorker->getStatus() == "Starting work"){

        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), status.c_str());
    }else if(factoryWorker->getStatus() == "working"){
        mvprintw(5 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), title.c_str());
        mvprintw(6 + factoryWorker->getId() * 4, collumns - sizeof(" Factory worker id:   "), status.c_str());
    }*/

    /*if(factoryWorker->getId() % 2 == 0){
        mvprintw(6 + factoryWorker->getId() * 4, 0 , ("Worker id. " + std::to_string(factoryWorker->getId())).c_str());
        mvprintw(6 + factoryWorker->getId() * 4 + 1, 0 , ("Worker status. " + factoryWorker->getStatus()).c_str());
    } else{
        mvprintw(6 + (factoryWorker->getId() - 1) * 4, collumns - sizeof(msg), ("Worker id. " + std::to_string(factoryWorker->getId())).c_str());
        mvprintw(6 + (factoryWorker->getId() - 1) * 4 + 1, collumns - sizeof(msg), ("Worker id. " + factoryWorker->getStatus()).c_str());
    }*/

    refresh();
}


