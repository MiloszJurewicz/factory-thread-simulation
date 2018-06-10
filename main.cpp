#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <conio.h>
#include "resources/Tool.h"
#include "resources/Workplace.h"
#include "gui/DrawGui.h"

using namespace std;

const int NUMOFWORKERS = 4;
const int NUMOFWORKPLACES = 4;
const int NUMOFTOOLS = NUMOFWORKERS * 2;
const int MILISECONDS = 200;
const std::chrono::milliseconds REFRESHRATE(MILISECONDS);
const int REFRESHESINSECOND= 1000/MILISECONDS;
mutex _muGUI;


void stopThreadsTimer(vector<FactoryWorker *> workers){

    //coment out getch and uncomment timer for it to work for given amount of time
    //for some reason u have to press getch twice for program to close (???)
    //std::this_thread::sleep_for(runTimer);
    getch();

    /*for(int i = 0; i < workers.size(); i++){
        workers.at(i)->setIsRunning(false);
    }*/
}

int main() {

    srand (time(NULL));

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
            subTools.push_back( tools.at(i) );
            subTools.push_back( tools.at(i + 1) );
            subTools.push_back( tools.at(0) );

            Workplace *w = new Workplace(i, subTools);
            workplaces.push_back(w);
        }else{
            subTools.push_back( tools.at(i) );
            subTools.push_back( tools.at(i + 1) );
            subTools.push_back( tools.at(i + 2) );

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


    getch();

    return 0;
}

