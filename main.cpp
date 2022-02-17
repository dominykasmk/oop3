#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <algorithm>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::array;


struct Student {
    string first_name;
    string last_name;

    unsigned num_of_scores{};
    static constexpr unsigned max_num_of_scores{10};
    array<unsigned, max_num_of_scores> scores{};

    double score_average{};
    double score_median{};
};


bool validate_input(string input);
void ignore_line();
void print_students(const std::array<Student, 10> &students, int num_of_students, unsigned option);


int main()
{
    cout << "Įveskite studento vardą" << endl;
    string first_name;

    constexpr unsigned max_num_of_students = 10;
    unsigned num_of_students = 0;
    array<Student, max_num_of_students> students;
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
        << "Įveskite -1 jei norite baigti įvedimą\n"
        << "Pažymių kiekis neturi viršyti 10ies" << endl;

    unsigned score;
    int max_num_of_scores = 10;

    while (true) {

        cout << "> ";
        cin >> score;

        if (cin.fail() || (score < 1 || score > 10 || score == -1)) {

            cin.clear();
            ignore_line();

            if (score == -1) {

                // Suvedus visus pažymius suskaičiuojam vidurkį ir medianą
                double average{};
                for (int i{}; i < student.num_of_scores; i++) {
                    average += student.scores[i];
                }
                student.score_average = average / student.num_of_scores;

                // Surikiuojam pažymius medianos apskaičiavimui
                std::sort (student.scores.begin(), student.scores.begin() + student.num_of_scores);
                
                if (student.num_of_scores % 2 == 0) {
                    int index2 = (int)student.num_of_scores / 2;
                    int index1 = (int)student.num_of_scores / 2 - 1;
                    double num_1 = student.scores[index1];
                    double num_2 = student.scores[index2];
                    student.score_median = (num_1 + num_2) / 2;
                }
                else {
                    int temp = (int)student.num_of_scores / 2;
                    student.score_median = student.scores[student.num_of_scores / 2];
                }
                
                break;
            }

            cout << "Įveskite skaičių nuo 1 iki 10" << endl;
            continue;

        } else {
            student.scores[student.num_of_scores++] = score;
            cout << endl;
        }

    } 
    
    students[num_of_students++] = student;
    cout << "Pasirinkite ar norite apskaičiuoti vidurkį (1) ar medianą (2)?" << endl;
    int option;
    while (true) {

        cout << "> ";
        cin >> option;

        if (cin.fail() || (option != 1 && option != 2)) {
            cout << "xdPasirinkite ar norite apskaičiuoti vidurkį (1) ar medianą (2)?" << endl;
            cin.clear();
            ignore_line(); 
            continue;
        }
        
        break;
    }

    print_students(students, num_of_students, option);

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

void print_students(const std::array<Student, 10> &students, int num_of_students, unsigned option)
{
    std::cout << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::left << "Vardas"
        << std::left << "Galutinis ";
    (option == 1) ? std::cout << "(Vid.)" : std::cout << "(Med).";
    cout << endl << endl;

    std::string temp(50, '-');
    cout << temp << endl;

    for (int i{}; i < num_of_students; i++) {
        std::cout << std::setw(15) << std::left << students[i].first_name;
        std::cout << std::setw(15) << std::left << students[i].last_name;
        
        switch (option) {
            case 1:
                std::cout << students[i].score_average << std::endl << std::endl;
                break; 

            case 2:
                std::cout << students[i].score_median << std::endl << std:: endl;
                break; 
        }
    }
}
