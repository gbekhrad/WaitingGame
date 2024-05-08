// models a single window in one of the offices

#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"
/**
 * @brief Models a single service window within an office.
 * Tracks the status of the window (occupied or idle).
 * Serves students by processing their tasks for a specified duration.
 * Records metrics such as window idle time.
*/
class Window {
    public:
        /**
         * @brief Default constructor 
        */
        Window();
        
        /**
         * @brief Default destructor
        */
        ~Window();

        /**
         * 
        */
        void processTask(Customer ctmr);


        Customer leaveWindow();
        
        /**
         * @brief Function that decreases the amount of time given. 
         * Ex: a customer is supposed to wait for 5, it'll decrement as they're in line.
        */
        void clockTick();

        /**
         * @brief Function that increments the amount of time the Customer has been idle. 
        */
        void addIdleTime();

        /**
         * @brief Getter for the timeIdle variable.
         * @return timeIdle
        */
        int getTimeIdle();

        /**
         * @brief function that checks if a window is occupied
         * @return boolean indicating if its occupied or not. 
        */
        bool isOccupied();

        // boolean to keep track of whether the window is currently occupied.
        bool occupied; 

        // integer indicating the amount of time waited at a window.
        int timeWaited; 

        // integer indicating the amount of time idle at a window.
        int timeIdle; 
    private:
        Customer currCustomer; // object to keep track of the current customer at the window
};

#endif

