#ifndef DBL_LIST_H
#define DBL_LIST_H

#include <iostream>
#include "ListNode.h"
using namespace std;

template <typename T>
class DblList{
    public:
        /**
         * @brief Default Constructor
        */
        DblList();

        /**
         * @brief Default Destructor
        */
        ~DblList();

        /**
         * @brief gets the size of the doubly-linked list
         * @returns int representation of the size 
        */
        int getSize();

        /**
         * @brief checks if the list is empty
         * @returns boolean true or false, true if empty
        */
        bool isEmpty();

        /**
         * @brief inserts object of type T to the front of the doubly-linked list
         * @param data of type T to be inserted 
        */
        void insertFront(T data);

        /**
         * @brief inserts object of type T to the back of the doubly-linked list
         * @param data of type T to be inserted 
        */
        void insertBack(T data);

        /**
         * @brief gets an object at a specified location and returns the object 
         * @param pos integer of the position that is to be returned
         * @return object of type T at position
        */
        T get(int pos);

        /**
         * @brief removes object of type T from the front of the doubly-linked list
         * @param data of type T to be removed 
        */
        T removeFront();

        /**
         * @brief removes object of type T from the back of the doubly-linked list
         * @param data of type T to be removed 
        */
        T removeBack();

        /**
         * @brief a function that prints the doubly-linked list. 
        */
        void printList();

        /**
         * node object keeping track of the front of the DLL.
        */
        ListNode<T>* front;

        /**
         * node object keeping track of the back of the DLL.
        */
        ListNode<T>* back;

        /**
         * integer representation of the size of the DLL.
        */
        int size;
};

template<typename T>
DblList<T>::DblList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template<typename T>
DblList<T>::~DblList() {
    // There is more to be done, looping through and deleting the nodes
    // But it results in a segfault

    // ListNode<T> *node = front;
    // ListNode<T> *nodeToBeDeleted = front; 

    // while (node != NULL){
    //     nodeToBeDeleted = node->next;
    //     delete node; 

    //     node = nodeToBeDeleted; 
    // }

    front = NULL;
    back = NULL;
    size = 0;
}

template<typename T>
void DblList<T>::insertFront(T data){
    ListNode<T>* node = new ListNode<T>(data);
    if(!isEmpty()){
        node->next = front;
        front->prev = node;
    }else{
        back = node;
    }
    front = node;
    ++size;
}

template<typename T>
void DblList<T>::insertBack(T data){
    ListNode<T>* node = new ListNode<T>(data);
    
    if(isEmpty()){
        front = node; // we are inserting to the back, and we're eventually gonna update the other one 
    } else {
        node->prev = back;
        back->next = node; 
    }
    back = node;
    ++size;
}

template<typename T>
T DblList<T>::removeFront(){
    T data = front->data;
    if(size == 1){
        delete front;
        front = NULL;
        back = NULL;
    }else{
        ListNode<T>* currFront = front;
        front = front->next;
        front->prev = NULL;
        delete currFront;
    }
    --size;
    return data;
}

template<typename T>
T DblList<T>::removeBack(){
    //make sure not empty
     T data = back->data;
     if (size == 1){
        delete back;
        front = NULL;
        back = NULL;
     } else {
        ListNode<T>* currBack = back;
        back = back->prev;
        back->next = NULL;
        delete currBack;
     }
     --size;
     return data;
}

template<typename T>
T DblList<T>::get(int pos){
    //is pos in range, etc.
    ListNode<T>* current = front;
    int cPos = 0;
    while(cPos != pos){
        current = current->next;
        ++cPos;
    }
    return current->data;
}

template <typename T>
void DblList<T>::printList(){
    string s;

    s+= "[";
    for(int i = 0; i < size; ++i){
        s+= "Customer " + to_string(i) + ", ";
    }
    s = s.substr(0, s.size() - 2); // cuts the last ", " out 
    s += "]";
    cout << s << endl; // print it 
} 

template<typename T>
int DblList<T>::getSize(){
    return size;
}

template<typename T>
bool DblList<T>::isEmpty(){
    return (size == 0);
}

#endif