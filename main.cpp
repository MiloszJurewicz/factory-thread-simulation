#include <iostream>
#include <thread>
#include <ncurses.h>
#include <algorithm>
#include <mutex>
#include "resources/Tool.h"
#include "resources/Workplace.h"
#include "gui/DrawGui.h"

using std::thread;
using std::vector;
using std::ref;
using std::mutex;

const static int NUMOFWORKERS = 4;
const static int NUMOFWORKPLACES = 4;
const static int NUMOFTOOLS = NUMOFWORKERS * 2;
mutex _muGUI;

void stopThreadsTimer(vector<FactoryWorker *> workers){

    //coment out getch and uncomment timer for it to work for given amount of time
    //for some reason u have to press getch twice for program to close (???)
    //std::this_thread::sleep_for(runTimer);
    getch();

    for(int i = 0; i < workers.size(); i++){
        workers.at(i)->setIsRunning(false);
    }
}

int main() {

    initGui();

    //creating proper amount of tools
    vector<Tool*>tools(NUMOFWORKERS);
    for(int i = 0 ; i < NUMOFTOOLS; i++){
        auto *t1 = new Tool(i);
        tools.push_back(t1);
    }

    //creating workplaces
    for(int i = 0; i < NUMOFWORKPLACES; i++){
        auto *w = new Workplace(i);
    }



    /*vector<thread> tasks(NUMOFWORKERS);
    vector<FactoryWorker*> workers;

    for(int i = 0; i < NUMOFWORKERS; i++) {
        FactoryWorker *f = new FactoryWorker(i);
        workers.push_back(f);

        tasks[i] = (thread(&FactoryWorker::routine,
                           f,
                           ref(_muGUI))
        );
    }

    for(int i = 0; i < tasks.size(); i++){
        stopThreadsTimer(workers);
        tasks.at(i).join();
    }*/

    getch();

    curs_set(FALSE);
    endwin();


    return 0;
}

