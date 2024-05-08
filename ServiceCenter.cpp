#include "ServiceCenter.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std; 

ServiceCenter::ServiceCenter(){
    // Set the time to 1. 0 customers have entered. 
    time = 1; 
    totalCustomers = 0; // so far there are 0 students
}

ServiceCenter::~ServiceCenter(){}

void ServiceCenter::timeTick(){
    // Increase the time, run functions on the office and decrease the time waited at the office. 
    time++;
    cashier.timeTick();
    financial.timeTick();
    registrar.timeTick();
}

void ServiceCenter::getWindowAmount(){
    ifstream file;
    file.open(inputFile);
    file >> numRegistrar;
    file >> numCashier;
    file >> numFinancial;
    file.close();
}

void ServiceCenter::setWindows(){
    // Create the specified amount of windows provided from the input file in getWindowAmount
    registrar.createWindows(numRegistrar);
    cashier.createWindows(numCashier);
    financial.createWindows(numFinancial);
}

void ServiceCenter::retrieveCustomers(){
    ifstream file(inputFile); // Open file provided in cl arg
    int temp;

    for (int i = 0; i < 3; ++i)
        file >> temp; // take in arrivals

    int timeArrived;
    int amtCustomers;
    int currWaitTime;
    char currOffice;
    string arrivals; // keep track of arrival times, to convert to times

    file >> timeArrived;
    file >> amtCustomers;

    bool processing = true; // while we are still in the file 
    while (processing){
        totalCustomers += amtCustomers; // increment the amt of customers we have
        for (int i = 0; i < amtCustomers; ++i){ // for each customer 
            Customer customer;
            customer.setArrivalTime(timeArrived); // set their time 
            // add all three wait times to a queue
            for (int i = 0; i < 3; ++i){
                file >> currWaitTime;
                customer.addWaitTime(currWaitTime);
            }
            // add all offices to a queue
            for (int i = 0; i < 3; ++i){
                file >> currOffice;
                customer.addOffice(currOffice);
            }
            // add each customer to a general line
            enteringCustomers.enqueue(customer);
        }
        file >> arrivals;
        if (file.eof()){ // if its the end of the file 
            processing = false; // no longer processing 
        } else {
            timeArrived = stoi(arrivals); // turns check back into an integer incase the file has not ended
            file >> amtCustomers;
        }
    }
    file.close();

}    

void ServiceCenter::simulate(){
    while (true){

        int lineSize = enteringCustomers.getSize(); // calculate the size of the line. 

        while (enteringCustomers.isEmpty() == false){ // while there are customers still entering, 
            if (enteringCustomers.peek().getArrivalTime() == time){ // if it's the customer's time to enter, enter. 
                if (enteringCustomers.peek().getNextOffice() == 'R'){ // if they're meant to enter registrar, 
                    registrar.enterQueue(enteringCustomers.dequeue()); // queue it in the registrar.
                } 
                else if (enteringCustomers.peek().getNextOffice() == 'F'){ // if they're meant to enter financial center
                    financial.enterQueue(enteringCustomers.dequeue()); // queue it in financial center window 
                } 
                else if (enteringCustomers.peek().getNextOffice() == 'C'){ // and so on for cashier. 
                    cashier.enterQueue(enteringCustomers.dequeue());
                }
            } else {
                break; // if it's not their time to enter, break. 
            }
        }

        // checks for available windows for students in line
        registrar.checkAvailability();
        financial.checkAvailability();
        cashier.checkAvailability();

        // if all the windows are empty, break
        if ((enteringCustomers.isEmpty() == true) && 
            (registrar.checkEmptyWindows() == true) && 
            (financial.checkEmptyWindows() == true) && 
            (cashier.checkEmptyWindows() == true)){ // all are empty
            break;
        }

        // increment time by 1, run function
        timeTick();

        // adds customers that are done with their office to a returning line
        for (int i = 0; i < cashier.numCustomersLeaving(); ++i){
            returningLine.enqueue(cashier.leaveQueue());
        }
        for (int i = 0; i < financial.numCustomersLeaving(); ++i){
            returningLine.enqueue(financial.leaveQueue());
        }
        for (int i = 0; i < registrar.numCustomersLeaving(); ++i){
            returningLine.enqueue(registrar.leaveQueue());
        }

        while (returningLine.isEmpty() == false){ // while there are more customers to return
            // if customer has no offices left they are added to the is done queue
            // if the returning line's office that they need to get to is none
            if (returningLine.peek().officeOrder.isEmpty() == true){ 
                isDone.enqueue(returningLine.dequeue()); // take them out of the returns and put them into exited
            } else { // adds customers to their next office queue
                if (returningLine.peek().getNextOffice() == 'R'){
                    registrar.enterQueue(returningLine.dequeue());
                } else if (returningLine.peek().getNextOffice() == 'F'){
                    financial.enterQueue(returningLine.dequeue());
                } else if (returningLine.peek().getNextOffice() == 'C'){
                    cashier.enterQueue(returningLine.dequeue());
                }
            }
        }
    }
}
 
