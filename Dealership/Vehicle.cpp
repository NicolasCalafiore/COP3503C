#include <iostream>
#include <string>
#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(){
    this->make = "COP3503";
    this-> model = "Rust Bucket";
    this-> year = 1900;
    this-> price = 0;
    this-> mileage = 0;
}

Vehicle::Vehicle(string make = "COP3503", string model = "Rust Bucket", unsigned int year = 1900, float price = 0, unsigned int mileage = 0){
    this->make = make;
    this->model = model;
    this->year = year;
    this->price = price;
    this->mileage = mileage;
}

void Vehicle::Display(){
    cout << year << " " << make << " " << model << " $" <<price << " " << mileage << endl;
}

string Vehicle::GetYearMakeModel(){
    return to_string(year) + " " + make + " " + model;
}

float Vehicle::GetPrice(){
    return price;
}

