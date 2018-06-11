#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <curses.h>
//#include <conio.h>
#include "resources/Tool.h"
#include "resources/Workplace.h"
#include "gui/DrawGui.h"

using namespace std;

const int NUMOFWORKERS = 4;
const int NUMOFWORKPLACES = 4;
const int NUMOFTOOLS = NUMOFWORKPLACES * 2;
const int MILISECONDS = 500;
const std::chrono::milliseconds REFRESHRATE(MILISECONDS);
const int REFRESHESINSECOND= 1000/MILISECONDS;
mutex _muGUI;


void stopThreadsTimer(vector<FactoryWorker *> workers){

    //coment out getch and uncomment timer for it to work for given amount of time
    //for some reason u have to press getch twice for program to close (???)
    //std::this_thread::sleep_for(runTimer);
    //getch();

    /*for(int i = 0; i < workers.size(); i++){
        workers.at(i)->setIsRunning(false);
    }*/
}

int main() {

    srand (time(NULL));
    initGui();



    //Vector of tool pointers
    vector<Tool*> tools;
    for(int i = 0; i < NUMOFTOOLS; i++){
        auto *t1 = new Tool(i);
        tools.push_back(t1);
    }


    //setting worker at tool
    //tools.at(0)->setFactoryWorker(&fn);

    vector<Workplace*> workplaces;
    for(int i = 0; i < NUMOFWORKPLACES; i++){

        vector<Tool*> subTools;
        if(i == NUMOFWORKPLACES - 1){
            subTools.push_back( tools.at(i * 2) );
            subTools.push_back( tools.at(i * 2 + 1) );
            subTools.push_back( tools.at(0) );

            Workplace *w = new Workplace(i, subTools);
            workplaces.push_back(w);
        }else{
            subTools.push_back( tools.at(i * 2) );
            subTools.push_back( tools.at(i * 2 + 1) );
            subTools.push_back( tools.at(i * 2 + 2) );

            Workplace *w = new Workplace(i, subTools);
            workplaces.push_back(w);
        }
    }

    vector<thread> tasks(NUMOFWORKERS);

    for(int i = 0; i < NUMOFWORKERS; i++){
        FactoryWorker *f = new FactoryWorker(i);

        tasks[i] = (thread(&FactoryWorker::routine,
                           f,
                           ref(workplaces),
                           ref(_muGUI))
            );

    }

    for(int i = 0; i < tasks.size();i++){
        tasks.at(i).join();
    }


    getch();

    curs_set(FALSE);
    endwin();

    return 0;
}

