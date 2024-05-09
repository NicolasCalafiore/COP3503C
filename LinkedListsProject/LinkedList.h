#ifndef LINKED_H
#define LINKED_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class LinkedList{

public:
    class Node{
    public:
        Node(T data){
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
        T data;
        Node* next;
        Node* prev;
    };

    LinkedList(){
        //std::cout << "LinkedList Created" << endl;

    }
    ~LinkedList(){
        Node* node = head_node;
        while(node != nullptr) {
            Node* next_node = node->next;
            delete node;
            node = next_node;
        }
    } // Delete all nodes in list
    void AddHead(T data){
        Node* curr = head_node;
        this->head_node = new Node(data);
        head_node->next = curr;


        //std::cout << "New Head Node Value: " << head_node->data << endl;

    } // New Node at front of list
    void AddTail(T data){
        Node* new_node = new Node(data); // Use Node* instead of Node

        if (head_node == nullptr) {
            head_node = new_node;
        } else {
            Node* last_node = GetLastNode();
            last_node->next = new_node;
            new_node->prev = last_node;
        }


    } // New Node at end of list
    void AddNodesHead(T data_array[], int size){

        //cout << endl << "AddNodesHead Called" << endl;
        for (int i = size - 1; i >= 0; i--){
            Node* node = new Node(data_array[i]);
            if (head_node != nullptr) {
                head_node->prev = node; // Ensure the current head node's previous pointer is updated.
            }
            node->next = head_node;
            head_node = node;
            //cout << "Node Created for Data: " << data_array[i] << " and added to head" << endl;

        }
    } // Given array, insert a node for each at beggining of list w/ order
    void AddNodesTail(T data_array[], int size){
        //cout << endl << "AddNodesTail Called" << endl;

        for (int index = 0; index < size; index++) {
            Node* node = new Node(data_array[index]);
            //cout << "Node Created for Data: " << data_array[index] << endl;

            if (head_node == nullptr) {
                head_node = node;
            } else {
                Node* last_node = GetLastNode(); // Find the last node.
                last_node->next = node;
                node->prev = last_node;
            }
        }
    } // ^ v.v
    int NodeCount(){
        Node* node = head_node;
        int counter = 1;
        while(node->next != nullptr){
            counter++;
            node = node->next;
        }

        return counter;
    } //  How many things are stored in this list
    void PrintForward(){

        //std::cout << "Node Value: " << head_node->data << endl;

        //std:: cout << endl << "PRINT FUNC CALLED" << endl;
        Node* node = head_node;
        while(node != nullptr){
            std::cout << node->data << endl;
            node = node->next;
        }


    } //Iterate through all of the nodes and print
    void PrintReverse(){
        //std:: cout << endl << "PRINT FUNC CALLED REVERSED" << endl;
        Node* node = head_node;
        vector<Node*> nodes;
        while(node != nullptr){
            nodes.push_back(node);
            node = node->next;
        }

        //std:: cout << nodes.size() << endl;
        for(int i = nodes.size() - 1; i >= 0; i--){
            std:: cout << nodes[i]->data << endl;
        }
    } // ^.^ v.v

    Node* getHead(){
        return head_node;
    }

private:
    Node* head_node = nullptr;

    Node* GetLastNode(){
        Node* node = head_node;
        while(node->next != nullptr){
            node = node->next;
        }

        return node;
    }




};

#endif
