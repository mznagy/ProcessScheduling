# Process Scheduling Simulation

This project is a simple simulation of process scheduling in an operating system. It uses three different scheduling algorithms: Round Robin with quantum 8 (rr8), Round Robin with quantum 16 (rr16), and First-Come-First-Serve (fcfs).

## Description

The program creates processes with random burst times and adds them to the rr8 queue. The scheduler then processes these tasks based on the scheduling algorithm and the current state of the queues. If a process is not finished within the quantum time, it is moved to the next queue. The process continues until all processes are finished.

Each process is represented by a struct that contains an ID and a burst time. The queues are implemented as circular arrays with a maximum size of 100.

## Installation

To install and run this project, you will need a C compiler such as gcc. You can clone this repository and compile the main.c file.

```bash
git clone https://github.com/username/project.git
cd project
gcc main.c -o main
./main
