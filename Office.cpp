#include "Office.h"

Office::Office(){

}

Office::~Office(){
    delete[] windowArr; 
}

void Office::createWindows(int numWindows){
    windowCount = numWindows; // set num windows
    windowArr = new Window[windowCount]; // set windowArr/create an array of windows for each office
}

void Office::enterQueue(Customer ctmr){
    // if wait time is >0, add the customer to the queue for the office 
    if (ctmr.getNextWaitTime() == 0){ // if the customer has waited/doesn't have time to wait
        ctmr.removeFollowingWT(); // dequeue the wait time 
        ctmr.dequeueOffice(); // dequeue the office 
        cExited.enqueue(ctmr); // queue the customer to the queue of exited Customers
    } else { // They have time to wait
        cQueue.enqueue(ctmr);
    }
}

void Office::checkAvailability(){
    // checks if window is occupied
    for (int i = 0; i < windowCount; ++i){ // for each window 
        // if theres no queue of customers and the window at index i is vacant
        if ((cQueue.isEmpty() == false) && (windowArr[i].isOccupied() == false)){
            // dequeue and process task 
            windowArr[i].processTask(cQueue.dequeue());
        }
    }
    // if customers are waiting and all windows are full their wait time is incremented
    if (cQueue.isEmpty() == false){
        for (int i = 0; i < cQueue.getSize(); i++){
            current = cQueue.dequeue();
            // note officeOrder has the list of offices the customer will visit in order
            // they're stored 
            // get the next office
            if (current.getNextOffice() == 'R'){ // if the next office is regisrar
                current.incRegistrarWT(); // increment the registrar wait time of the current object
                cQueue.enqueue(current); // add the customer to the queue
            }else if(current.getNextOffice() == 'F'){ // if the next office is finaid
                current.incFinancialWT(); // increment finaid wait time 
                cQueue.enqueue(current); // add the customer to the queue
            }else if(current.getNextOffice() == 'C'){ // if the next office is cashier
                current.incCashierWT(); // increment cashier wait time 
                cQueue.enqueue(current); // add the customer to the queue
            }
        }
    }
}

bool Office::checkEmptyWindows(){
    // checks if all windows are empty
    bool status = true;
    for (int i = 0; i < windowCount; ++i){ // for each window
        if (windowArr[i].isOccupied() == true){ // if any are occupied 
            status = false;
        }
    } 
    return status;
}

void Office::timeTick(){
    for (int i = 0; i < windowCount; ++i){
        if (windowArr[i].isOccupied() == true){ // if its occupied 
            windowArr[i].clockTick(); // timewaited--
            // customer leaves window when their time is done
            if (windowArr[i].timeWaited <= 0){
                cExited.enqueue(windowArr[i].leaveWindow());
            }
        // if the window is not occupied its idle time increases
        } else {
            windowArr[i].addIdleTime();
        }
    }
}

Customer Office::leaveQueue(){
    return cExited.dequeue(); // sends customer back to service center
}

int Office::numCustomersLeaving(){
    return cExited.getSize(); // gets amount of customers ready to leave
}

double Office::calcAvgIdle(){
    // gets average idle time for all windows in the office
    double avgIdle = 0.0;
    for (int i = 0; i < windowCount; ++i){
        avgIdle += windowArr[i].getTimeIdle();
    }
    return avgIdle/windowCount;
}

int Office::calcLongestIdle(){
    int longestIdle = 0; 
    for (int i = 0; i < windowCount; ++i){ // for each window
        if (windowArr[i].getTimeIdle() > longestIdle){ // if the time we are parsing is greater than the existing longest time 
            longestIdle = windowArr[i].getTimeIdle(); // update that variable 
        }
    }
    return longestIdle;
}

int Office::calcFiveWindowIdle(){
    int windowsIdle = 0;
    for (int i = 0; i < windowCount; ++i){ // for each window
        if (windowArr[i].getTimeIdle() > 5){ // if idle time is >5, 
            windowsIdle++; // add it the the variable indicating that a window was idle for >5 minutes
        }
    }
    return windowsIdle;
}