// models the service center

#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <string>
#include "Office.h"
using namespace std; 

class ServiceCenter {
    public: 
        ServiceCenter();
        ~ServiceCenter();

        /**
         * Increments time, and increments the time for each office by calling Office::timeTick 
        */
        void timeTick(); 

        /**
         * @brief take in all the variables from the file, read the file. 
        */
        void getWindowAmount(); 

        /**
         * @brief creates an array of windows for each office
        */
        void setWindows();
        
        /**
         * @brief a method that reads the input file and retrieves the amount of customers in each service center.
        */
        void retrieveCustomers();

        /**
         * @brief runs the entire simulation loop of the students entering the office, waiting, and records their wait and idle times. 
        */
        void simulate();

        /**
         * @brief Calculates all the final statistics to be displayed, printing all the final stats. 
        */
        void calcStats();

        /**
         * @brief function that takes in a file name and sets the member variable of ServiceCenter to the file
         * @param inputF the file that is input
        */
        void setFile(string inputF);

        Office registrar; // Office object of registrar office
        Office cashier; // Office object of cashier office
        Office financial; // Office object of financial aid office 

        ListQueue<Customer> enteringCustomers; //line for entering students 
        ListQueue<Customer> returningLine; //line for students that need to go to another office
        ListQueue<Customer> isDone; //line for finished students used to retrieve statistics

    private: 
        // Tracks metrics such as student wait times and window idle times across all offices.
        string inputFile;

        int time; // variable keeping track of the time in the service center, to be updated
        int totalCustomers; // var to keep track of the number of the students in the center

        int numRegistrar; // variable indicating the number of windows open at the registrar
        int numCashier; // variable indicating the number of windows open at the cashier
        int numFinancial; // variable indicating the number of windows open at the financial aid office
        
        int timeArrived; // variable indicating the time a customer arrives
        int numStudentsArrived; // variable indicating the number of students that arrived (at a given time)
}; 

#endif 