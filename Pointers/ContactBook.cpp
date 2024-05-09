#include <string>
#include <vector>
#include <iostream>
#include "ContactBook.h"
#include <algorithm>

using namespace std;

ContactBook::ContactBook(){

    for(int i = 0; i < size; i++){
        contacts[i] = nullptr;
    }


    this->size = sizeof(contacts)/sizeof(Contact*);

}
Contact* ContactBook::Find(string name_or_number){
    for(int i = 0; i < size; i++){
        if(contacts[i] == nullptr) continue;
        if(contacts[i]->getName() == name_or_number
           || contacts[i]->getNumber() == name_or_number
                ) {

            return contacts[i];
        }

    }
    return nullptr;
}
void ContactBook::Add(Contact& contact){
    for(int i = 0; i < size; i++){
        if(contacts[i] == nullptr) {
            this->contacts[i] = &contact;
            break;
        }
    }


    curr_size++;
}

void ContactBook::AddContacts(vector<Contact*> vector){
    for(auto j : vector){
        for(int i = 0; i < size; i++){
            if(contacts[i] == nullptr) {
                this->contacts[i] = j;

                break;
            }
        }
        curr_size++;
    }


    cout << endl;

}
void ContactBook::Remove(Contact& contact){
    cout << " Remove Called " << endl;
    for(int i = 0; i < size; i++){
        if(contacts[i] == &contact){

            contacts[i] = nullptr;
        }

    }




    cout << endl;
}

void ContactBook::Display(){
    for(int i = 0; i < size; i++){
        if(contacts[i] == nullptr) continue;
        if(contacts[i] != nullptr) contacts[i]->Display();
    }
}

void ContactBook::Alphabetize(){

    Contact* contacts_2[100];
    for(int i = 0; i < size; i++){
        contacts_2[i] = nullptr;
    }

    vector<string> names;
    for(int i = 0; i < size; i++){
        if(contacts[i] == nullptr) continue;
        else{
            names.push_back(contacts[i]->getName());

        }
    }



    std::sort(names.begin(), names.end());



    for(int i = 0; i < size; i++){
        if(names.size() != 0) {
            contacts_2[i] = ContactBook::Find(names.front());
            names.erase(names.begin());
        }
    }

    for(int i = 0; i < size; i++){
        contacts[i] = contacts_2[i];
    }


}

ContactBook& ContactBook::operator+=(Contact& contact) {
    Add(contact);
    return *this;
}

// ContactBook operator+=(ContactBook contact_book, ContactBook contact_book_2){

// }
// ContactBook operator+ (ContactBook contact_book, ContactBook contact_book_2){}
// ContactBook operator-= (ContactBook contact_book, Contact contact){}
// ContactBook operator-= (ContactBook contact_book, ContactBook contact_book_2){}
// ContactBook operator- (ContactBook contact_book, ContactBook contact_book_2){}
// bool operator== (ContactBook contact_book, ContactBook contact_book_2){}
// bool operator!= (ContactBook contact_book, ContactBook contact_book_2){}
















Contact::Contact(string name, string number){
    this->name = name;
    this->number = number;

}
string Contact::getName(){
    return name;
}
string Contact::getNumber(){
    return number;
}
void Contact::Display(){
    cout << name << ", " << number << endl;
}
