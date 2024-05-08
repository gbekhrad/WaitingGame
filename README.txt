Name: Gabriella Bekhrad
ID: 2417841
Class/Section: CPSC 350-01
PA4 - The Waiting Game

Overview:
Simulation of Student Services Center (SSC) Traffic Flow
The Problem:
- The SSC houses offices like the registrar, cashier, and financial aid, and experiences fluctuating traffic throughout the day.
- The challenge is to optimize the number of service windows open at each office to minimize wait times while avoiding unnecessary idle time for staff.
Assignment Task:
- The assignment involves building a simulation program to address issues faced by the Student Services Center (SSC), including long student wait times and inefficient window usage.
- The program will calculate metrics on student wait times and window idle times based on a specific traffic flow of students through the SSC.
Implementation:
1. Develops a generic doubly-linked list data structure and a generic queue data structure from scratch, without using existing libraries.
2. Uses the queue implementation to simulate the traffic flow of students through the SSC.
3. Input, provided via a text file, specifies the number of windows open at each office, arrival times of students, and their service requirements.
Input Includes:
  - Number of windows open at the registrar, cashier, and financial aid office.
  - Arrival times of students and their service requirements (time needed at each office and order of visit).
The simulation will start at time 1, and run until all student requests have been addressed, meaning the queue at each office is 
empty and no more students are going to arrive.
At the end of the simulation, your program will display (on standard out) the following (labeled) metrics:
1. The mean student wait time for each office.
2. The longest student wait time for each office.
3. The number of students waiting over 10 minutes total across all offices.
4. The mean window idle time for each office
5. The longest window idle time for each office
6. Number of windows idle for over 5 minutes across all offices.

Source Files:
- ListNode.h 
- ListQueue.h
- DblList.h
- Window.h
- Window.cpp
- Office.h
- Office.cpp 
- ServiceCenter.h
- ServiceCenter.cpp
- Customer.cpp
- Customer.h 

Instructions to compile/run:
- g++ *.cpp
- ./a.out inputFileName.txt