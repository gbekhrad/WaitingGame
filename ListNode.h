#ifndef LIST_NODE_H
#define LIST_NODE_H
#include <cstdlib>

template<typename T>
class ListNode{
    public:
        /**
         * @brief Default Constructor
        */
        ListNode(T d);

        /**
         * @brief Default Destructor 
        */
        virtual ~ListNode();

        /**
         * data to be stored in the node of type T. 
        */
        T data;

        /**
         * pointer to the next listnode. 
        */
        ListNode<T>* next;

        /**
         * pointer to the previous listnode 
        */
        ListNode<T>* prev;
};

template<typename T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template<typename T>
ListNode<T>::~ListNode(){
    next = NULL;
    prev = NULL;
}

#endif