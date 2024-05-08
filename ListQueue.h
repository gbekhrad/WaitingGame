#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DblList.h"

template <typename T>
class ListQueue: private DblList<T>{ //inherit from the DL List but don't make an is-a relationship
public:
  /**
   * @brief Default Constructor
  */
  ListQueue(); 

  /**
   * @brief Default Destructor
  */
  ~ListQueue();

  /**
   * @brief a function that inserts data and inserts it in the queue 
   * @param data of type T to be inserted
  */
  void enqueue(T data);

  /**
   * @brief removes the data from the end of the queue. 
   * @return the data that was dequeued
  */
  T dequeue();

  /**
   * @brief function that grabs the top element of the queue. 
   * @return the data at the top
  */
  T peek();

  /**
   * @brief gets the size of the queue
   * @returns int representation of the size 
  */
  int getSize();

  /**
   * @brief checks if the list is empty
   * @returns boolean true or false, true if empty
  */
  bool isEmpty();

  /**
   *  @brief prints the queue. 
  */
  void printQueue(); 
};

template <typename T>
bool ListQueue<T>::isEmpty(){
  return DblList<T>::isEmpty();
}

template <typename T>
int ListQueue<T>::getSize(){
  return DblList<T>::getSize();
}

template <typename T>
ListQueue<T>::ListQueue(){
}

template <typename T>
ListQueue<T>::~ListQueue(){
}

template <typename T>
T ListQueue<T>::dequeue(){
  return DblList<T>::removeFront(); //smallest always at front
}

template <typename T>
T ListQueue<T>::peek(){
  return DblList<T>::get(0); //smallest always at front
}

template <typename T>
void ListQueue<T>::enqueue(T d){
  if (isEmpty()){ 
    DblList<T>::insertFront(d);
    return;
  } else {
    DblList<T>::insertBack(d);
  }
}

template <typename T>
void ListQueue<T>::printQueue(){
  DblList<T>::printList();
}


#endif