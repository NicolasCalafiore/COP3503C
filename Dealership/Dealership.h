#ifndef DEALERSHIP_H
#define DEALERSHIP_H
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Showroom.h"

class Dealership{
private:
    vector<Showroom> showroom_vector;
    string name;
    unsigned int capacity;

public:
    Dealership(string name = "Generic Dealership", unsigned int capacity = 0);

    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};

#endif