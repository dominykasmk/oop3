#include "../headers/Student.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE( "Pažymių palyginimas", "[compare_by_final_score]" ) {
    Student s1, s2;
    s1.set_final_score( 9 );
    s2.set_final_score( 5 );
    REQUIRE( compare_by_final_score( s1, s2 ) == false );
}


TEST_CASE( "Studentų failo nuskaitymas į vektorių", "[read_student_file]" ) {
    vector<Student> students; 
    string file_name{"studentai1000.txt"};
    read_student_file(students, file_name);

    REQUIRE_FALSE( students.empty() );
    REQUIRE_THROWS( read_student_file(students, "bet_koks_failas.txt") );
}


TEST_CASE( "Studentų konteinerio rašymas į failą", "write_student_file" ) {
    vector<Student> students; 
    string file_name{"studentai1000.txt"};
    read_student_file(students, file_name);

    write_student_file(students, file_name);
    std::ifstream student_file;
    bool isEmpty = student_file.peek() == EOF;
    REQUIRE_FALSE( isEmpty );
}
