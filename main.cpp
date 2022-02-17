#include <iostream>
#include <string>
#include <limits>


using std::cout;
using std::cin;
using std::endl;
using std::string;


struct Student {
    string first_name;
    string last_name;
    unsigned scores[10]{0};
    unsigned num_of_scores{};
};


bool validate_input(string input);
unsigned get_score();
void ignore_line();
void print_student(Student &student);




int main()
{
    cout << "Įveskite studento vardą" << endl;
    string first_name;

    unsigned num_of_students = 10;
    unsigned current_student = 0;
    Student students[num_of_students];
    Student student;

    do {

        cout << "> ";
        getline(cin, first_name);

        if (!validate_input(first_name)) {
            cout << endl << "Įveskite studento vardą" << endl;
            continue;
        }
        
        student.first_name = first_name;
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

        student.last_name = last_name;
        break;

    } while (true);


    cout << endl << "Veskite studento pažymius (paskutinis turi būti egzamino pažymys).\n"
        << "Kai norėsite baigti įvedimą įveskite EOF (ctrl+z on windows, ctrl+d on Unix).\n"
        << "Pažymių kiekis neturi viršyti 10ies" << endl;

    unsigned score;
    int max_num_of_scores = 10;
    int current_score = 0;

    while (true) {

        cout << "> ";
        cin >> score;

        if (cin.eof()) {
            ignore_line();
            cout << endl;
            break;
        }

        if (cin.fail() || (score < 1 || score > 10)) {
            cout << "Įveskite skaičių nuo 1 iki 10" << endl;
            cin.clear();
            ignore_line();

            continue;
        }
        else {
            student.scores[current_score++] = score;
            cout << endl;
        }

    } 

    students[current_student++] = student;
    print_student(students[0]);

    return 0;
}


void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


bool validate_input(string input)
{

    if (input.empty()) {
        return false;
    }


    bool valid_string = true;
    for (decltype(input.size()) i{}; i != input.size() && valid_string; i++) {
        if (!(std::isalnum(input[i])) || std::isspace(input[i])) {
            valid_string = false;
        }
    }

    return valid_string;
}

void print_student(Student &student)
{
    cout << student.first_name << " " << student.last_name << endl;
    cout << "Pažymiai: ";
    for (auto s : student.scores) {
        if (s == 0)
            break;

        cout << s << " ";
    }

    cout << endl;
}
