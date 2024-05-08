#include "Customer.h"

Customer::Customer(){
    // Set all to 0, as none have been waited for yet.
    registrarWaitTime = 0; 
    financialWaitTime = 0; 
    cashierWaitTime = 0;
}

Customer::~Customer(){}

void Customer::addOffice(char office){
    officeOrder.enqueue(office);
}

void Customer::addWaitTime(int time){
    waitTimes.enqueue(time);
}

void Customer::dequeueOffice(){
    officeOrder.dequeue();
}


void Customer::incRegistrarWT(){
    registrarWaitTime++;
}

void Customer::incFinancialWT(){
    financialWaitTime++;
}

void Customer::incCashierWT(){
    cashierWaitTime++;
}

// GETTTERS AND SETTERS

void Customer::setArrivalTime(int time){
    arrivalTime = time;
}

int Customer::getArrivalTime(){
    return arrivalTime;
}

char Customer::getNextOffice(){
    return officeOrder.peek();
}

int Customer::getRegistrarWaitTime(){
    return registrarWaitTime;
}

int Customer::getFinancialWaitTime(){
    return financialWaitTime;
}

int Customer::getCashierWaitTime(){
    return cashierWaitTime;
}

int Customer::getNextWaitTime(){
    return waitTimes.peek();
}

int Customer::removeFollowingWT(){
    return waitTimes.dequeue();
}