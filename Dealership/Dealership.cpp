#include <iostream>
#include <string>
#include <vector>
#include "Dealership.h"
#include "Showroom.h"

using namespace std;


Dealership::Dealership(string name, unsigned int capacity){
    this->name = name;
    this->capacity = capacity;
}

void Dealership::AddShowroom(Showroom s){
    if(showroom_vector.size() == capacity){
        cout << "Dealership is full, can't add another showroom!" << endl;
    }
    else{
        showroom_vector.push_back(s);
    }
}
float Dealership::GetAveragePrice(){
    float total = 0;
    float count = 0;
    for(int i = 0; i < showroom_vector.size(); i++){
        total += showroom_vector[i].GetInventoryValue();
        count += showroom_vector[i].GetVehicleList().size();
    }

    return total / count;
}


void Dealership::ShowInventory(){
    if(showroom_vector.size() == 0){
        cout << name << " is empty!" << endl;
        cout << "Average car price: $0.00" ;
    }
    else{
        for(int i = 0; i < showroom_vector.size(); i++){
            cout << "Vehicles in " << showroom_vector[i].name << endl;
            vector<Vehicle> vehicle_list_on_showroom = showroom_vector[i].GetVehicleList();
            for(int j = 0; j < vehicle_list_on_showroom.size(); j++){
                vehicle_list_on_showroom[j].Display();
            }
            cout << endl;
        }

        cout << "Average car price: $" << Dealership::GetAveragePrice();
    }
}



