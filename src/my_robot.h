#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <thread>
#include <chrono>

using namespace enviro;

//A class that controls the pacman shaped robot in the game.
class MyRobotController : public Process, public AgentInterface {

    public:
    MyRobotController() : Process(), AgentInterface() {}
    
    //Initialization of the robot controller. This functions watches user input from the "w", "a", "s", "d" keys of the keyboard.
    //Also, it listens for collisions with zombie, speedup, and slowdown agents. When a collision with a zombie agent has occurred,
    //it emits a "restart game" event to signal all zombies to teleport to their initial location to restart the game. When a collision
    //with a speedup agent occurs, it increases the speed of the robot. When a collision with the slowdown agent have occured, it will
    //reduce the speed of the robot.
    void init() {

        watch("keydown", [&](Event &e) {
        auto k = e.value()["key"].get<std::string>();
        if ( k == "w" ) {
                f = magnitude;
        } else if ( k == "s" ) {
                f = -magnitude;
        } else if ( k == "a" ) {
                tau = -magnitude_t;
        } else if ( k == "d" ) {
                tau = magnitude_t;
        }
        });
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "w" || k == "s" ) {
                    f = 0;
            } else if ( k == "a" ) {
                    tau = 0;
            } else if ( k == "d" ) {
                    tau = 0;
            }
        });

        notice_collisions_with("zombie", [&](Event &e) {
            teleport(0,0,0);
            emit(Event("restart game"));
            magnitude = 200;
        });
        notice_collisions_with("speedup", [&](Event &e) {
            magnitude += 100;
        });
        notice_collisions_with("slowdown", [&](Event &e) {
            magnitude -= 50;
        });

    }
    void start() {}

    //Update function to apply the speed and rotation values previously specified whenever "w", "a", "s", "d" key on the
    //keyboard is pressed.
    void update() {
        apply_force(f,tau);
    }
    void stop() {}
    //f stores the speed to move and tau stores the magnitude and direction of rotation.
    double f, tau;
    //magnitude stores the magnitude of velocity to move.
    double magnitude = 200;
    //magnitude_t stores the magnitude of rotational velocity.
    double magnitude_t = 200;

};

//The MyRobot class is defined where the physics of the agent and cooridination of various activities with the manager are done.
//Also, the class acts as a container for processes.
class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyRobotController c;
};

DECLARE_INTERFACE(MyRobot)

#endif