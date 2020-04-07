// 
// CS44001 Assignment 11 - Coffee Shack
// Connor DeGeorge
// 4/13/20

#ifndef COFFEESHACK_HPP
#define COFFEESHACK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>

enum class DrinkType { small, medium, large };

class Drink {
public:
    Drink(DrinkType type = DrinkType::small) : type_(type) {
        if (type_ == DrinkType::small) {
            price_ = 1.00;
            name_ = "small coffee with ";
        }
        else if (type_ == DrinkType::medium) {
            price_ = 2.00;
            name_ = "medium coffee with ";
        }
        else if (type_ == DrinkType::large) {
            price_ = 3.00;
            name_ = "large coffee with ";
        }
    }
    virtual double getPrice() const { return price_; }
    virtual std::string getName() const { return name_; }
private:
    double price_;
    std::string name_;
    DrinkType type_;
};

class Sprinkles : public Drink {
public:
    Sprinkles(const Drink* wrapped) :
        wrapped_(wrapped) {}
    double getPrice() const override { return wrapped_->getPrice() + .50; }
    std::string getName() const override { return wrapped_->getName() + "sprinkles, "; }
private:
    const Drink *wrapped_;
};

class Caramel : public Drink {
public:
    Caramel(const Drink* wrapped) :
        wrapped_(wrapped) {}
    double getPrice() const override { return wrapped_->getPrice() + .20; }
    std::string getName() const override { return wrapped_->getName() + "caramel, "; }
private:
    const Drink* wrapped_;
};

class MilkFoam : public Drink {
public:
    MilkFoam(const Drink* wrapped) :
        wrapped_(wrapped) {}
    double getPrice() const override { return wrapped_->getPrice() + .40; }
    std::string getName() const override { return wrapped_->getName() + "foam, "; }
private:
    const Drink* wrapped_;
};

class Ice : public Drink {
public:
    Ice(const Drink* wrapped) :
        wrapped_(wrapped) {}
    double getPrice() const override { return wrapped_->getPrice() + .10; }
    std::string getName() const override { return wrapped_->getName() + "ice, "; }
private:
    const Drink* wrapped_;
};

class Customer;

class Barista {
public:
    Barista(Barista* successor = nullptr) : successor_(successor) {}
    virtual void takeOrder(Customer* c) {
        successor_->takeOrder(c);
    }
    void registerCustomer(Customer* c) { orders_.insert(c); }
    void deregisterCustomer(Customer* c) { orders_.erase(c); }
    void notifyCustomers() const;
protected:
    std::set<Customer*> orders_;
    Barista* successor_;
};

class Customer {
public:
    Customer(class Barista* b) :
        barista_(b) {
        barista_->registerCustomer(this);
    }
    void notify(Drink*) const;
    std::string getName() const { return name_; }
    void setName(std::string name) { name_ = name; }
    Drink* getdrink() const { return drink_; }
    void setDrink(Drink* drink) { drink_ = drink; }
private:
    std::string name_;
    Drink* drink_;
    Barista* barista_;
};

class JuniorBarista : public Barista {
public:
    JuniorBarista(Barista* successor = nullptr) :
        Barista(successor) {}
    void takeOrder(Customer* c) override;
};

class SeniorBarista : public Barista {
public:
    SeniorBarista(Barista* successor = nullptr) :
        Barista(successor) {}
    void takeOrder(Customer* c) override;
};

class Manager : public Barista {
public:
    Manager(Barista* successor = nullptr) :
        Barista(successor) {}
    void takeOrder(Customer* c) override;
};

#endif // !COFFEESHACK_HPP