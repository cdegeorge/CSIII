// Reads in a file and shows how many times each word occurs
// CS44001 Assignment 2 - Word Count
// Connor DeGeorge
// 1/27/20

#include <fstream>
#include <string>
#include <cctype>
#include "WordList.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	WordList w;

	while (!file.eof()) {
		std::string line = "";
		std::getline(file, line);

		// Remove punctuation and add word to list
		std::string word = "";
		for (int i = 0; i < line.length(); i++) {
			char c = line[i];
			if ((isspace(c) || ispunct(c)) && !word.empty()){
				w.addWord(word);
				word = "";
			}
			else if (c != ' ') // Ensures no empty characters are appended
				word += tolower(c);
		}
	}
	w.print();
}