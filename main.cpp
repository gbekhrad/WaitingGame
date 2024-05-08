

// main.cpp to run the program takes the input specification file as a command line argument.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#include "ServiceCenter.h"
/*
Input will be in the form of a command line argument that specifies the location of a text file. 
The text file will define at what times students arrive, and what offices they will visit and in what order. 
It will have the following format. 

The following lines will be the amount of time each student needs at the registrar, cashier, and financial aid office, 
respectively, as well as the order they visit them. This is followed by the next clock tick, number of students, etc. 
*/

int main(int argc, char **argv){
    ServiceCenter myCenter;
    myCenter.setFile(argv[1]);
    myCenter.getWindowAmount();
    myCenter.setWindows();
    myCenter.retrieveCustomers();
    myCenter.simulate();
    myCenter.calcStats();
    return 0;
}