#ifndef __RECORD_AGENT__H
#define __RECORD_AGENT__H 

#include "enviro.h"
#include <string> 

using namespace enviro;

//A class that records the number of coins collected.
class recordController : public Process, public AgentInterface {

    public:
    //Defines a controller for the record agent
    recordController() : Process(), AgentInterface() {}

    //Initialization function to watch for when coins are collected and when it is time to restart the game. When coins are
    //collected, the count number increments by 1. When it is time to restart the game, the count number resets to 0.
    void init() {
        watch("coin collected", [&](Event &e) {
            count += 1;
        });
        watch("restart game", [&](Event &e) {
            count = 0;
        });
    }
    void start() {}

    //The update function displays the number of coins collected on the screen to notify players of their progress.
    void update() {
        
        label("Coin Collected: " + std::to_string(count) , 0, 0);
        
    }
    void stop() {}
    //Variable to store the number of coins collected
    int count = 0;
};

//The record class is defined where the physics of the agent and cooridination of various activities with the manager are done.
//Also, the class acts as a container for processes.
class record : public Agent {
    public:
    record(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    recordController c;
};

DECLARE_INTERFACE(record)

#endif