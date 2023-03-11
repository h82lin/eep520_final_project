#ifndef __ZOMBIE_AGENT__H
#define __ZOMBIE_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"


namespace
{

    using namespace enviro;

    //A class that represents the state of "MovingForward". This state basically tells the zombie agent to move forward or backwards
    class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}

        //The during function specifies and enables the straight line velocity of the zombie agent. It also implements mechanism to prevent the zombie from getting
        //stuck. It does so by checking whether an object is within 40 units of distance in front. If it is, the functio will emit an
        //event to signal a change of state so that the zombie can rotate to another direction. 
        void during()
        {
            track_velocity(6, 0);
            if (sensor_value(0) < 40)
            {
                emit(Event(tick_name));
            }

        }
        void exit(const Event &e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    //A class that represents the state of "Rotating". This state basically tells the zombie rotate its direction.
    class Rotating : public State, public AgentInterface
    {
    public:
        //The entry function defines the rate and directionthat the zombie will rotate.
        void entry(const Event &e) { rate = rand() % 2 == 0 ? 2 : -2; }

        //The during function specifies and enables the rotation of the zombie agent. It also implements mechanism to prevent the zombie from rotating too
        //much. It does so by stopping rotation when an object is over 140 units from an object in front. The function will emit an event when this happens
        //to signal a change in state. This change of state will change the state so that the zombie can move forward in a particular direction.
        void during()
        {
            track_velocity(0, rate);
            if (sensor_value(0) > 140)
            {
                emit(Event(tick_name));
            }
        }
        void exit(const Event &e) {}

        //Stores rate of which the zombie will rotate.
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    //A controller that acts as a statemachine which helps the zombie agent transition between the "MovingForward" and "Rotating" states.
    class ZombieController : public StateMachine, public AgentInterface
    {

    public:
        //Sets the intial state of the state maachine, define transitions
        ZombieController() : StateMachine()
        {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand() % 1000); 
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);
        }
        //Update function damps movement of zombie agent so that the agent can move in a more natural manner and prevent zombies from sticking
        //to each other. The emit event is used to cause the state to change. This emit event is true only about 5% of the time, so only occasiinally ticks. 
        //The last line in the update function ensures that the superclass, StateMachine, has a chance to run its update method as well.
        void update()
        {
            damp_movement();
            if (rand() % 100 <= 5)
            {
                emit(Event("tick"));
            }
            StateMachine::update();
            
        }

        //Defining an object of MovingForward class
        MovingForward moving_forward;
        //Defining an object of rotating class
        Rotating rotating;
        //Variable used to store the name of each transition.
        std::string tick_name;
        
    };

    //Class used take care of when the robot collides with a zombie. When this occurs, the game starts over.
    class ZombieReset: public Process, public AgentInterface {
    public:
    ZombieReset() : Process(), AgentInterface() {}

    //Initialization function used to store the initial position of the robot and set the position of the robot to its initial position
    //when the game restarts(when the robot collides with a zombie).
    void init() {
        x = position().x;
        y = position().y;
        t = angle();

        watch("restart game", [&](Event& e)  {
            teleport(x, y ,t);
        });
    }
    void start() {}
    void update() {}
    void stop() {}
    double x, y, t;
};

    //The Zombie class is defined where the physics of the agent and cooridination of various activities with the manager are done.
    //Also, the class acts as a container for processes. Note that the ZombieReset process zr is added to tohis class in order to
    //takes care of when the game restarts.
    class Zombie : public Agent
    {

    public:
        Zombie(json spec, World &world) : Agent(spec, world)
        {
            add_process(wc);
            add_process(zr);
        }

        ZombieController wc;
        ZombieReset zr;
    };

    DECLARE_INTERFACE(Zombie);

}

#endif