// Tests implementation of hashmap.hpp
// CS44001 Assignment 7 - Hash Container
// Connor DeGeorge
// 3/2/20

#include "hashmap.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::for_each;

int main() {
    int numBuckets = 101;
    hashmap<int, int> myHash;

    // Filling map with 50 elements
    cout << "Filling hashmap with 50 numbers" << endl;
    int index = 0;
    while (index < 50) {
        int a = rand() % 101;
        
        myHash.insert(make_pair(a, a * 2)); // Filling hashmap with number pairs
        ++index;
    }

    // Checking find with multiples of the same element
    auto x = myHash.find(100);
    if (x != nullptr)
        cout << "100 maps to " << x->second << endl;
    else
        cout << "cannot find 100 in map" << endl;

    cout << "Inserting 100 with the value 35..." << endl;
    auto y = myHash.insert(pair<int, int>(100, 35));

    if (y.second)
        cout << "Successfully inserted 100 with the value 35" << endl;
    else
        cout << "100 is already mapped to " << *y.first << endl;

    cout << "Inserting 100 with the value 60. Should not work..." << endl;
    y = myHash.insert(pair<int, int>(100, 60));

    if (y.second)
        cout << "Successfully inserted 100 with the value 60" << endl;
    else
        cout << "100 is already mapped to " << *y.first << endl;

    cout << "Inserting 101 to the end of the hashmap..." << endl;
    y = myHash.insert(make_pair(101, 756));

    if (y.second)
        cout << "Successfully inserted 101 with the value 756" << endl;
    else
        cout << "101 is already mapped to " << *y.first << endl;

    // Checking rehash grow - Should work
    cout << "Now doubling the size of the hashmap..." << endl;
    cout << "Old number: " << numBuckets << endl;
    
    myHash.rehash(numBuckets *= 2);

    cout << "New size: " << numBuckets << endl;

    // Making sure rehash does not shrink hashmap
    cout << "Now attempting to use rehash to shrink hashmap. This should not work..." << endl;
    cout << "Old size: " << numBuckets << endl;

    myHash.rehash(numBuckets / 2);

    cout << "New size: " << numBuckets << endl;

    cout << "Since we know 100 is in this list, let's remove it. The value of the next element should be 756..." << endl;

    auto e = myHash.erase(100);
    if (e.second)
        cout << "Successfully removed 100. The value of the next element is " << e.first->second << endl;
    else
        cout << "We were unable to remove 100 from the hashmap" << endl;

    cout << "Now let's try to remove the last element 101..." << endl;

    e = myHash.erase(101);
    if (e.second) {
        if (e.first == nullptr)
            cout << "Successfully removed the last element 101" << endl;
        else
            cout << "Removed 101 but the element after it is " << e.first->second << endl;
    }
    else
        cout << "We were unable to remove 101 from the hashmap" << endl;

    cout << "Finally, we will attempt to remove an element that does not exist, 1086..." << endl;
    e = myHash.erase(1086);

    if (e.second)
        cout << "Somehow, we removed 1086 from the hashmap" << endl;
    else
        cout << "We did not remove 1086 from the hashmap because it was not in there" << endl;

    return 0;
}