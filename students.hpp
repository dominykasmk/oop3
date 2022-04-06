#ifndef STUDENTS_HPP
#define STUDENTS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstring>
#include <vector>
#include <list>
#include <deque>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;


struct Student {
    string first_name;
    string last_name;

    vector<unsigned> scores;
    unsigned test_score{};

    double score_average{};
    double score_median{};

    double final_score_avg{};
    double final_score_med{};
};


bool validate_input(std::string input);
void input_valid_string(std::string &input, const std::string prompt);
void calculate_averages(Student &student);
void ignore_line();
int input_student(Student *student);
void print_students(const std::vector<Student> &students, unsigned option);
unsigned generate_random_score();
bool compare(Student a, Student b);
bool compare_by_final_score(Student a, Student b);
void sort_students(std::vector<Student> &students);
void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount);
void read_student_vector(std::vector<Student> &students, const std::string file_name);
void read_student_list(std::list<Student> &students, const std::string file_name);
void read_student_deque(std::deque<Student> &students, const std::string file_name);
void write_student_file(const std::vector<Student> &students, const std::string file_name);

#endif
