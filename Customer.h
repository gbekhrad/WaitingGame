#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "ListQueue.h"
using namespace std; 
/** 
 * @brief Represents a student visiting the SSC.
 * Stores information about the student, such as the time needed at each office and the order of visits.
 * Interacts with the ServiceCenter and Office objects to join queues and receive service.
*/
class Customer {
    public:
        /**
         * @brief Default Constructor
        */
        Customer();

        /**
         * @brief Default Destructor
        */
        ~Customer();

        /**
         * @brief adds an office to queue
         * @param office to be added to the queue
        */
        void addOffice(char office);

        /**
         * @brief removes the next office from queue
        */
        void dequeueOffice();

        /**
         * @brief adds wait time to queue
         * @param time the amt of time to be added 
        */
        void addWaitTime(int time);

        /**
         * @brief increment the wait time at the registrar
        */
        void incRegistrarWT();

        /**
         * @brief increment the wait time at the financial aid office
        */
        void incFinancialWT();

        /**
         * @brief increment the wait time at the cashier
        */
        void incCashierWT();

        // Getters and Setters. 
        char getNextOffice();
        void setArrivalTime(int time);
        int getArrivalTime();
        int getRegistrarWaitTime();
        int getFinancialWaitTime();
        int getCashierWaitTime();
        int getNextWaitTime(); // gets the next wait time from queue
        int removeFollowingWT(); // gets the wait time and removes it from queue
        
        ListQueue<char> officeOrder; // a queue indicating the order in which the customer visits certain offices. 
        ListQueue<int> waitTimes; // queue of waittimes to be passed in by input file. 


    private:
        int arrivalTime; // indicating customer's time arrived
        int registrarWaitTime; // indicating the amount of time the customer will wait at the registrar
        int financialWaitTime; // indicating the amount of time the customer will wait at the financial aid office
        int cashierWaitTime; // indicating the amount of time the customer will wait at the cashier

        int timeInLine; // time customer entered queue
        int timeService; // length of time needed for service
        int timeWaiting; // time waiting for service
};

#endif 



