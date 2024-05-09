#include <iostream>
#include <fstream>
using namespace std;

//00 null termiantor of element
void GetShipsFromFile(string path, vector<Ship>& ships){
    ifstream file;
    file.open(path, ios::binary);

    int number_of_ships;
    file.read(reinterpret_cast<char*> (&number_of_ships), sizeof(number_of_ships));
    // cout << number_of_ships << endl;


    for(int i = 0; i < number_of_ships; i++){
        int ship_name_length;
        file.read(reinterpret_cast<char*> (&ship_name_length), sizeof(ship_name_length));
        // cout << ship_name_length << endl;

        char ship_name[ship_name_length];
        file.read(reinterpret_cast<char*> (&ship_name), sizeof(ship_name));
        // cout << ship_name << endl;

        int ship_class_length;
        file.read(reinterpret_cast<char*> (&ship_class_length), sizeof(ship_class_length));
        // cout << ship_class_length << endl;

        char ship_class[ship_class_length];
        file.read(reinterpret_cast<char*> (&ship_class), sizeof(ship_class));
        // cout << ship_class << endl;

        short length;
        file.read(reinterpret_cast<char*> (&length), sizeof(length));
        // cout << length << endl;


        int shield_capacity;
        file.read(reinterpret_cast<char*> (&shield_capacity), sizeof(shield_capacity));
        // cout << shield_capacity << endl;

        float max_warp;
        file.read(reinterpret_cast<char*> (&max_warp), sizeof(max_warp));
        // cout << max_warp << endl;

        // cout << "Armaments" << endl;

        int arm_count;
        file.read(reinterpret_cast<char*> (&arm_count), sizeof(arm_count));
        // cout << arm_count << endl;

        vector<Weapon> weapons;
        for(int i = 0; i < arm_count; i++){
            int weapon_name_length;
            file.read(reinterpret_cast<char*> (&weapon_name_length), sizeof(weapon_name_length));
            // cout << weapon_name_length << endl;

            char weapon_name[weapon_name_length];
            file.read(reinterpret_cast<char*> (&weapon_name), sizeof(weapon_name));
            // cout << weapon_name << endl;

            int firewpower;
            file.read(reinterpret_cast<char*> (&firewpower), sizeof(firewpower));
            // cout << firewpower << endl;

            float unknown_number;
            file.read(reinterpret_cast<char*> (&unknown_number), sizeof(unknown_number));
            // cout << unknown_number << endl;

            Weapon weapon(weapon_name, firewpower, unknown_number);
            weapons.push_back(weapon);
        }

        Ship ship(ship_name, ship_class, length, shield_capacity, max_warp, weapons);
        ships.push_back(ship);
    }
}

int main()
{
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    vector<Ship> ships;
    string path = "";
    if(option == 1) {
        GetShipsFromFile("friendlyships.shp", ships);
    }
    if(option == 2){
        GetShipsFromFile("enemyships.shp", ships);
    }
    if(option == 3){
        GetShipsFromFile("friendlyships.shp", ships);
        GetShipsFromFile("enemyships.shp", ships);
    }



    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    cin >> option;

    if(option == 1){
        for(Ship i : ships){
            i.PrintShip();
        }
    }

    if(option == 2){
        int max = 0;
        int index = 0;
        for(int i = 0; i < ships.size(); i++){
            int max_fire_power = ships[i].GetMaxWeaponFirePower();
            if(max_fire_power > max){
                index = i;
                max = max_fire_power;
            }
        }
        ships[index].PrintShip();
    }

    if(option == 3){
        int max = 0;
        int index = 0;
        for(int i = 0; i < ships.size(); i++){
            int firepower = ships[i].GetTotalFirePower();
            if(firepower > max){
                index = i;
                max = firepower;
            }
        }
        ships[index].PrintShip();
    }

    if(option == 4){
        int min = ships[0].GetTotalFirePower();
        int index = 0;
        for(int i = 1; i < ships.size(); i++){
            int firepower = ships[i].GetTotalFirePower();
            if(firepower < min && ships[i].GetWeapons().size() != 0){
                index = i;
                min = firepower;
            }
        }
        ships[index].PrintShip();
    }

    if(option == 5){

        for(int i = 1; i < ships.size(); i++){

            if(ships[i].GetWeapons().size() == 0){
                ships[i].PrintShip();
            }
        }

    }



    return 0;
}