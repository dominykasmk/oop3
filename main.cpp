#include "students.hpp"


int main()
{
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Įvesti studentų duomenis ranka\n"
            << "2 - Sugeneruoti 5 studentų sąrašus automatiškai\n"
            << "  21 - atlikti testus naudojant vektorių\n"
            << "  22 - atliiti naudojant list'ą\n"
            << "  23 - atlikti naudojant dek'ą\n"

            << endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 2 || option == 21 || option == 22 || option == 23)) {
                break;         
            }
            else {
                cout << "Pasirinkite ką nors iš meniu\n";
                cin.clear();
                ignore_line();
            }
        } 

        switch (option) {

            case 0:
                return 0;

            case 1: {

                vector<Student> students;
                cout << "\nJeigu norite baigti įvestį, įveskite 'x'\n";

                while (true) {

                    Student student;
                    if(input_student(&student) == -1) {
                        break;
                    }
                    
                    calculate_averages(student);
                    students.push_back(student);
                }

                if (students.empty()) {
                    cout << "\nNeįvedėte nei vieno studento.\n" << endl;
                    return 0;
                }

                cout << "\nPasirinkite ar norite apskaičiuoti vidurkį (1) ar medianą (2)?" << endl;
                unsigned option;
                while (true) {

                    cout << "> ";
                    cin >> option;
                    if (cin && (option == 1 || option == 2)) {
                        print_students(students, option);
                        break;
                    }
                    else {
                        cout << "Įveskite 1 arba 2\n";
                        cin.clear();
                        ignore_line();
                    }
                }

                break;
            }

            case 2: {

                unsigned student_amount = 100;
                unsigned scores_amount = 5;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    auto start = std::chrono::high_resolution_clock::now();
                    // creating
                    create_student_file(file_name, student_amount, scores_amount);
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;

                    cout << endl << student_amount << "ies studentų failo kūrimas užtruko: "<< diff.count() << "s\n";
                }
                break;
            }

            case 21: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    //reading
                    ifstream student_file;
                    vector<Student> students;

                    auto start = std::chrono::high_resolution_clock::now();

                    read_student_vector(students, file_name);

                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;

                    cout << endl << student_amount << "ies studentu vektoriaus nuskaitymas užtruko: "<< diff.count() << "s\n";

                    // sorting
                    std::sort(students.begin(), students.end(), compare_by_final_score);
                    
                    vector<Student> students_low;
                    vector<Student> students_high;

                    auto it = students.begin();
                    auto end = students.end();

                    for (; it != end; it++) {
                        
                        if ((*it).final_score_avg >= 5) {
                            break;
                        }

                        students_low.push_back(*it);
                    }

                    for (; it != end; it++) {
                        
                        students_high.push_back(*it);
                    }
                    students.clear();

                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;

                    cout << student_amount << "ies studentu vektoriaus rūšiavimas į dvi grupes užtruko: "<< diff.count() << "s\n";
                }

                break;
            }


            case 22: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    //reading
                    ifstream student_file;
                    std::list<Student> student_list;

                    auto start = std::chrono::high_resolution_clock::now();

                    read_student_list(student_list, file_name);

                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;

                    cout << endl << student_amount << "ies studentu list'o nuskaitymas iš failo užtruko: "<< diff.count() << "s\n";

                    // sorting
                    std::list<Student> students_low;
                    std::list<Student> students_high;
                    student_list.sort(compare_by_final_score);

                    auto beg = student_list.begin();
                    for (;;beg++) {
                        if ((*beg).final_score_avg >= 5)
                            break;

                        students_low.push_back(*beg);
                    }

                    for (; beg != student_list.end(); beg++) {
                        students_high.push_back(*beg);
                    } 

                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;

                    cout << student_amount << "ies studentu list'o rūšiavimas į dvi grupes užtruko: "<< diff.count() << "s\n";

                    students_low.clear();
                    students_high.clear();
                    student_list.clear();
                }

                break;
            }

            case 23: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    //reading
                    ifstream student_file;
                    std::deque<Student> student_deque;

                    auto start = std::chrono::high_resolution_clock::now();

                    read_student_deque(student_deque, file_name);

                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;

                    cout << endl << student_amount << "ies studentu deko nuskaitymas iš failo užtruko: "<< diff.count() << "s\n";

                    // sorting
                    std::deque<Student> students_low;
                    std::deque<Student> students_high;
                    std::sort(student_deque.begin(), student_deque.end(), compare_by_final_score);

                    auto beg = student_deque.begin();
                    for (;;beg++) {
                        if ((*beg).final_score_avg >= 5)
                            break;

                        students_low.push_back(*beg);
                    }

                    for (; beg != student_deque.end(); beg++) {
                        students_high.push_back(*beg);
                    }

                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;

                    cout << student_amount << "ies studentu deko rūšiavimas į dvi grupes užtruko: "<< diff.count() << "s\n";
                }

                break;
            }

            default:
                break;
        }
    }

    return 0;
}
