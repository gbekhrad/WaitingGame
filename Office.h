#ifndef OFFICE_H
#define OFFICE_H

#include <iostream>
#include <fstream>
#include "Window.h"
using namespace std;

/**
 * @brief Represents an individual office within the SSC. 
 * Contains instances of Window objects representing service windows within the office.
 * Manages the queue of students waiting to be served at the office.
 * Tracks metrics such as student wait times and window idle times specific to the office.
*/
class Office {
    public: 
        /**
         * @brief Default Constructor
        */
        Office();

        /** 
         * @brief Default Destructor for an Office object. 
         * Delete array of windows
         */
        ~Office();
        
        /** 
         * @brief Function to create windows based on the specified amount given from input file. 
         * @param numWindows the number of windows to be created 
         */
        void createWindows(int numWindows);

        /** 
         * @brief Funtion allowing a customer to enter the queue for the office. 
         * @param ctmr the Customer entering the queue 
         */
        void enterQueue(Customer ctmr);

        /** 
         * @brief Function to check if a single window is empty.
         */
        void checkAvailability();
        
    
        /** 
         * @brief A function that returns a boolean to check if all of the windows are empty. 
         * @return boolean indicating true if empty, false if occupied. 
         */
        bool checkEmptyWindows();

        /**
         * @brief Function incrementng the clock based on multiple conditions. 
         * Function is called recursively to increment time if conditions are met. 
        */
        void timeTick();

        /**
         * @brief Function indicating that a customer has left the queue
         * @return Customer object that left the queue
        */
        Customer leaveQueue();

        /**
         * @brief Function that returns the amount of customers that are ready to leave
         * @return num customers leaving 
        */
        int numCustomersLeaving();

        /**
         * @brief Function that returns the average amount of time that customers have been idle on average. 
         * @return avg idle time 
        */
        double calcAvgIdle();

        /**
         * @brief Function to calculate the longest window idle time for the office
         * @return int longest idle time 
        */
        int calcLongestIdle();

        /**
         * @brief Function to calculate amount of windows that were idle for over 5 minutes
         * @return num windows idle for >5 mins
        */
        int calcFiveWindowIdle();
        
        ListQueue<Customer> cQueue; // A queue of Customer objects, representing the current Queue in the office and Customers to be helped still. 
        ListQueue<Customer> cExited; // A queue of Customer objects, representing the Customers that have exited the queue and are finished at the SCC
        Customer current; // The current customer 
    private:
        Window* windowArr; // An array of Window objects to model each office, is an array of pointers as it is to be set. 
        int windowCount; // Indicating the number of windows. 

        
};

#endif