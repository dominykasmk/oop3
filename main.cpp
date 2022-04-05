#include "students.hpp"


int main()
{
    while(true) {

        unsigned option;
        cout << "\nPasirinkite\n"
            << "0 - baigti programą\n"
            << "1 - Nuskaityti studentų duomenis iš failo\n"
            << "2 - Įvesti studentų duomenis ranka\n" << endl;

        while (true) {
            cout << "> ";
            cin >> option;

            if (cin && (option == 0 || option == 1 || option == 2)) {
                break;         
            }
            else {
                cout << "Įveskite 1 arba 2\n";
                cin.clear();
                ignore_line();
            }
        } 

        switch (option) {

            case 0:
                return 0;

            case 1: {

                ifstream student_file;
                vector<Student> students;
                const string file_name = "kursiokai.txt";

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

                                unsigned score;
                                while (iss >> score) {
                                    student.scores.push_back(score);
                                }

                                calculate_averages(student);
                                students.push_back(student);
                        }
                        
                        cout << "\nPasirinkite ar norite apskaičiuoti vidurkį (1) ar medianą (2)?" << endl;
                        unsigned option;
                        while (true) {

                            cout << "> ";
                            cin >> option;
                            if (cin && (option == 1 || option == 2)) {
                                sort_students(students);
                                print_students(students, option);
                                break;
                            }
                            else {
                                cout << "Įveskite 1 arba 2\n";
                                cin.clear();
                                ignore_line();
                            }
                        }
                    }

                    student_file.close();
                }
                catch (string e) {
                    cout << "\nKlaida atidarinėjant failą\n" << endl;
                    continue;
                }

                break;
            }


            case 2: {

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

            default:
                break;
        }
    }

    return 0;
}
