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

    double score_average{};
    double score_median{};
};


bool validate_input(std::string input);
void input_valid_string(std::string &input, const std::string prompt);
void calculate_averages(Student &student);
void ignore_line();
int input_student(Student *student);
void print_students(const std::vector<Student> &students, unsigned option);
unsigned generate_random_score();
bool compare(Student a, Student b);
void sort_students(std::vector<Student> &students);

#endif
