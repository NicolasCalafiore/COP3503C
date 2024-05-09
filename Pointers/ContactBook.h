#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Contact;

class ContactBook{
private:
    Contact* contacts[100];
    unsigned int size = 100;
    unsigned int curr_size = 0;

public:
    ContactBook();
    Contact* Find(string name_or_number);
    void Add(Contact& contact);
    void AddContacts(vector<Contact*> vector);
    void Remove(Contact& contact);
    void Display();
    void Alphabetize();

    ContactBook& operator+=(Contact& contact);
    ContactBook operator+=(ContactBook contact_book){

    }
    ContactBook operator+ (ContactBook contact_book);
    ContactBook operator-= (Contact contact);
    ContactBook operator-= (ContactBook contact_book);
    ContactBook operator- (ContactBook contact_book);
    bool operator== (ContactBook contact_book);
    bool operator!= (ContactBook contact_book);
    void FillArrayGaps();

};


class Contact{

private:
    string name;
    string number;

public:
    Contact(string name, string number);
    string getName();
    string getNumber();
    void Display();

};

#endif