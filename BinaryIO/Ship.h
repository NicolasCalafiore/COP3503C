#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Weapon{
public:
    string name;
    int firepower;
    float unknown_number;

    Weapon(string name, int firepower, float unknown_number){
        this->name = name;
        this->firepower = firepower;
        this->unknown_number = unknown_number;
    }

    void PrintWeapon(){
        cout << name << ", " << firepower << ", " << unknown_number << endl;
    }



};

class Ship{
private:
    string name;
    string ship_class;
    short length;
    int shield_cap;
    float warp_speed;
    vector<Weapon> weapons_list;

public:
    Ship(string name, string ship_class, short length, int shield_cap, float warp_speed, vector<Weapon> weapons_list){
        this->name = name;
        this->ship_class = ship_class;
        this->length = length;
        this->shield_cap = shield_cap;
        this->warp_speed = warp_speed;
        this->weapons_list = weapons_list;
    }

    void PrintShip(){
        cout << "Name: " << name << endl;
        cout << "Class: " << ship_class << endl;
        cout << "Length: " << length << endl;
        cout << "Shield capacity: " << shield_cap << endl;
        cout << "Maximum Warp: " << warp_speed << endl;
        cout << "Armaments: " << endl;
        if(weapons_list.size() == 0){
            cout << "Unarmed" << endl;
        }
        else{
            int firepower = 0;
            for(Weapon i : weapons_list){
                i.PrintWeapon();
                firepower += i.firepower;
            }
            cout << "Total firepower: " << firepower << endl;
        }

        cout << endl;
    }


    int GetMaxWeaponFirePower(){
        int max = 0;
        for(Weapon i : weapons_list){
            if(i.firepower > max) max = i.firepower;
        }
        cout << endl;

        return max;
    }

    int GetShieldCap(){
        return shield_cap;
    }

    int GetTotalFirePower(){
        int firepower = 0;
        for(Weapon i : weapons_list){
            firepower += i.firepower;
        }

        return firepower;
    }

    vector<Weapon> GetWeapons(){
        return weapons_list;
    }
};


#endif