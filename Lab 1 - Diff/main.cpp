// Compare two text files and outputs where in the file they differ from each other
// CS44001 Assignment 1 - Diff
// Connor DeGeorge
// 1/14/20

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Command must contain two arguments" << std::endl;
		return 1;
	}

	std::ifstream file1(argv[1]);
	std::ifstream file2(argv[2]);
	std::vector<std::string> file1Lines;
	std::vector<std::string> file2Lines;
	std::string file1String;
	std::string file2String;

	// getting each line of the first file and adding it into a vector
	while (!file1.eof()) {
		getline(file1, file1String);
		file1Lines.push_back(file1String);
	}

	// getting each line of the second file and adding it into a vector
	while (!file2.eof()) {
		getline(file2, file2String);
		file2Lines.push_back(file2String);
	}

	// Looping through the vectors and comparing them
	int size = file1Lines.size() < file2Lines.size() // Determine larger size and set to loop to that
		? file2Lines.size() : file1Lines.size();

	for (int i = 0; i < size; i++) {
		if (i < file1Lines.size())
			file1String = file1Lines[i];
		else
			file1String.clear();
		if (i < file2Lines.size())
			file2String = file2Lines[i];
		else
			file2String.clear();

		if (file1String != file2String) {
			int lineSize = file1String.length() < file2String.length() // Determine larger size and set to loop to that
				? file2String.length() : file1String.length();

			// Determining the index of the difference
			int index = 0;
			bool end = false;
			while (index < lineSize && !end) {
				if (file1String[index] != file2String[index]) {
					std::string arg1 = argv[1];
					std::string arg2 = argv[2];

					std::string out1String = arg1 + ": " + std::to_string(i) + ": " + file1String;
					std::string out2String = arg2 + ": " + std::to_string(i) + ": " + file2String;

					int printSize = out1String.length() < out2String.length() // Determine larger size and set to loop to that
						? out2String.length() : out1String.length();

					int diffPos = printSize - (lineSize - index); // Find the position of the difference
					std::string diffMarker(diffPos, ' ');
					diffMarker += '^';

					std::cout << out1String << std::endl;
					std::cout << out2String << std::endl;
					std::cout << diffMarker << std::endl;

					end = true;
				}
				index++;
			}
		}
	}

	file1.close();
	file2.close();
	return 0;
}
