#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int CountNumberOf(string, char);
bool IntegerAfterComma(string word, int index);
bool ValidateInput(string data_point);
string PrintStars(int value);

int main()
{
    string header_one;
    string header_two;
    string title;
    string data_point = "0";

    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    cout << "Enter the column 1 header:" << endl;
    getline(cin, header_one);
    cout << "You entered: " << header_one << endl;

    cout << "Enter the column 2 header:" << endl;
    getline(cin, header_two);
    cout << "You entered: " << header_two << endl;

    vector<string> authors;
    vector<int> values;

    while(data_point != "-1"){

        cout << "Enter a data point (-1 to stop input):" << endl;
        getline(cin, data_point);
        if(data_point != "-1") {
            if (ValidateInput(data_point)) {
                int comma_index = data_point.find_first_of(",");
                string author = data_point.substr(0, comma_index);
                string value = data_point.substr(comma_index + 2, data_point.length());
                authors.push_back(author);
                values.push_back(stoi(value));
                cout << "Data string: " << author << endl << "Data integer: " << value << endl;
            }
        }

    }
    cout << endl;
    cout << setw(33) << title << endl;
    cout << header_one << setw(21 - header_one.size()) << "|" << setw(23) << header_two << endl;
    cout << "--------------------------------------------" << endl;

    for(int i = 0; i < authors.size(); i++){
        cout << authors.at(i) << setw(21 - authors[i].length()) << "|" << setw(23) << values.at(i) << endl;
    }

    cout << endl;

    for(int i = 0; i < authors.size(); i++){
        cout << setw(20) << authors.at(i) << " " << PrintStars(values.at(i)) << endl;
    }
    cout <<  "=========================";



    return 0;
}

string PrintStars(int value){
    string stars = "";
    for(int i = 0; i < value; i++){
        stars.push_back('*');
    }

    return stars;
}

bool ValidateInput(string data_point){
    if(CountNumberOf(data_point, ',') == 0){
        cout << "Error: No comma in string." << endl;
        return false;
    }
    if(CountNumberOf(data_point, ',') > 1){
        cout << "Error: Too many commas in input." << endl;
        return false;
    }

    if(!IntegerAfterComma(data_point, data_point.find_first_of(","))){
        return false;
    }

    return true;
}

int CountNumberOf(string word, char character){
    int counter = 0;
    for(char i : word){
        if(i == character) counter++;
    }

    return counter;
}

bool IntegerAfterComma(string word, int index){
    string string_after_comma = word.substr(index + 2, word.length());
    try{
        int number = stoi(string_after_comma);
        return true;
    }
    catch(...){
        cout << "Error: Comma not followed by an integer." << endl;
        return false;
    }
}

