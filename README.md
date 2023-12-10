# OS-Project
The project aims to provide a flexible and extensible simulation tool for studying and comparing the performance of multitasking scheduling algorithms. The main objectives are as follows:

* Generate random tasks with diverse characteristics (execution time, priorities, arrival times).
* Implement multiple multitasking scheduling algorithms.
* Allow for the configuration of simulation parameters, including the number of tasks, arrival intervals, scheduling parameters, etc.
* Collect data on task execution and algorithm performance metrics.
* Visualize the simulation results in the form of graphs and statistics.

# How to use

## Installation
 First we need to install nodejs using the following commands
 ```bash
   sudo apt update
   sudo apt install nodejs
   node -v
```

Next we need to install gcc using the following commands
```bash
   sudo apt update
   npm install gcc
```

If it is already installed, we can check the version by running this command
```bash
   gcc --version
```

Finally we will install git to access to our scheduler's repository from github
```bach
   sudo apt update
   sudo apt install git
```

After installing the required tools, we need to clone our scheduler's repository in a directory we choose
```bash
   cd my-directory
   git clone https://github.com/moatazkhabbouchi/OS-Project.git
```





## Execution
The repository is now cloned into your machine. Type the commands below to compile the code
```bach
   cd OS-Project
   make
```

Now that our scheduler is compiled, type the command **./test** to run the program

![403632051_345722961565790_6881381553542873231_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/d69e27da-7860-4acb-a579-5b6203499615)

We will be asked to play a simple game before we access to scheduler. We chose not and pass to the next steps

![393914961_3720052864932859_7699875794403860497_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/88f0c5c3-4986-40ad-9b05-147ef4c4ca84)

Then we type the number of processes to generate, the intervals of **Arrival Time**, **Execution Time** and **Priority**.
The processes file is generated successfully.

![403634930_354066917214484_9054304723149671756_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/a179e08d-274a-4ea8-b1bb-89fa2144d7b9)

![393117255_889278342879414_2375724090981075116_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/ae275156-b1e6-44f7-af1f-b4026d72ad45)

We will choose for this example the Round Robin algorithm from the menu by typing **2**.
Execution details of each process will be shown in addition of metrics like **Turn Around** and **Waiting** times. 

![393104376_889868526076710_3467014497274294809_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/b9eee354-1708-4bd3-9086-e19278b9b8d6)

A link will appear at the end that will show the Gant Diagram Interface on the navigator.

![393087789_1041434543843038_8991605136139246357_n](https://github.com/moatazkhabbouchi/OS-Project/assets/73138833/3cc68d5b-4d9c-4a1a-9afd-0ac4732ac61a)


