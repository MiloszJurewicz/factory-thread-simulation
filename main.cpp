#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <curses.h>
#include "resources/Tool.h"
#include "gui/DrawGui.h"
#include "threads/Courier.h"

using namespace std;

const int NUMOFWORKERS = 4;
const int NUMOFWORKPLACES = 4;
const int NUMOFTOOLS = NUMOFWORKPLACES * 2;
const int NUMOFCOURIERS = 2;
const int MILISECONDS = 250;
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

    //creating subvector of tools for each workplace
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



    //Creating mainStorage
    PartsStorage *ps = new PartsStorage();

    vector<thread> tasks(NUMOFWORKERS);
    //threads of workers each gets all workplaces
    for(int i = 0; i < NUMOFWORKERS; i++){
        FactoryWorker *f = new FactoryWorker(i);

        tasks[i] = (thread(&FactoryWorker::routine,
                           f,
                           ref(workplaces),
                           ref(_muGUI))
            );
    }

    vector<thread> couries(NUMOFCOURIERS);
    vector<Workplace*> subWorkplacesEven;
    vector<Workplace*> subWorkplaceOdd;

    //subvector of workplaces, each curier gets half of workplaces
    for(int i = 0; i < workplaces.size();i++){
        if(workplaces.at(i)->getId() % 2 == 0){
            subWorkplacesEven.push_back(workplaces.at(i));
        }else{
            subWorkplaceOdd.push_back(workplaces.at(i));
        }
    }


    //creating courier threads
    for(int i = 0; i < NUMOFCOURIERS; i++){
        Courier *c = new Courier(i);

        if(i % 2 == 0){
            couries[i] = (thread(&Courier::routine,
                                 c,
                                 ref(subWorkplacesEven),
                                 ref(_muGUI),
                                 ref(ps))
            );
        }else{
            couries[i] = (thread(&Courier::routine,
                                 c,
                                 ref(subWorkplaceOdd),
                                 ref(_muGUI),
                                 ref(ps))
            );
        }
    }

    for(int i = 0; i < tasks.size();i++){
        tasks.at(i).join();
    }

    for(int i = 0; i < couries.size();i++){
        couries.at(i).join();
    }


    getch();

    curs_set(FALSE);
    endwin();

    return 0;
}

