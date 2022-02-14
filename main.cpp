#include <iostream>
#include <string>


using std::cout;
using std::cin;
using std::endl;
using std::string;


bool validate_input(string input);


int main()
{
    cout << endl << "Įveskite studento vardą" << endl;
    string first_name;

    do {

        cout << "> ";
        getline(cin, first_name);

        if (!validate_input(first_name)) {
            cout << endl << "Įveskite studento vardą" << endl;
            continue;
        }

        break;

    } while (true);


    cout << endl << "Įveskite studento pavardę" << endl;
    string last_name;

    do {

        cout << "> ";
        getline(cin, last_name);

        if (!validate_input(last_name)) {
            cout << endl << "Įveskite studento pavardę" << endl;
            continue;
        }

        break;

    } while (true);


    cout << endl << first_name << " " << last_name << endl; 
    return 0;
}


bool validate_input(string input)
{

    if (input.empty()) {
        return false;
    }


    bool valid_string = true;
    for (std::size_t i{}; i < input.size() && valid_string; i++) {
        if (!(std::isalnum(input[i])) || std::isspace(input[i])) {
            valid_string = false;
        }
    }

    return valid_string;
}
