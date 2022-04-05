#include "students.hpp"


int main()
{
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Įvesti studentų duomenis ranka\n"
            << "2 - Sugeneruoti ir apdorotu 5 studentų sąrašus automatiškai\n"<< endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 2 || option == 3)) {
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
                unsigned scores_amount = 20;
                string temp_file_name("studentai");
                for (int i{}; i < 5; i++) {
                    
                    student_amount *= 10;
                    const string file_name = temp_file_name + std::to_string(student_amount) + ".txt";

                    // creating
                    auto start = std::chrono::high_resolution_clock::now();
                    create_student_file(file_name, student_amount, scores_amount);
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;

                    cout << endl << endl <<student_amount << "ies studentų failą sukurti užtruko: " << diff.count() << "s\n";

                    //reading
                    ifstream student_file;
                    vector<Student> students;
                    read_student_file(students, file_name);
                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;

                    cout << student_amount << "ies studentu failo nuskaitymas užtruko: "<< diff.count() << "s\n";

                    // sorting
                    std::sort(students.begin(), students.end(), compare_by_final_score);
                    
                    vector<Student> students_low;
                    vector<Student> students_high;

                    auto it = students.begin();
                    auto end = students.end();

                    for (; it != end; it++) {
                        
                        if ((*it).score_average >= 5) {
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

                    cout << student_amount << "ies studentu failo rūšiavimas į dvi grupes užtruko: "<< diff.count() << "s\n";

                    // writing
                    write_student_file(students_low, "vargsiukai" + std::to_string(student_amount) + ".txt");
                    write_student_file(students_high, "kietekai" + std::to_string(student_amount) + ".txt");
                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;

                    cout << student_amount << "ies studentu failo rašymas į du failus užtruko: "<< diff.count() << "s\n";


                    diff = time - start;
                    cout << endl << student_amount << "ies studentų testas užtruko: " << diff.count() << "s\n";
                }

                break;
            }

            default:
                break;
        }
    }

    return 0;
}
