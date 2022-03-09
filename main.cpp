#include "students.hpp"


int main()
{

    unsigned option;
    cout << "\nPasirinkite\n"
        << "1 - Nuskaityti studentų duomenis iš failo\n"
        << "2 - Įvesti studentų duomenis ranka\n" << endl;

    while (true) {
        cout << "> ";
        cin >> option;

        if (cin && (option == 1 || option == 2)) {
            break;         
        }
        else {
            cout << "Įveskite 1 arba 2\n";
            cin.clear();
            ignore_line();
        }
    } 

    switch (option) {
        case 1: {

            ifstream student_file;
            vector<Student> students;

            student_file.exceptions( ifstream::badbit );
            try {
                student_file.open("kursiokai.txt");

                if (student_file.is_open()) {
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
            }
            catch (const ifstream::failure& e) {
                cout << "Klaida atidarinėjant failą\n" << endl;
                return 1;
            }
            student_file.close();

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


    return 0;
}
