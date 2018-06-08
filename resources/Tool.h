//
// Created by Admin on 08.06.2018.
//

#ifndef FACTORY_THREAD_SIMULATION_TOOL_H
#define FACTORY_THREAD_SIMULATION_TOOL_H

#include <mutex>

class Tool {
public:
    Tool(int id);

    int getId() const;

    void setId(int id);

    bool isIsBeingUsed() const;

    void setIsBeingUsed(bool isBeingUsed);

    const std::string &getStatus() const;

    void setStatus(const std::string &status);

    std::mutex m;

private:
    int id;

    bool isBeingUsed;

    std::string status;



};


#endif //FACTORY_THREAD_SIMULATION_TOOL_H
