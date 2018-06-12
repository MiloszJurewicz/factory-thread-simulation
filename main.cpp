#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <curses.h>
#include "resources/Tool.h"
#include "gui/DrawGui.h"
#include "threads/Courier.h"
#include "threads/Orders.h"

using namespace std;

const int NUMOFWORKERS = 4;
const int NUMOFWORKPLACES = 4;
const int NUMOFTOOLS = NUMOFWORKPLACES * 2;
const int NUMOFCOURIERS = 2;
const int NUMOFORDERS = 1; // must  be 1 not fully thread safe and printing not implemented
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

    //init gui and pseudo random
    srand (time(NULL));
    initGui();

    //Resources
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

    //Stockpile
    ProductStockpille *productStockpille = new ProductStockpille();

    //Creating mainStorage
    PartsStorage *ps = new PartsStorage();

    //subvector of workplaces, each curier gets half of workplaces
    vector<Workplace*> subWorkplacesEven;
    vector<Workplace*> subWorkplaceOdd;

    for(int i = 0; i < workplaces.size();i++){
        if(workplaces.at(i)->getId() % 2 == 0){
            subWorkplacesEven.push_back(workplaces.at(i));
        }else{
            subWorkplaceOdd.push_back(workplaces.at(i));
        }
    }

    //threads
    vector<thread> tasks(NUMOFWORKERS);
    vector<thread> ordersList(NUMOFORDERS);
    vector<thread> couries(NUMOFCOURIERS);


    //threads of workers each gets all workplaces
    for(int i = 0; i < NUMOFWORKERS; i++){
        FactoryWorker *f = new FactoryWorker(i);

        tasks[i] = (thread(&FactoryWorker::routine,
                           f,
                           ref(workplaces),
                           ref(_muGUI),
                           ref(productStockpille))
            );
    }

    //orderds
    for(int i = 0; i < NUMOFORDERS; i++){
        Orders *o = new Orders();

        ordersList[i] = (thread(&Orders::routine,
                                 o,
                                 ref(_muGUI),
                                 ref(productStockpille))
        );

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

    //end condition(getch();)
    getch();

    //joining everything
    for(int i = 0; i < tasks.size();i++){
        tasks.at(i).join();
    }

    for(int i = 0; i < couries.size();i++){
        couries.at(i).join();
    }

    for(int i; i < ordersList.size(); i++){
        ordersList.at(i).join();
    }




    curs_set(FALSE);
    endwin();

    return 0;
}

