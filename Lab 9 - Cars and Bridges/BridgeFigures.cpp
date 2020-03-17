// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// CS44001 Assignment 9 - Bridge Figures
// Connor DeGeorge
// 3/30/20

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
    Fill(char fillChar, char borderChar) :fillChar_(fillChar), borderChar_(borderChar) {}
    virtual char getBorder() = 0;
    virtual char getInternal() = 0;
    virtual ~Fill() {}
protected:
    char fillChar_;
    char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
    Hollow(char borderChar) :Fill(' ', borderChar) {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return ' '; }
    ~Hollow() {}
};



// another concrete body
class Filled : public Fill {
public:
    Filled(char fillChar, char borderChar) :Fill(fillChar, borderChar) {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return fillChar_; }
    ~Filled() {}
};

class EnhancedFilled : public Fill {
public:
    EnhancedFilled() :Fill('#', '*') {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return fillChar_; }
    ~EnhancedFilled() {}
};

// abstract handle
class Figure {
public:
    Figure(int size, Fill* fill) : size_(size),
        fill_(fill) {}
    void changeFill(const Fill* fill) { fill_ = const_cast<Fill*>(fill); }

    virtual void draw() = 0;
    virtual ~Figure() {}
protected:
    int size_;
    Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
    Square(int size, Fill* fill) : Figure(size, fill) {}
    void draw() override;
};


void Square::draw() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j)
            if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
                cout << fill_->getBorder();
            else
                cout << fill_->getInternal();
        cout << endl;
    }
}


int main() {
    cout << "Hollow Square:" << endl;
    Figure* hollowUserBox = new Square(8, static_cast<Fill*>(new Hollow('#')));
    hollowUserBox->draw();

    cout << "\nFilled Square:" << endl;
    Figure* filledUserBox = new Square(8, static_cast<Fill*>(new Filled('#', '#')));
    filledUserBox->draw();

    cout << "\nChanging fill character:" << endl;
    filledUserBox->changeFill(new Filled('%', '#'));
    filledUserBox->draw();

    cout << "\nEnchanged Filled Square:" << endl;
    Figure* EFilledUserBox = new Square(8, static_cast<Fill*>(new EnhancedFilled()));
    EFilledUserBox->draw();

    return 0;
}