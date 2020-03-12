// Logs functions into a text file
// CS44001 Assignment 8 - Logger
// Connor DeGeorge
// 3/16/20

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

class Logger {
public:
	~Logger();
	static Logger& instance() {
		static Logger l;
		return l;
	}

	void report(const std::string& str) { fout << str << std::endl; } // Logs to file
private:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	std::ofstream fout;
};


// Constructor
Logger::Logger() {
	fout.open("log.txt", std::fstream::out | std::fstream::app);
}

// Destructor
Logger::~Logger() {
	fout.flush();
	fout.close();
}

// Logs a random number
void randNum() {
	int r = rand() % 501;
	std::string str = "Random Number: " + std::to_string(r);
	Logger::instance().report(str);
}

// Logs a greeting
void greeting() {
	int r = rand() % 4;
	std::string greeting = "Greeting: ";

	switch (r) {
	case 0:
		greeting += "Hello!";
		break;
	case 1:
		greeting += "Howdy!";
		break;
	case 3:
		greeting += "Greetings!";
		break;
	default:
		greeting += "Hi.";
		break;
	}

	Logger::instance().report(greeting);
}

int main() {
	std::cout << "Running randNum..." << std::endl;
	randNum();
	randNum();
	randNum();

	std::cout << "Running greeting..." << std::endl;
	greeting();
	greeting();
	greeting();

	std::cout << "Closing logger..." << std::endl;
	return 0;
}