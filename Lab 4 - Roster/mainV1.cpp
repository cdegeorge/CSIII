// Reads in class rosters and prints a sorted list of all students and their classes
// Uses a list of lists of strings
// CS44001 Assignment 4 - Class Roster V1
// Connor DeGeorge
// 2/10/20

#include <fstream>
#include <iostream>
#include <list>
#include <string>

using std::ifstream;
using std::string;
using std::list;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(list<string>& roster, string fileName);

// printing a list out
void print(const list<string>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses"
			<< endl; exit(1);
	}

	// list of courses of students
	list<list<string>> studentEntries;

	for (int i = 1; i <= argc - 1; ++i) {
		// Read each file into roster
		list<string> roster;
		readRoster(roster, argv[i]);

		// Remove ".txt" from className;
		string className = argv[i];
		className = className.substr(0, className.find('.'));

		for (string studentName : roster) {
			// Checking if student is already in studentEntries
			bool contains = false;
			for (list<string>& entry : studentEntries) {
				if (entry.front() == studentName) {
					entry.push_back(className);
					contains = true;
					break;
				}
			}
			if (!contains) {
				list<string> student;
				student.push_front(studentName);
				student.push_back(className);
				studentEntries.push_back(student);
			}
		}
	}

	studentEntries.sort();

	cout << "All Students" << endl;
	cout << "last name, first name: courses enrolled" << endl;
	for (list<string> student : studentEntries) {
		print(student);
	}

	return 0;
}

// reading in a file of names into a list of strings
void readRoster(list<string>& roster, string fileName) {
	ifstream course(fileName);
	string first, last;
	while (course >> first >> last)
		roster.push_back(move(last + ", " + first));
	course.close();
}

// printing a list out
void print(const list<string>& student) {
	for (const auto& str : student) {
		if (str == student.front())
			cout << str << ": ";
		else
			cout << str << " ";
	}
	cout << endl;
}