#include "../headers/Student.hpp"

Student::Student(std::string& data)
{
    read_student(data);
}

Student::Student(std::string first_name, std::string last_name, unsigned test_score, std::vector<unsigned> scores)
    : first_name { first_name }, last_name { last_name }, test_score { test_score }, scores { scores }
{
}

void Student::read_student(std::string& data)
{
    istringstream iss(data);
    
    iss >> last_name;
    iss >> first_name;

    double score;
    while (iss >> score) {
        scores.push_back(score);
    }
    final_score_avg = scores.back();
    scores.pop_back();

    test_score = scores.back();
    scores.pop_back();

    calculate_averages();
}

void Student::print_student() const
{
        std::cout << std::setw(15) << std::left << last_name;
        std::cout << std::setw(15) << std::left << first_name;
        std::cout << std::setprecision(2) << final_score_avg << std::endl << std::endl;
        printf("%15s%15s%15.2lf", last_name.c_str(), first_name.c_str(), final_score_avg);
}

void Student::write_student(std::ostringstream& ss) const
{
    ss << std::setw(15) << std::left << last_name;
    ss << std::setw(15) << std::left << first_name;

    for (const auto& score : scores) {
        ss << std::setw(15) << std::left << score;
    }
    ss << std::setw(15) << std::left << std::setprecision(2) << test_score;
    ss << std::setw(15) << std::left << std::setprecision(2) << final_score_avg;
    ss << "\n"; 
}

unsigned Student::get_score_amount() const
{
    return scores.size();
}

std::string Student::get_first_name() const
{
    return first_name;
}

std::string Student::get_last_name() const
{
    return last_name;
}

double Student::get_final_score() const
{
    return final_score_avg;
}

const std::vector<unsigned>& Student::get_scores() const
{
    return scores;
}


std::ostream& operator<< (std::ostream& out, const Student& student)
{
    out << student.first_name << " " << student.last_name << "\n"
        << "Namų darbų pažymiai: ";
    
    for (const auto& score: student.scores) {
        out << score << " ";
    }
    out << "\n";

    out << "Egzaminas: " << student.test_score << "\n"
        << "Galutinis: " << student.final_score_avg << "\n\n";

    return out;
}

std::istream& operator>> (std::istream& in, Student& student)
{
    string prompt{"\nĮveskite studento vardą\n"};
    string input;
    input_valid_string(input, prompt);
    student.first_name = input;

    prompt = "\nĮveskite studento pavardę\n";
    input_valid_string(input, prompt);
    student.last_name = input;

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
                            
                            student.scores.push_back(generate_random_score());
                            cout << student.scores.back() << " ";
                            student.scores.size() % 10 == 0 ? cout << '\n' : cout << "";
                    }

                    student.test_score = student.scores.back();
                    student.scores.pop_back();

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
                    student.scores.push_back(score);
                }
                else {
                    if (score == -1)
                    {
                        student.test_score = student.scores.back();
                        student.scores.pop_back();
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

    return in;
}

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

void Student::calculate_averages()
{
    if (scores.empty()) {
        score_average = score_median = 0;
        return;
    }

    double average{};
    for (const auto score : scores) {
        average += score;
    }
    score_average = average / scores.size();
    double temp = 0.4 * score_average + 0.6 * test_score;
    final_score_avg = round(temp * 100) / 100;

    // Surikiuojam pažymius medianos apskaičiavimui
    std::sort (scores.begin(), scores.begin() + scores.size());

    
    if (scores.size() % 2 == 0) {
        score_median = (scores[(scores.size() - 1) / 2] + 
            scores[scores.size() / 2]) / 2.0;
            return;
    }
    score_median = scores[scores.size() / 2];
    temp = 0.4 * score_median + 0.6 * test_score;
    final_score_med = round(temp * 100) / 100;
}


void print_students(const std::vector<Student> &students, unsigned option)
{
    printf("\n%-15s%-15s%s", "Pavardė", "Vardas", "(Vid.)");
    cout << endl << endl;

    std::string temp(50, '-');
    cout << temp << endl;

    for (const auto& student : students) {
        student.print_student();
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
    return a.get_last_name() < b.get_last_name();
}

bool compare_by_final_score(Student a, Student b)
{
    return a.get_final_score() < b.get_final_score();
}

void sort_students(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), compare);
}

void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount)
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

            for (unsigned i{}; i < scores_amount - 1; i++) {
                ss << std::setw(15) << std::left << "ND" + std::to_string(i + 1);
            }
            ss << std::setw(15) << std::left << "Egzaminas";
            ss << std::setw(15) << std::left << "Galutinis";
            ss << "\n";
            student_file << ss.str();

            for (unsigned i{}; i < student_amount; i++) {

                string first_name = "Vardas" + std::to_string(i + 1);
                string last_name = "Pavarde" + std::to_string(i + 1);

                vector<unsigned> temp_scores;
                for (unsigned i{}; i < scores_amount - 1; i++) {
                    temp_scores.push_back(generate_random_score());
                }
                unsigned test_score = generate_random_score();
                
                Student student{first_name, last_name, test_score, temp_scores};
                student.calculate_averages();

                std::ostringstream ss;
                student.write_student(ss);
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

            for (unsigned i{}; i < students[0].get_score_amount(); i++) {
                ss << std::setw(15) << std::left << "ND" + std::to_string(i + 1);
            }
            ss << std::setw(15) << std::left << "Egzaminas";
            ss << std::setw(15) << std::left << "Galutinis";
            ss << "\n";
            student_file << ss.str();

            for (const auto &student : students) {
                std::ostringstream ss;
                student.write_student(ss);
                student_file << ss.str();
            }

            student_file.close();
        }
    }
    catch (string e) {
        std::cerr << "\nKlaida kuriant failą\n";
    }
}

void read_student_vector(std::vector<Student> &students, const std::string file_name)
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
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}

void read_student_list(std::list<Student> &students, const std::string file_name)
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
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}

void read_student_deque(std::deque<Student> &students, const std::string file_name)
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
                    Student student(line);
                    students.push_back(student);
            }
        }

        student_file.close();
    }
    catch (string e) {
        cout << "\nKlaida atidarinėjant failą\n" << endl;
    }
}
