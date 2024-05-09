#ifndef ABQ_H
#define ABQ_H

/*
Template class
Copy Constructor
Copy Assignment operator
Destructor
Data will be stored using a dynamically allocated array
Attempting to push() or enqueue() an item onto an ABS/ABQ that is full will resize the current
capacity to current_capacity*scale_factor (scale_factor = 2.0f)

if the “percent full” (e.g. current size / max capacity) becomes
strictly less than 1/scale_factor, resize the storage array to current_capacity/scale_factor.

1. Create a new array based on the desired size
2. Copy elements from the old array to the new array (up to the size of the old array, or the
capacity of the new array, WHICHEVER IS SMALLER).
3. If you were adding something to the array, copy that as well
4. Delete the old array
5. Redirect the pointer to the old array to the new array

runtime_error

*/
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class ABQ{
    int max_capacity = 1;
    int top = -1;
    T* array_queue;
    float scale_factor = 2.0f;

public:
    ABQ(){
        this->array_queue = new T[max_capacity];
    }
    ABQ(int capacity){
        this->array_queue = new T[capacity];
        this->max_capacity = capacity;
    }
    ABQ(const ABQ &d){}
    ABQ &operator=(const ABQ &d){}
    ~ABQ(){
        delete[] array_queue;
    }
    void enqueue(T data){
        if(isFull()){
            expandStack();
        }
        top++;

        array_queue[top] = data;

    }
    T dequeue(){
        if(top == -1) throw runtime_error("EMPTY STACK");
        T object = array_queue[0];
        shiftLeft();

        if( (double) top/max_capacity < (double) 1/scale_factor){
            reduceStack();
        }

        top--;
        return object;
    }
    T peek(){
        if(top == -1) throw runtime_error("EMPTY STACK");
        return array_queue[0];
    }
    unsigned int getSize(){
        return top + 1;
    }
    unsigned int getMaxCapacity(){
        return max_capacity;
    }
    T* getData(){
        return array_queue;
    }

    void DisplayQueue(){
        cout << "STACK VIEW:" << endl;
        for(int i = 0; i < max_capacity; i++){
            if(i <= top) cout << i << ". " << array_queue[i] << endl;
            else  cout << i << ". NOT IN USE" << endl;
        }

    }

private:

    void shiftLeft(){
        for(int i = 1; i < max_capacity; i++){
            array_queue[i - 1] = array_queue[i];
        }
    }

    void expandStack() {
        int new_capacity = max_capacity * scale_factor;
        T* new_array = new T[new_capacity];

        for (int i = 0; i <= top; i++) {
            new_array[i] = array_queue[i];
        }

        delete[] array_queue;
        array_queue = new_array;
        max_capacity = new_capacity;
    }

    bool isFull(){
        if(top == max_capacity - 1) return true;
        return false;
    }

    void reduceStack(){
        int new_capacity = max((int)(max_capacity / scale_factor), 1);
        T* new_array = new T[new_capacity];

        for(int i = 0; i <= top; i++){
            if(i < new_capacity) new_array[i] = array_queue[i];
        }

        delete[] array_queue;
        array_queue = new_array;
        max_capacity = new_capacity;
    }


};

#endif