// Main usage of coffee shack
// CS44001 Assignment 11 - Coffee Shack
// Connor DeGeorge
// 4/13/20

#include <ctime>
#include <cmath>
#include "coffeeShack.hpp"

int main() {
	srand(time(nullptr));
	Barista* jb = new JuniorBarista(new SeniorBarista(new Manager));

	std::vector<Customer*> customers;
	int index = 0;
	while (index < 2) {					// Fill customers vector
		customers.push_back(new Customer(jb));
		++index;
	}
	
	int served = 0;
	for (Customer* c : customers) {		// Serve customers
		std::cout << "Next customer:" << std::endl;
		jb->takeOrder(c);
		int r = rand() % 2;
		if (r == 0) {					// Decide weather to take another order or make a drink
			jb->notifyCustomers();
			++served;
		}
	}
	//std::cout << "HIT" << std::endl;
	while (served < customers.size()) { // Serve remaining customers
		jb->notifyCustomers();
		++served;
	}

	std::cout << "All customers have been served" << std::endl;
}