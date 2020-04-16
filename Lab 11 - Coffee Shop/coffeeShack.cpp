// Implmentation of coffeeShack
// CS44001 Assignment 11 - Coffee Shack
// Connor DeGeorge
// 4/13/20

#include <iomanip>
#include "coffeeShack.hpp"

std::vector<Drink*> drinks;

void JuniorBarista::takeOrder(Customer* c) {
    char coffeeSize;
    std::cout << "Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
    std::cin >> coffeeSize;
    while (coffeeSize != 'l' && coffeeSize != 'm' && coffeeSize != 's') {
        std::cout << "Invalid size" << std::endl;
        std::cout << "Welcome to Coffee Shack, can I get you a [l]arge, [m]edium, or [s]mall coffee? ";
        std::cin >> coffeeSize;
    }

    Drink* drink;
    if (coffeeSize == 'l') drink = new Drink(DrinkType::large);
    else if (coffeeSize == 'm') drink = new Drink(DrinkType::medium);
    else drink = new Drink();

    char toppings;
    std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
    std::cin >> toppings;

    if (toppings != 'n') {
        std::cout << "Transfering your request to a Senior Barista" << std::endl;
        drinks.push_back(drink);
        Barista::takeOrder(c);
    }
    else {
        std::string name;
        std::cout << "Can I get your name? ";
        std::cin >> name;

        c->setName(name);
        c->setDrink(drink);
        orders_.insert(c);
        drinks.push_back(drink);
        
        std::string priceStr = std::to_string(drink->getPrice());
        priceStr = priceStr.substr(0, 4);
        std::cout << "That will be $" << priceStr << ", please." << std::endl;
    }
}

void SeniorBarista::takeOrder(Customer* c) {
    Drink* drink = drinks.back();
    drinks.pop_back();

    std::cout << "A Senior Barista is now handling your order" << std::endl;

    char toppings;
    std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
    std::cin >> toppings;
    while (toppings != 'n' && toppings != 'f') {
        if (toppings == 's') drink = new Sprinkles(drink);
        else if (toppings == 'c') drink = new Caramel(drink);
        else if (toppings == 'f') drink = new MilkFoam(drink);
        else if (toppings == 'i') drink = new Ice(drink);
        else std::cout << "Invalid input" << std::endl;

        std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
        std::cin >> toppings;
    }

    if (toppings == 'f') {
        std::cout << "Transfering your request to a Manager" << std::endl;
        drinks.push_back(drink);
        Barista::takeOrder(c);
    }
    else {
        std::string name;
        std::cout << "Can I get your name? ";
        std::cin >> name;

        c->setName(name);
        c->setDrink(drink);
        orders_.insert(c);
        drinks.push_back(drink);
        
        std::string priceStr = std::to_string(drink->getPrice());
        priceStr = priceStr.substr(0, 4);
        std::cout << "That will be $" << priceStr << ", please." << std::endl;
    }
}

void Manager::takeOrder(Customer* c) {
    Drink* drink = drinks.back();
    drinks.pop_back();

    std::cout << "A Manager is now handling your order and adding foam" << std::endl;
    drink = new MilkFoam(drink);

    char toppings;
    std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
    std::cin >> toppings;
    while (toppings != 'n') {
        if (toppings == 's') drink = new Sprinkles(drink);
        else if (toppings == 'c') drink = new Caramel(drink);
        else if (toppings == 'f') drink = new MilkFoam(drink);
        else if (toppings == 'i') drink = new Ice(drink);
        else std::cout << "Invalid input" << std::endl;

        std::cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot? ";
        std::cin >> toppings;
    }

    std::string name;
    std::cout << "Can I get your name? ";
    std::cin >> name;
    
    c->setName(name);
    c->setDrink(drink);
    orders_.insert(c);
    drinks.push_back(drink);

    std::string priceStr = std::to_string(drink->getPrice());
    priceStr = priceStr.substr(0, 4);
    std::cout << "That will be $" << priceStr << ", please." << std::endl;
}

void Barista::notifyCustomers() const {
    Drink* drink = drinks[0];
    int pos = drink->getName().find_last_of(',');
    std::cout << "A " << drink->getName().substr(0, pos) << " is ready" << std::endl;
    for (auto c : orders_)
        c->notify(drink);
    drinks.erase(drinks.begin());
}

void Customer::notify(Drink* drink) const {
    if (drink_ != nullptr && drink->getName() == drink_->getName())
        std::cout << name_ << " has retrieved their drink" << std::endl;
}