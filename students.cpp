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
    double temp = 0.4 * student.score_average + 0.6 * student.test_score;
    student.final_score_avg = round(temp * 100) / 100;

    // Surikiuojam pažymius medianos apskaičiavimui
    std::sort (student.scores.begin(), student.scores.begin() + student.scores.size());

    
    if (student.scores.size() % 2 == 0) {
        student.score_median = (student.scores[(student.scores.size() - 1) / 2] + 
            student.scores[student.scores.size() / 2]) / 2.0;
            return;
    }
    student.score_median = student.scores[student.scores.size() / 2];
    temp = 0.4 * student.score_median + 0.6 * student.test_score;
    student.final_score_med = round(temp * 100) / 100;
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

                    student->test_score = student->scores.back();
                    student->scores.pop_back();

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
                    {
                        student->test_score = student->scores.back();
                        student->scores.pop_back();
                        break;
                    }

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
                std::cout << std::setprecision(2) << student.final_score_avg << std::endl << std::endl;
                break; 

            case 2:
                std::cout << std::setprecision(2) << student.final_score_med << std::endl << std:: endl
                    << std::endl << std:: endl;
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

bool compare_by_final_score(Student a, Student b)
{
    return a.final_score_avg < b.final_score_avg;
}

void sort_students(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), compare);
}


void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount)
{
    vector<Student> students_auto;
    
    for (int i{}; i < student_amount; i++) {
        Student student;

        student.first_name = "Vardas" + std::to_string(i + 1);
        student.last_name = "Pavarde" + std::to_string(i + 1);

        for (int i{}; i < scores_amount - 1; i++) {
            student.scores.push_back(generate_random_score());
        }
        student.test_score = generate_random_score();

        calculate_averages(student);
        students_auto.push_back(student);
    }

    std::ofstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            
            std::ostringstream ss;
            ss << std::setw(15) << std::left << "Pavarde"
                << std::setw(15) << std::left << "Vardas";

            for (int i{}; i < students_auto[0].scores.size() - 1; i++) {
                ss << std::setw(15) << std::left << "ND" + std::to_string(i + 1);
            }
            ss << std::setw(15) << std::left << "Egzaminas";
            ss << std::setw(15) << std::left << "Galutinis";
            ss << "\n";
            student_file << ss.str();

            for (auto &student : students_auto) {
                std::ostringstream ss;
                ss << std::setw(15) << std::left << student.last_name;
                ss << std::setw(15) << std::left << student.first_name;

                for (auto &score : student.scores) {
                    ss << std::setw(15) << std::left << score;
                }
                ss << std::setw(15) << std::left << std::setprecision(2) << student.test_score;
                ss << std::setw(15) << std::left << std::setprecision(2) << student.final_score_avg;
                ss << "\n"; 
                student_file << ss.str();
            }

            student_file.close();
        }
    }
    catch (string e) {
        std::cerr << "\nKlaida kuriant failą\n";
    }
}

void write_student_file(const std::vector<Student> &students, const std::string file_name)
{
    std::ofstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            
            std::ostringstream ss;
            ss << std::setw(15) << std::left << "Pavarde"
                << std::setw(15) << std::left << "Vardas";

            for (int i{}; i < students[0].scores.size() - 1; i++) {
                ss << std::setw(15) << std::left << "ND" + std::to_string(i + 1);
            }
            ss << std::setw(15) << std::left << "Egzaminas";
            ss << std::setw(15) << std::left << "Galutinis";
            ss << "\n";
            student_file << ss.str();

            for (auto &student : students) {
                std::ostringstream ss;
                ss << std::setw(15) << std::left << student.last_name;
                ss << std::setw(15) << std::left << student.first_name;

                for (auto &score : student.scores) {
                    ss << std::setw(15) << std::left << score;
                }
                ss << std::setw(15) << std::left << std::setprecision(4) << student.final_score_avg;
                ss << "\n"; 
                student_file << ss.str();
            }

            student_file.close();
        }
    }
    catch (string e) {
        std::cerr << "\nKlaida kuriant failą\n";
    }
}

void read_student_file(std::vector<Student> &students, const std::string file_name)
{
    ifstream student_file;
    try {
        student_file.open(file_name);

        if (student_file.fail())
            throw file_name;

        else if (student_file.is_open()) {
            string line;

            getline(student_file, line);
            while (getline(student_file, line)) {

                    istringstream iss(line);
                    Student student;
                    
                    iss >> student.last_name;
                    iss >> student.first_name;

                    double score;
                    while (iss >> score) {
                        student.scores.push_back(score);
                    }
                    student.final_score_avg = student.scores.back();
                    student.scores.pop_back();

                    student.test_score = student.scores.back();
                    student.scores.pop_back();

                    calculate_averages(student);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}
