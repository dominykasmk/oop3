#ifndef STUDENT_HPP
#define STUDENT_HPP

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
using std::list;
using std::deque;
using std::ifstream;
using std::istringstream;


class Student {
    string first_name;
    string last_name;
   
    unsigned test_score{};
    vector<unsigned> scores;

    double score_average{};
    double score_median{};

    double final_score_avg{};
    double final_score_med{};

public:
    Student() {};
    Student(std::string& data);
    Student(std::string first_name, std::string last_name, unsigned test_score, std::vector<unsigned> scores);
    void read_student(std::string& data);
    void write_student(std::ostringstream& ss) const;
    void calculate_averages();
    void print_student() const;
    unsigned get_score_amount() const;
    string get_first_name() const;
    string get_last_name() const;
    double get_final_score() const;
};


void input_valid_string(std::string &input, const std::string prompt);
void ignore_line();
void print_students(const std::vector<Student> &students, unsigned option);
bool compare(Student a, Student b);
bool compare_by_final_score(Student a, Student b);
unsigned generate_random_score();
void sort_students(std::vector<Student> &students);
void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount);
void read_student_vector(std::vector<Student> &students, const std::string file_name);
void read_student_list(std::list<Student> &students, const std::string file_name);
void read_student_deque(std::deque<Student> &students, const std::string file_name);
void write_student_file(const std::vector<Student> &students, const std::string file_name);

#endif
