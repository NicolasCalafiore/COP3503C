///////////////////////////////////////////////////////////////////////////////
///////////////////////ONLY WORK IN THIS FILE//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef ABS_H
#define ABS_H

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

template <typename T> class ABS{

public:
    int max_capacity = 1;
    int top = -1;
    T* array_stack = new T[max_capacity];
    float scale_factor = 2.0f;

    ABS(){
    }
    ABS(int capacity){
        this->max_capacity = capacity;
    }
    ABS(const ABS &d){
//        this-> max_capacity = d.max_capacity + 5;
//        this-> array_stack = d.array_stack;
//        this-> top = d.top;

    }
    ABS &operator=(const ABS &d){}
    ~ABS(){
        delete[] array_stack;
    }
    void push(T data){
        if(isFull()){
            expandStack();
        }
        cout << "Attempting to push " << data << endl;
        if(top != -1) shiftToRight();
        array_stack[0] = data;
        top++;
    }
    T pop(){
        if(top == -1) throw runtime_error("EMPTY STACK");

        T object = array_stack[0];
        shiftToLeft();
        if( (float) getSize()/max_capacity < 1/scale_factor){
            reduceStack();
        }
        return object;
    }
    T peek(){
        if(top == -1) throw runtime_error("EMPTY STACK");
        else return array_stack[0];
    }
    unsigned int getSize(){
        return top + 1;
    }
    unsigned int getMaxCapacity(){
        return max_capacity;
    }
    T* getData(){
        return array_stack;
    }

    void DisplayStack(){
        cout << "STACK VIEW:" << endl;
        for(int i = 0; i < max_capacity; i++){
            if(i <= top) cout << i << ". " << array_stack[i] << endl;
            else  cout << i << ". NOT IN USE" << endl;
        }

    }

private:

    bool isFull(){
        if(top < max_capacity - 1) return false;
        return true;

    }

    void shiftToRight(){

        cout << "shiftToRight called" << endl;
        cout << "getSize(): " << top << endl;


        for(int i = top; i >= 0; i--){
            cout << "array_stack[" << i + 1 << "] = array_stack[" << i << "]" << endl;
            cout << array_stack[i + 1] << " = " << array_stack[i] << endl;
            if(i+1 < max_capacity) array_stack[i + 1] = array_stack[i];
        }

        cout  << endl;
    }

    void shiftToLeft(){
        for(int i = 0; i < top; i++){
            if(i + 1 < max_capacity)
                array_stack[i] = array_stack[i + 1];
        }
        top--;
    }

    void reduceStack() {
        int new_capacity = max((int)(max_capacity / scale_factor), 1);
        T* new_array = new T[new_capacity];

        for (int i = 0; i <= top; i++) {
            if(i < new_capacity) new_array[i] = array_stack[i];
        }

        delete[] array_stack;
        array_stack = new_array;
        max_capacity = new_capacity;
    }

    void expandStack() {
        int new_capacity = max_capacity * scale_factor;
        T* new_array = new T[new_capacity];

        for (int i = 0; i <= top; i++) {
            new_array[i] = array_stack[i];
        }

        delete[] array_stack;
        array_stack = new_array;
        max_capacity = new_capacity;
    }

};

#endif
