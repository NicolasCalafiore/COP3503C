#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>

using namespace std;


class Vehicle{
private:
    string make;
    string model;
    unsigned int year;
    float price;
    unsigned int mileage;

public:
    Vehicle();
    Vehicle(string make, string model, unsigned int year, float price, unsigned int mileage);
    void Display();
    string GetYearMakeModel();
    float GetPrice();
};


#endif