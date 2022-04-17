#include "headers/students.hpp"


int main()
{
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Sugeneruoti 5 studentų sąrašus automatiškai\n"
            << "  11 - atlikti testus naudojant vektorių\n"
            << "  12 - atliiti testus naudojant list'ą\n"
            << "  13 - atlikti testus naudojant dek'ą\n"

            << endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 11 || option == 12 || option == 13)) {
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

            case 11: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";
                    cout << endl << student_amount << " studentų\n";
                    {
                        vector<Student> students;
                        read_student_vector(students, file_name);

                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students.begin(), students.end(), compare_by_final_score);
                        
                        vector<Student> students_low;
                        vector<Student> students_high;

                        auto it = students.begin();
                        auto end = students.end();
                        while (it != end) {
                            if ((*it).final_score_avg < 5)
                                students_low.push_back(*it);
                            else
                                students_high.push_back(*it);

                            ++it;
                        }

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        cout << "rūšiavimas naudojant du naujus konteinerius užtruko: "<< diff.count() << "s\n";
                    }

                    {
                        vector<Student> students_high;
                        read_student_vector(students_high, file_name);
                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students_high.begin(), students_high.end(), compare_by_final_score);
                        vector<Student> students_low;

                        auto it = students_high.begin();
                        auto end = students_high.end();

                        for (; it != end; ++it) {
                            if ((*it).final_score_avg >= 5)
                                break;

                            students_low.push_back(*it);
                        }
                        students_high.erase(students_high.begin(), it);

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        auto stop = time;

                        cout << "rūšiavimas naudojant vieną papildomą konteinerį užtruko: "<< diff.count() << "s\n";

                    }
                }
                break;
            }

            case 12: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";
                    cout << endl << student_amount << " studentų\n";
                    {
                        list<Student> students;
                        read_student_list(students, file_name);

                        auto start = std::chrono::high_resolution_clock::now();
                        students.sort(compare_by_final_score);
                        
                        list<Student> students_low;
                        list<Student> students_high;

                        auto it = students.begin();
                        auto end = students.end();
                        while (it != end) {
                            if ((*it).final_score_avg < 5)
                                students_low.push_back(*it);
                            else
                                students_high.push_back(*it);

                            ++it;
                        }

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        cout << "rūšiavimas naudojant du naujus konteinerius užtruko: "<< diff.count() << "s\n";
                    }

                    {
                        list<Student> students_high;
                        read_student_list(students_high, file_name);
                        auto start = std::chrono::high_resolution_clock::now();
                        students_high.sort(compare_by_final_score);
                        vector<Student> students_low;

                        auto it = students_high.begin();
                        auto end = students_high.end();

                        for (; it != end; ++it) {
                            if ((*it).final_score_avg >= 5)
                                break;

                            students_low.push_back(*it);
                        }
                        students_high.erase(students_high.begin(), it);

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        auto stop = time;

                        cout << "rūšiavimas naudojant vieną papildomą konteinerį užtruko: "<< diff.count() << "s\n";

                    }
                }
                break;
            }

            case 13: {
                
                unsigned student_amount = 100;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";
                    cout << endl << student_amount << " studentų\n";
                    {
                        deque<Student> students;
                        read_student_deque(students, file_name);

                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students.begin(), students.end(), compare_by_final_score);
                        
                        deque<Student> students_low;
                        deque<Student> students_high;

                        auto it = students.begin();
                        auto end = students.end();
                        while (it != end) {
                            if ((*it).final_score_avg < 5)
                                students_low.push_back(*it);
                            else
                                students_high.push_back(*it);

                            ++it;
                        }

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        cout << "rūšiavimas naudojant du naujus konteinerius užtruko: "<< diff.count() << "s\n";
                    }

                    {
                        deque<Student> students_high;
                        read_student_deque(students_high, file_name);
                        auto start = std::chrono::high_resolution_clock::now();
                        std::sort(students_high.begin(), students_high.end(), compare_by_final_score);
                        deque<Student> students_low;

                        auto it = students_high.begin();
                        auto end = students_high.end();

                        for (; it != end; ++it) {
                            if ((*it).final_score_avg >= 5)
                                break;

                            students_low.push_back(*it);
                        }
                        students_high.erase(students_high.begin(), it);

                        auto time = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double> diff = time - start;
                        auto stop = time;

                        cout << "rūšiavimas naudojant vieną papildomą konteinerį užtruko: "<< diff.count() << "s\n";

                    }
                }
                break;
            }

            default:
                break;
        }
    }

    return 0;
}