void ServiceCenter::calcStats(){
    // define all the variables to be calculated.
    double totalRegistrarWait = 0.0;
    double totalFincancialWait = 0.0;
    double totalCashierWait = 0.0;
    int longestRegistrarWait = 0;
    int longestFinancialWait = 0;
    int longestCashierWait = 0;
    int totalWaitOverTenMins = 0;

    // grabs stats from students in the isDone queue
    while(isDone.isEmpty() == false){ // loop through the entire line of customers that have finished the task
        int totalWait = isDone.peek().getRegistrarWaitTime() + 
                        isDone.peek().getFinancialWaitTime() + 
                        isDone.peek().getCashierWaitTime(); // get all their wait times 
        if (totalWait > 10){ // for those who have waited over 10 minutes 
            totalWaitOverTenMins++; // increment the variable 
        }
        // loop through all the values in the queue.
        // if the wait time of the one thats peeked is higher than the variable holding the longest one, 
        if (isDone.peek().getRegistrarWaitTime() > longestRegistrarWait){
            // update the variable 
            longestRegistrarWait = isDone.peek().getRegistrarWaitTime();
        } // same for financial and cashier. 
        if (isDone.peek().getFinancialWaitTime() > longestFinancialWait){
            longestFinancialWait = isDone.peek().getFinancialWaitTime();
        }
        if (isDone.peek().getCashierWaitTime() > longestCashierWait){
            longestCashierWait = isDone.peek().getCashierWaitTime();
        }
        totalRegistrarWait += isDone.peek().getRegistrarWaitTime();
        totalFincancialWait += isDone.peek().getFinancialWaitTime();
        totalCashierWait += isDone.peek().getCashierWaitTime();
        // dequeue it. 
        isDone.dequeue();
    }

    // after everything is calculated, print out all the total calculations 
    cout << "Cashier's Office:" << endl;
    cout << "Mean student wait time: " << totalCashierWait/totalCustomers << " tick(s) " << endl;
    cout << "Mean window idle time: " << cashier.calcAvgIdle()<< " tick(s) " << endl;
    cout << "Longest student wait time: " << longestCashierWait << " tick(s) " << endl;
    cout << "Longest window idle time: " << cashier.calcLongestIdle() << " tick(s) " << endl;

    cout << "\nFinancial Aid Office: " << endl;
    cout << "Mean student wait time: " << totalFincancialWait/totalCustomers << " tick(s) " << endl;
    cout << "Mean window idle time: " << financial.calcAvgIdle() << " tick(s) " << endl;
    cout << "Longest student wait time: " << longestFinancialWait << " tick(s) " << endl;
    cout << "Longest window idle time: " <<  financial.calcLongestIdle() << " tick(s) " << endl;

    cout << "\nRegistrar's Office: " << endl;
    cout << "Mean student wait time: " << totalRegistrarWait/totalCustomers << " tick(s) " << endl;
    cout << "Mean window idle time: " << registrar.calcAvgIdle() << " tick(s) " << endl;
    cout << "Longest student wait time: " << longestRegistrarWait << " tick(s) " << endl;
    cout << "Longest window idle time: " << registrar.calcLongestIdle() << " tick(s) " << endl;

    cout << "\nNumber of students waiting over 10 minutes across all offices: " << totalWaitOverTenMins << endl;
    cout << "Number of windows idle for over 5 minutes across all offices: " << (registrar.calcFiveWindowIdle() + financial.calcFiveWindowIdle() + cashier.calcFiveWindowIdle()) << endl;
}

void ServiceCenter::setFile(string inputF){
    inputFile = inputF;
}