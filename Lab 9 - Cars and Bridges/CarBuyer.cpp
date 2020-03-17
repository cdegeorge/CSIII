// Implementation of CarBuyer
// CS44001 Assignment 9 - Car Dealership
// Connor DeGeorge
// 3/30/20

#include <iostream>
#include <vector>
#include <array>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
    CarLot();

    Car* nextCar();
    int lotSize() { return cars4Sale_.size(); }

    // if a car is bought, requests a new one
    Car* buyCar(int index) {
        Car* bought = cars4Sale_[index];
        cars4Sale_[index] = factories_[rand() % factories_.size()]->requestCar();
        testDrive = 0;
        return bought;
    }

private:
    std::array<Car*, 10> cars4Sale_;
    vector<CarFactory*> factories_;

    int testDrive = 0;
};


CarLot::CarLot() {
    // creates 2 Ford factories and 2 Toyota factories 
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());
    factories_.push_back(new FordFactory());
    factories_.push_back(new ToyotaFactory());

    // Fill the lot with 10 cars
    for (int i = 0; i < lotSize(); ++i) {
        Car* car = factories_[rand() % factories_.size()]->requestCar();
        cars4Sale_[i] = car;
    }
}

Car* CarLot::nextCar() {
    //cout << testDrive;
    Car* car = cars4Sale_[testDrive];
    
    if (testDrive >= lotSize() - 1)
        testDrive = 0;
    else
        ++testDrive;
    
    return car;
}

CarLot* carLotPtr = nullptr; // global pointer instantiation


// test-drives a car
// buys it if Toyota of chosen model
void toyotaLover(CarLot& lot, int id) {
    static const std::array<std::string, 5>
        models = { "Corolla", "Camry", "Prius", "4Runner", "Yaris" };

    std::string wantedModel = models[rand() % models.size()];

    int index = 0;
    Car* toBuy = nullptr;
    while (index < lot.lotSize()) {
        Car* driving = lot.nextCar();

        if (driving->getMake() == "Toyota" && driving->getModel() == wantedModel) {
            toBuy = driving;
            break;
        }

        ++index;
    }

    cout << "Buyer " << id << "'s prefered car: Toyota " << wantedModel << endl;;
    if (toBuy != nullptr) {
        lot.buyCar(index);
        cout << "  found and purchased a " << toBuy->getMake() << " " << toBuy->getModel() << endl;
    }
    else {
        cout << "  Was unable to find their prefered car" << endl;
    }
}

// test-drives a car
// buys it if Ford of chosen model
void fordLover(CarLot& lot, int id) {
    static const std::array<std::string, 4>
        models = { "Focus", "Mustang", "Explorer", "F-150" };

    std::string wantedModel = models[rand() % models.size()];

    int index = 0;
    Car* toBuy = nullptr;
    while (index < lot.lotSize()) {
        Car* driving = lot.nextCar();

        if (driving->getMake() == "Ford" && driving->getModel() == wantedModel) {
            toBuy = driving;
            break;
        }

        ++index;
    }

    cout << "Buyer " << id << "'s prefered car: Ford " << wantedModel << endl;;
    if (toBuy != nullptr) {
        lot.buyCar(index);
        cout << "  found and purchased a " << toBuy->getMake() << " " << toBuy->getModel() << endl;
    }
    else {
        cout << "  Was unable to find their prefered car" << endl;
    }
}


int main() {
    CarLot lot = CarLot();

    for (int i = 0; i < 6; ++i) {
        if (rand() % 2 == 0)
            toyotaLover(lot, i);
        else
            fordLover(lot, i);
    }

    return 0;
}