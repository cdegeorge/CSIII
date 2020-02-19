// Filters a vector of apples based on user input
// Uses multimaps and the upper_bound and lower_bound functions
// CS44001 Assignment 6 - Orange Sort
// Connor DeGeorge
// 2/24/20

#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <vector>
#include <deque>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;
using std::count_if; using std::find_if;
using std::max_element; using std::for_each;
using std::transform; using std::remove_if;
using std::remove_copy_if; using std::back_inserter;
using std::sort; using std::distance; using std::next;
using std::bind;
using namespace std::placeholders;

struct Apples {
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " << weight << endl; }
	void operator=(double newWeight) { this->weight = newWeight; }
};

bool belowMax(Apples& a, const double &maxWeight) {
	return a.weight < maxWeight;
}

int main() {
	const double minWeight = 8.;
	const double maxWeight = 3.;

	srand(time(nullptr));

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apples> crate(size);

	// assign random weight and color to apples in the crate
	generate(crate.begin(), crate.end(), [&]() -> Apples {
		Apples a;
		a.weight = minWeight +
			static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
		a.color = rand() % 2 == 1 ? "green" : "red";

		return a;
	});

	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;

	int cnt = count_if(crate.begin(), crate.end(), [&](Apples& a) -> bool {
		return a.weight > toFind;
	});

	cout << "There are " << cnt << " apples heavier than "
		<< toFind << " oz" << endl;

	cout << "at positions ";
	auto findIt = find_if(crate.begin(), crate.end(), [&](Apples& a) -> bool {
		return a.weight > toFind;
	});
	while (findIt != crate.end()) {
		int index = findIt - crate.begin();
		cout << index << ",";

		findIt = find_if(findIt + 1, crate.end(), [&](Apples& a) -> bool {
			return a.weight > toFind;
		});
	}
	cout << endl;

	auto maxIt = max_element(crate.begin(), crate.end(), [&](Apples& a, Apples& b) -> bool {
		return a.weight < b.weight;
	});
	cout << "Heaviest apple weighs: " << maxIt->weight << " oz" << endl;

	double sum = 0;
	for_each(crate.begin(), crate.end(), [&](Apples& a) -> void {
		sum += a.weight;
	});
	cout << "Total apple weight is: " << sum << " oz" << endl;

	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;

	transform(crate.begin(), crate.end(), crate.begin(), [&](Apples& a) -> double {
		return a.weight += toGrow;
	});

	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;

	auto remove = remove_if(crate.begin(), crate.end(), [&](Apples& a) -> bool {
		return a.weight < minAccept;
	});
	crate.erase(remove, crate.end()); // remove_if puts "removed" elements at back of vector
	cout << "removed " << size - crate.size() << " elements" << endl;

	sort(crate.begin(), crate.end(), [&](Apples a, Apples b) -> bool {
		return a.weight < b.weight;
	});

	// moving all red apples from crate to peck
	deque<Apples> peck;
	remove_copy_if(crate.begin(), crate.end(), back_inserter(peck), [&](Apples& a) -> bool {
		return a.color != "red"; // Copies is expression is false
	});
	auto removed = remove_if(crate.begin(), crate.end(), [&](Apples& a) -> bool { // Need to remove the copied elements from crate
		return a.color == "red";
	});
	crate.erase(removed, crate.end());

	cout << "apples in the create" << endl;
	for_each(crate.begin(), crate.end(), [&](Apples& a) -> void {
		a.print();
	});
	cout << endl;

	cout << "apples in the peck" << endl;
	for_each(peck.begin(), peck.end(), [&](Apples& a) -> void {
		a.print();
	});
	cout << endl;

	// prints every "space" apple in the peck
	const int space = 3;
	cout << "every " << space << "\'d apple in the peck" << endl;

	auto it = peck.cbegin();
	while (it != peck.cend()) {
		if ((distance(peck.cbegin(), it) + 1) % space == 0) {
			it->print();
		}

		it = next(it);
	}

	// putting all small green apples in a jam
	const double weightToJam = 10.0;
	double jamWeight = 0;
	int index = 0;

	auto below = bind(belowMax, _1, weightToJam);
	auto cntIt = crate.begin();
	while (index != count_if(crate.begin(), crate.end(), below)) {
		if (cntIt->weight < weightToJam) {
			jamWeight += cntIt->weight;
			++index;
		}
	}

	auto eraIt = remove_if(crate.begin(), crate.end(), below);
	crate.erase(eraIt, crate.end());

	cout << "Weight of jam is: " << jamWeight << endl;
}
