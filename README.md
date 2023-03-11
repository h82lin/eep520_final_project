  

# Robot vs Zombie game

  

## Project Goal:

To create a video game in which a robot can be controlled by a player. The player's objective is to collect as most gold coins as possible. There will also be numerous zombies that will end the game if it touches the robot. Performance enhancing items are available for robots to collect in order to increase and decrease its speed. Lastly, this project is also for me to familiarize myself with developing programs in Enviro and get a general understanding of what developing programs in embedded systems are like.

  
  

## Key challenges:

Developing a project using Enviro can present several challenges, including:



**Understanding the Enviro architecture**: Enviro has a unique architecture that can be challenging to understand at first. It is based on a decentralized system of agents that interact with each other using message passing. To address this challenge, it is important to study the Enviro documentation and examples carefully and understand how agents, behaviors, and messages work together.

  

**Lacking full documentation**: Enviro lacks full documentation. Many of the functions are not documented completely, thus it often resulted in trail and error in order to implement functions.

  

**Implementing agent behaviors**: Implementing agent behaviors that interact with the environment and other agents can be challenging, especially if the behavior is complex or requires coordination with other agents. To address this challenge, it is important to break down the behavior into smaller, simpler components and test each component independently before integrating them into the final behavior.

  

**Debugging**: Debugging can be challenging in Enviro because of the decentralized nature of the system. It can be difficult to identify which agent or behavior is causing a problem. To address this challenge, it is important to use debugging tools such as print statements or the Enviro debugger to narrow down the problem.

  

Overall, developing a project using Enviro requires careful planning, testing, and debugging. However, with the right approach and mindset, these challenges can be overcome and a successful project can be created.

  

## How to Install and Run the Code

  

To start a Docker container with ENVIRO pre-loaded into it, do:

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.61  bash

```

Note: There are different version of the klavins/enviro image, so it is possible that only one image would run on your computer. To know which image is suitable for your computer you may need to run all the versions once. Here are all the versions of the image:

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.6  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.5  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.4  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.3  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:v1.2  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:1.1  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:1.01  bash

```

```sh

docker run -p80:80  -p8765:8765  -v  $PWD:/source  -it klavins/enviro:alpha bash

```
The above commands do the following:
- The `-p80:80 option maps port 80 from the Docker container to ports on your host computer. This should allow you to go to

  

- http://localhost with your web browser and see the ENVIRO client. It should say "Error: Failed to fetch. Is the server running?" at this point.

  

- The -p8765:8765 option allows the ENVIRO client to communicate with the enviro server (not yet running) via a WebSocket.

 &nbsp;

  

Git clone this repository:

```sh

git clone https://github.com/h82lin/eep520_final_project.git

```

In the command prompt, navigate to the root of the eep520_final_project directory and make the project:

```sh

make

```

Then execute the command:

```sh

enviro

``````

This should allow you to go to http://localhost and use the application.

  
  

## How to use the Project

- The green pacman-like character is named "Robot". This is the character that the player can control

  

- Robot can be controlled using the "w", "a", "s", and "d" keys on the keyboard. The keys direct Robot to move forward, rotate left, move backward, rotate right respectively.

  

- There are always 2 gold oval coins located at random places on the map. The objective is to collect as many gold coins as possible.

  

- The number of gold coins collected is recorded on the top left of the screen.

  

- There are 2 performance enhancing balls availalbe for Robot to collect. The light-blue ball speeds up Robot and the black ball slows down Robot.

  

- The brown square-shaped blocks are zombies. If Robot collides with a zombie, the game starts over and the number of coins collected resets to 0.

  
  

## Sources of information

  

https://github.com/klavinslab/enviro

  

https://github.com/sosper30/eep520/blob/main/week7/Lecture7_README.md

  
  

https://github.com/sosper30/eep520/blob/main/week9/Lecture9_README.md#the-transitions

  

https://github.com/sosper30/eep520/blob/main/week10/Lecture10_README.md

  

https://github.com/sosper30/eep520/blob/main/week10/README%202.md