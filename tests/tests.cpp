#include "../headers/Student.hpp"
#include "catch.hpp"


TEST_CASE( "Pažymių palyginimas", "[compare_by_final_score]" ) {
    Student s1, s2;
    s1.set_final_score( 9 );
    s2.set_final_score( 5 );
    REQUIRE( compare_by_final_score( s1, s2 ) == false );
}


TEST_CASE( "Studentų failo nuskaitymas į vektorių", "[read_student_file]" ) {
    vector<Student> students; 
    read_student_file(students, "studentai1000.txt");

    CHECK_FALSE( students.empty() );
    REQUIRE_THROWS( read_student_file(students, "bet_koks_failas.txt") );
}


TEST_CASE( "Studentų konteinerio rašymas į failą", "[write_student_file]" ) {
    vector<Student> students; 
    read_student_file(students, "studentai1000.txt");

    write_student_file(students, "studentai_output.txt");
    std::ifstream student_file("studentai_output.txt");
    bool isEmpty = student_file.peek() == EOF;
    remove("studentai_output.txt");
    REQUIRE_FALSE( isEmpty );
}


TEST_CASE( "Studentų vidurkių apskaičiavimas", "[calculate_averages]" ) {
    string first_name = "Vardas";
    string last_name = "Pavarde";

    vector<unsigned> temp_scores;
    for (unsigned i{}; i < 5; i++) {
        temp_scores.push_back(generate_random_score());
    }
    unsigned test_score = generate_random_score();
    Student student{first_name, last_name, test_score, temp_scores};

    CHECK( student.get_has_final_score() == true );
    CHECK( student.get_final_score() != 0 );
}
