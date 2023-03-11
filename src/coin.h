#ifndef __COIN_AGENT__H
#define __COIN_AGENT__H 

#include "enviro.h"
#include <random>

using namespace enviro;

//A class that controls the coin agent in the game.
class coinController : public Process, public AgentInterface {

    public:
    //Define a controller for the coin agent
    coinController() : Process(), AgentInterface() {}

    //The initialization function of the coin controller. This function detects whether the coin has colided with MyRobot, if yes, send an emit
    //to so that the record.h file can watch and record the number of coins collected.
    void init() {
        notice_collisions_with("MyRobot", [&](Event &e) {        
            emit(Event("coin collected"));
            collided = true;
        });

    }
    void start() {}
    //The update method removes the coin if the coin has been collected by the robot. Then, it assigns a random
    //location for the coin to spawn again. Checks are put into place so that coins do not spawn within static blocks.
    void update() {
        if(collided == true){
            remove_agent(id());
            collided = false;
            const int range_from_x  = -330;
            const int range_to_x    = 330;
            const int range_from_y  = -220;
            const int range_to_y    = 220;

            std::random_device rand_dev;
            std::mt19937  generator(rand_dev());
            std::uniform_int_distribution<int>  distr_x(range_from_x, range_to_x);
            std::uniform_int_distribution<int>  distr_y(range_from_y, range_to_y);
            int x = distr_x(generator);
            int y = distr_y(generator);
            while((x <= -70 && x >= -100 && y >= 0 && y <= 80) || 
                  (x >= 70 && x <= 100 && y >= -80 && y <= 0) ||
                  (x >= 320 && x <= 340 && y >= -40 && y <= 40) ||
                  (x >= -340 && x <= -320 && y >= -40 && y <= 40) ||
                  (x >= -250 && x <= 250 && y <= -140 && y >= -150) ||
                  (x >= -250 && x <= 250 && y <= 150 && y >= 140)){
                x = distr_x(generator);
                y = distr_y(generator);
            }
            

            add_agent("coin", x, y, 0, {{"fill", "yellow"}});
            
        }
    }
    void stop() {}
    //Used to record whether robots have collided with a coin.
    bool collided = false;
};

//The coin class is defined where the physics of the agent and cooridination of various activities with the manager are done.
//Also, the class acts as a container for processes.
class coin : public Agent {
    public:
    coin(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    coinController c;
};

DECLARE_INTERFACE(coin)

#endif