#include "students.hpp"


int main()
{

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

    return 0;
}
