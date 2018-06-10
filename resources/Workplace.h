//
// Created by jupiter on 10.06.18.
//

#ifndef FACTORY_THREAD_SIMULATION_WORKPLACE_H
#define FACTORY_THREAD_SIMULATION_WORKPLACE_H

#include <iostream>

class Workplace {
public:

    Workplace(int id);

    int getId() const;

    void setId(int id);

    bool isIsTaken() const;

    void setIsTaken(bool isTaken);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    int getParts() const;

    void setParts(int parts);

private:
    int id;

    bool isTaken;

    std::string status;

    int parts;

};


#endif //FACTORY_THREAD_SIMULATION_WORKPLACE_H
