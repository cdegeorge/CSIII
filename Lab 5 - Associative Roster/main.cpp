// Reads in class rosters and prints a sorted list of all students and their classes
// Uses associative containers
// CS44001 Assignment 5 - Associative Class Roster
// Connor DeGeorge
// 2/17/20

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <map>

using std::ifstream;
using std::string; using std::pair;
using std::list; using std::map;
using std::cout; using std::endl;
using std::move; using std::make_pair;

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

    void printStudent() const;

    string getFirstName() const { return firstName_; }
    string getLastName() const { return lastName_; }

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
};

//void Student::printStudent() const {
//    cout << firstName_ << ", " << lastName_ << ": ";
//    for (string cls : classes_) {
//        cout << cls << " ";
//    }
//    cout << endl;
//}

// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);

// Printing a student
void printStudent(Student, list<string>);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses" << endl; exit(1);
    }

    // Map of students and the courses they belong to
    map<Student, list<string>> studentEntries;

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
            map<Student, list<string>>::iterator it;
            for (it = studentEntries.begin(); it != studentEntries.end(); ++it) {
                if (it->first.getFirstName() == studentsInRoster.getFirstName() &&
                    it->first.getLastName() == studentsInRoster.getLastName())
                {
                    it->second.push_back(className);
                    contains = true;
                    break;
                }
            }
            if (!contains) {
                Student s = Student(studentsInRoster.getFirstName(), studentsInRoster.getLastName());
                list<string> classes = { className };
                pair<Student, list<string>> p = make_pair(s, classes);
                
                studentEntries.insert(p);
            }
        }
    }

    // Sorting class lists and printing roster
    cout << "All Students" << endl;
    cout << "last name, first name: courses enrolled" << endl;

    map<Student, list<string>>::iterator it;
    for (it = studentEntries.begin(); it != studentEntries.end(); ++it) {
        it->second.sort();
        printStudent(it->first, it->second);
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

void printStudent(Student s, list<string> classes) {
    cout << s.getLastName() << ", " << s.getFirstName() << ": ";
    for (string c : classes)
        cout << c << " ";
    cout << endl;
}