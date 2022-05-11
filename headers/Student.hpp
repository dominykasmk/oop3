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


/// Abstrakti žmogaus klasė
class Human {
    protected:
        std::string first_name;
        std::string last_name;

    public:

        /// Gražiną žmogaus vardą
        std::string get_first_name() const { return first_name; };

        /// Gražina žmogaus pavardę
        std::string get_last_name() const { return last_name; };
        
        /// Settina žmogaus vardą
        virtual void set_first_name(std::string name) = 0;

        /// Settina žmogaus pavardę
        virtual void set_last_name(std:: string name) = 0;
};


/// Studentų klasė kurį paveldi iš abstrakčios klasės Human
///
/// Ši klasė leidžia sukurti Studento objektą kuriam galima
/// priskirti vardą, pavardę, namų darbų pažymius, egzamino
/// pažymį ir galima apskaičiuoti galutinį pažymį
class Student : public Human {
    string first_name;
    string last_name;
   
    unsigned test_score{};
    vector<unsigned> scores;

    double score_average{};
    double score_median{};

    double final_score_avg{};
    double final_score_med{};

public:
    Student() = default;
    Student(const Student&) = default;
    Student& operator = (const Student &) = default;

    /// Konstruktorius kuriam galima pateikt visą eilutę su visais duomenimis kai nuskaitoma iš failo
    ///
    /// @param data Reference'as į duomenų string'ą
    Student(std::string& data);

    /// Konstruktorius kuriam galima pateikt iškart visus duomenis apie studentą
    ///
    /// @param first_name Vardas
    /// @param last_name Pavardė
    /// @param test_score Egzamino pažymys
    /// @param scores Pažymių vektorius
    Student(std::string first_name, std::string last_name, unsigned test_score, std::vector<unsigned> scores);

    ~Student() {};
    
    /// Vardo setteris
    /// @param first_name Studento vardas
    void set_first_name(std::string name) override { first_name = name; };

    /// Pavardės setteris
    /// @param last_name Studento pavardė
    void set_last_name(std::string name) override { last_name = name; };

    /// Nuskaito duomenis apie studentą iš string'o
    ///
    /// @param data Reference'as į duomenų string'ą
    void read_student(std::string& data);

    /// Išveda studento duomenis į stringstreamą
    ///
    /// @param ss stringstreamas į kurį bus išvesti duomenys
    void write_student(std::ostringstream& ss) const;

    /// Apskaičiuoja studento galutinį pažymį
    void calculate_averages();

    /// Išprintina duomenis apie studentą
    void print_student() const;

    /// Gražina pažymių skaičių
    unsigned get_score_amount() const;

    /// Gražina vardą
    string get_first_name() const;

    /// Gražina pavardę
    string get_last_name() const;

    /// Gražina galutinį pažymį
    double get_final_score() const;
    
    /// Gražiną pažymių vektorių
    const vector<unsigned>& get_scores() const;

    /// << operatoriaus perdengimas
    friend std::ostream& operator<< (std::ostream& out, const Student& student);

    /// >> operatoriaus perdengimas
    friend std::istream& operator>> (std::istream& in, Student& student);
};

/// Validuoja string'ą
void input_valid_string(std::string &input, const std::string prompt);

/// Ignoruoja nereikalingus duomenis buferyje
void ignore_line();

/// Išspausdina studentus
void print_students(const std::vector<Student> &students, unsigned option);

/// Palygina studentus pagal pavardę
bool compare(Student a, Student b);

/// Palygina studentus pagal galutinį pažymį
bool compare_by_final_score(Student a, Student b);

/// Sugeneruoja atsitiktinį pažymį
unsigned generate_random_score();

/// Surūšiuoja studentų vektorių
void sort_students(std::vector<Student> &students);

/// Sukuria studentų failą
void create_student_file(const std::string file_name, const unsigned student_amount, const unsigned scores_amount);

/// Nuskaito studentus iš failo į vektorių
void read_student_vector(std::vector<Student> &students, const std::string file_name);

/// Nuskaito studentus iš failo į list'ą
void read_student_list(std::list<Student> &students, const std::string file_name);

/// Nuskaito studentus iš failo į dek'ą
void read_student_deque(std::deque<Student> &students, const std::string file_name);

/// Išveda studentus į failą
void write_student_file(const std::vector<Student> &students, const std::string file_name);

#endif
