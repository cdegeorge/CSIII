// Filters a vector of fruit and prints the colors of the oranges
// Uses multimaps and the upper_bound and lower_bound functions
// CS44001 Assignment 6 - Orange Sort
// Connor DeGeorge
// 2/24/20

#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

int main() {
    srand(time(nullptr));
    multimap<Variety, string> tree;

    // Fill multimap
    int total = rand() % 100 + 1;
    int i = 0;
    while (i < total) {
        tree.insert({ static_cast<Variety>(rand() % 3), colors[rand() % 3] });
        ++i;
    }
     
    // Printing
    cout << "Colors of the oranges: ";
    for (auto f = tree.begin(); f != tree.end(); ++f)
        if (f->first == Variety::orange) cout << f->second << ", ";
    cout << endl;
}
