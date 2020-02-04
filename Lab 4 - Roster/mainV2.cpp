// Reads in class rosters and prints a sorted list of all students and their classes
// Uses class Student
// CS44001 Assignment 4 - Class Roster V2
// Connor DeGeorge
// 2/10/20

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    // move constructor, not really needed, generated automatically
    Student(Student&& org) :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}

    // force generation of default copy constructor
    Student(const Student& org) = default;

    void addClass(string cls) { classes_.push_back(cls); }
    void printStudent() const;

    string getFirstName() const { return firstName_; }
    string getLastName() const { return lastName_; }
    list<string> getClasses() const { return classes_; }

    // needed for unique() and for remove()
    friend bool operator== (Student left, Student right) {
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    // needed for sort()
    friend bool operator< (Student left, Student right) {
        return left.lastName_ < right.lastName_ ||
            (left.lastName_ == right.lastName_ &&
                left.firstName_ < right.firstName_);
    }
private:
    string firstName_;
    string lastName_;
    list<string> classes_;
};

void Student::printStudent() const {
    cout << firstName_ << ", " << lastName_ << ": ";
    for (string cls : classes_) {
        cout << cls << " ";
    }
    cout << endl;
}

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses" << endl; exit(1);
    }

    // list of courses of students
    list<Student> studentEntries;

    for (int i = 1; i <= argc - 1; ++i) {
        // Read each file into roster
        list<Student> roster;
        readRoster(roster, argv[i]);

        // Remove ".txt" from className;
        string className = argv[i];
        className = className.substr(0, className.find('.'));

        for (Student studentsInRoster : roster) {
            // Checking if student is already in studentEntries
            bool contains = false;
            for (Student& studentsInEnt : studentEntries) {
                if (studentsInEnt.getFirstName() == studentsInRoster.getFirstName() &&
                    studentsInEnt.getLastName() == studentsInRoster.getLastName()) {
                    studentsInEnt.addClass(className);
                    contains = true;
                    break;
                }
            }
            if (!contains) {
                Student s = Student(studentsInRoster.getFirstName(), studentsInRoster.getLastName());
                s.addClass(className);
                studentEntries.push_back(s);
            }
        }
    }

    studentEntries.sort();

    cout << "All Students" << endl;
    cout << "last name, first name: courses enrolled" << endl;
    for (Student student : studentEntries) {
        student.printStudent();
    }

    return 0;
}


void readRoster(list<Student>& roster, string fileName) {
    ifstream course(fileName);
    string first, last;
    while (course >> first >> last)
        roster.push_back(Student(first, last));
    course.close();
}