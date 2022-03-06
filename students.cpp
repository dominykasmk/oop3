#include "students.hpp"

void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void calculate_averages(Student &student)
{
    if (student.scores.empty()) {
        student.score_average = student.score_median = 0;
        return;
    }

    double average{};
    for (const auto score : student.scores) {
        average += score;
    }
    student.score_average = average / student.scores.size();

    // Surikiuojam pažymius medianos apskaičiavimui
    std::sort (student.scores.begin(), student.scores.begin() + student.scores.size());

    
    if (student.scores.size() % 2 == 0) {
        student.score_median = (student.scores[(student.scores.size() - 1) / 2] + 
            student.scores[student.scores.size() / 2]) / 2.0;
            return;
    }
    student.score_median = student.scores[student.scores.size() / 2];
}

int input_student(Student *student)
{
    string prompt{"\nĮveskite studento vardą\n"};
    string input;
    input_valid_string(input, prompt);
    if (input == "x")
        return -1;
    student->first_name = input;

    prompt = "\nĮveskite studento pavardę\n";
    input_valid_string(input, prompt);
    if (input == "x")
        return -1;
    student->last_name = input;


    unsigned max_scores_amount = 100;
    prompt = "\nAr norėtumėte sugeneruoti pažymius atsitiktinai?(y/n)\n";
        
    while (true) {
        
        input_valid_string(input, prompt);

        if (input == "y" || input == "taip") {
                
            cout << "\nPasirinkite kiek pažymių sugeneruoti(1/100)" << endl;
            unsigned amount_to_generate{};

            while (true) {

                cout << "> ";
                cin >> amount_to_generate;
                if (cin && amount_to_generate >= 1 && amount_to_generate <= 100) {

                    unsigned score;
                    cout << "\nSugeneruoti pažymiai\n";
                    for (unsigned i{}; i < amount_to_generate; i++) {
                            
                            student->scores.push_back(generate_random_score());
                            cout << student->scores.back() << " ";
                            student->scores.size() % 10 == 0 ? cout << '\n' : cout << "";
                    }
                    cout << endl;
                    break;
                }
                else {
                    cout << "\nĮveskite skaičių nuo 1 iki 100\n";  
                    cin.clear();
                    ignore_line();
                    continue;
                }
            }
            break;
        }
        else if (input == "n" || input == "ne") {

            unsigned score;
            cout << "\nVeskite studento pažymius (paskutinis turi būti egzamino pažymys).\n"
                << "Įveskite -1 jei norite baigti įvedimą\n"
                << "Pažymių kiekis neturi viršyti 10ies\n" << endl;

            while (true) {

                cout << "> ";
                cin >> score;
                if (cin && score >= 1 && score <= 10) {
                    student->scores.push_back(score);
                }
                else {
                    if (score == -1)
                        break;

                    cout << "\nĮveskite skaičių tarp 1 ir 10\n";
                    cin.clear();
                    ignore_line(); 
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

    return 0;
}

void print_students(const std::vector<Student> &students, unsigned option)
{
    std::cout << "\n" << std::setw(15) << std::left << "Pavardė" << std::setw(15) << std::left << "Vardas"
        << std::left << "Galutinis ";
    (option == 1) ? std::cout << "(Vid.)" : std::cout << "(Med).";
    cout << endl << endl;

    std::string temp(50, '-');
    cout << temp << endl;

    for (const auto student : students) {
        std::cout << std::setw(15) << std::left << student.last_name;
        std::cout << std::setw(15) << std::left << student.first_name;
        
        switch (option) {
            case 1:
                std::cout << std::setprecision(2) << student.score_average << std::endl << std::endl;
                break; 

            case 2:
                std::cout << std::setprecision(2) << student.score_median << std::endl << std:: endl;
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

bool compare(Student a, Student b)
{
    return a.last_name < b.last_name;
}

void sort_students(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), compare);
}
