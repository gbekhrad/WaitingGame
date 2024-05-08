#include "Window.h"


Window::Window(){
    // Create a window. A window contains a queue. 
    occupied = false; 
    timeIdle = 0;
}

Window::~Window(){}

void Window::processTask(Customer ctmr){
    occupied = true; // set to true as a customer is being helped
    currCustomer = ctmr;
    currCustomer.dequeueOffice(); 
    timeWaited = currCustomer.removeFollowingWT(); 
}

// reset a window upom departure of customer 
Customer Window::leaveWindow(){
    occupied = false; // the window is no longer occupied 
    return currCustomer;
}

bool Window::isOccupied(){
    return occupied;
}


void Window::addIdleTime(){
    timeIdle++;
}

void Window::clockTick(){
    timeWaited--;
}

// Getters and Setters begins below

int Window::getTimeIdle(){
    return timeIdle;
}