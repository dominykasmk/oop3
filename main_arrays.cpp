#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::array;


struct Student {
    string first_name;
    string last_name;

    unsigned scores_amount{};
    unsigned scores_max_amount = 10;
    unsigned *scores = new unsigned[scores_max_amount];

    double score_average{};
    double score_median{};
};


bool validate_input(string input);
template <typename T>
T test_validation(T &input, std::string prompt, std::string error_msg);
void input_valid_string(std::string &input, const string prompt);
void input_valid_num(unsigned &input, unsigned left_range, unsigned right_range);
void calculate_averages(Student &student);
void ignore_line();
void print_students(const Student *students, size_t student_amount, unsigned option);
unsigned generate_random_score();
void resize_student_array(Student **students, size_t &array_size);
void resize_score_array(unsigned **scores, unsigned &array_size);


int main()
{

    size_t student_array_size = 5;
    size_t student_amount = 0;
    Student *students = new Student[student_array_size];
    cout << "\nJeigu norite baigti įvestį, įveskite 'x'\n";


    while (true) {

        Student student;
        string prompt{"\nĮveskite studento vardą\n"};
        string input;
        input_valid_string(input, prompt);
        if (input == "x")
            break;
        student.first_name = input;


        prompt = "\nĮveskite studento pavardę\n";
        input_valid_string(input, prompt);
        if (input == "x")
            break;
        student.last_name = input;


        unsigned max_scores_amount = 100;
        prompt = "\nAr norėtumėte sugeneruoti pažymius atsitiktinai?(y/n)\n";

            
        while (true) {
            
            input_valid_string(input, prompt);

            if (input == "y" || input == "taip") {
                    
                cout << "\nPasirinkite kiek pažymių sugeneruoti(1/100)" << endl;
                unsigned amount_to_generate{};
                input_valid_num(amount_to_generate, 1, max_scores_amount);

                unsigned score;
                cout << "\nSugeneruoti pažymiai\n";
                for (int i{}; i < amount_to_generate; i++) {
                        
                        student.scores[student.scores_amount++] = generate_random_score();
                        cout << student.scores[student.scores_amount - 1] << " ";
                        student.scores_amount % 10 == 0 ? cout << '\n' : cout << "";

                        if (student.scores_amount > student.scores_max_amount) {
                            resize_score_array(&student.scores, student.scores_max_amount);
                        }
                }
                cout << endl;

                break;
            }
            else if (input == "n" || input == "ne") {

                unsigned score;
                cout << "\nVeskite studento pažymius (paskutinis turi būti egzamino pažymys).\n"
                    << "Įveskite -1 jei norite baigti įvedimą\n"
                    << "Pažymių kiekis neturi viršyti 10ies\n" << endl;

                while (true) {

                    input_valid_num(score, 1, 10);

                    if (score == -1) {

                        if (student.scores_amount == 0) {
                            student.scores[0] = 0;
                        }

                        break;
                    }
                    else {
                        
                        student.scores[student.scores_amount++] = score;
                        if (student.scores_amount > student.scores_max_amount) {
                            resize_score_array(&student.scores, student.scores_max_amount);
                        }
                    }
                }

                break;
            }
            else {
                prompt = "\n'y' arba 'taip' jei norite generuoti atsitiktinai, 'ne' jei ne\n";
            }
        }
        cin.clear();
        ignore_line();


        calculate_averages(student);
        if (student_amount + 1 > student_array_size) {
            resize_student_array(&students, student_array_size);
        }
        students[student_amount++] = student;
    }


    if (student_amount == 0) {
        cout << "\nNeįvedėte nei vieno studento.\n" << endl;
        return 0;
    }

    cout << "\nPasirinkite ar norite apskaičiuoti vidurkį (1) ar medianą (2)?" << endl;
    unsigned option;
    input_valid_num(option, 1, 2);
    print_students(students, student_amount, option);

    return 0;
}


void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void resize_student_array(Student **students, size_t &array_size)
{
    Student *new_array = new Student[array_size * 2];
    memcpy(new_array, *students, array_size * sizeof(Student));
    array_size *= 2;
    *students = new_array;
}

void resize_score_array(unsigned **scores, unsigned &array_size)
{

    unsigned *new_array = new unsigned[array_size * 2];
    memcpy(new_array, *scores, array_size * sizeof(unsigned));
    array_size *= 2;
    *scores = new_array;
}

void input_valid_string(std::string &input, const string prompt)
{
    cout << prompt;
    while (true) {

        cout << "> ";
        cin >> input;

        if (!cin) {
            cout << prompt << endl;
            cin.clear();
            ignore_line();
        }
        else {
            ignore_line();
            break; 
        }
    }
}

void input_valid_num(unsigned &input, unsigned left_range, unsigned right_range)
{
    do {

        cout << "> ";
        cin >> input;

        if (cin.good()) {
            break;
        }

        if (cin.fail() || (input < left_range || input > right_range)) {
            cout << "\nĮveskite skaičių tarp " << left_range << " ir " << right_range << "\n";
            cin.clear();
            ignore_line(); 
            continue;
        }
        else {
            break;
        }

    } while (true);
}


void calculate_averages(Student &student)
{
    double average{};
    for (int i{}; i < student.scores_amount; i++) {
        average += student.scores[i];
    }
    student.score_average = average / student.scores_amount;

    // Surikiuojam pažymius medianos apskaičiavimui
    std::sort (student.scores, student.scores + student.scores_amount);

    
    if (student.scores_amount % 2 == 0) {
        int index2 = (int)student.scores_amount / 2;
        int index1 = (int)student.scores_amount / 2 - 1;
        double num_1 = student.scores[index1];
        double num_2 = student.scores[index2];
        student.score_median = (num_1 + num_2) / 2;
    }
    else {
        int temp = (int)student.scores_amount / 2;
        student.score_median = student.scores[student.scores_amount / 2];
    }
}


void print_students(const Student *students, size_t student_amount, unsigned option)
{
    std::cout << "\n" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::left << "Vardas"
        << std::left << "Galutinis ";
    (option == 1) ? std::cout << "(Vid.)" : std::cout << "(Med).";
    cout << endl << endl;

    std::string temp(50, '-');
    cout << temp << endl;

    for (int i{}; i < student_amount; i++) {
        std::cout << std::setw(15) << std::left << students[i].last_name;
        std::cout << std::setw(15) << std::left << students[i].first_name;
        
        switch (option) {
            case 1:
                std::cout << std::setprecision(2) << students[i].score_average << std::endl << std::endl;
                break; 

            case 2:
                std::cout << std::setprecision(2) << students[i].score_median << std::endl << std:: endl;
                break; 
        }
    }
}

unsigned generate_random_score()
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);
    
    return dist(mt);
}
