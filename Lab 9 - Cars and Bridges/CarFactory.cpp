// Implementation of carFactory
// CS44001 Assignment 9 - Car Dealership
// Connor DeGeorge
// 3/30/20

#include <array>
#include <string>
#include "CarFactory.hpp"

// product methods

Ford::Ford() {
    make_ = "Ford";
    model_ = getRandomModel();
}

std::string Ford::getRandomModel() {
    static const std::array<std::string, 4>
        models = { "Focus", "Mustang", "Explorer", "F-150" };

    return models[rand() % models.size()];
}

Toyota::Toyota() {
    make_ = "Toyota";
    model_ = getRandomModel();
}

std::string Toyota::getRandomModel() {
    static const std::array<std::string, 5>
        models = { "Corolla", "Camry", "Prius", "4Runner", "Yaris" };

    return models[rand() % models.size()];
}

// ractory methods
Car* CarFactory::requestCar() {
    ++numCarsInProduction_;
    return makeCar();
}

Car* FordFactory::makeCar() {
    return new Ford();
}

Car* ToyotaFactory::makeCar() {
    return new Toyota();
}