// Draws a square of specified size, then resizes and redraws it
// CS44001 Assignment 10 - Adapter Moving Square
// Connor DeGeorge
// 4/6/20

#include <iostream>

using std::cout; using std::cin; using std::endl;

// base interface
class Figure {
public:
    virtual void draw() = 0;
    virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
    LegacyRectangle(int topLeftX,
        int topLeftY,
        int bottomRightX,
        int bottomRightY) :
        topLeftX_(topLeftX),
        topLeftY_(topLeftY),
        bottomRightX_(bottomRightX),
        bottomRightY_(bottomRightY) {}

    int getTopLeftX() { return topLeftX_; }
    int getTopLeftY() { return topLeftY_; }
    int getBottomRightX() { return bottomRightX_; }
    int getBottomRightY() { return bottomRightY_; }

    void oldDraw() {
        for (int i = 0; i < bottomRightY_; ++i) {
            for (int j = 0; j < bottomRightX_; ++j)
                if (i >= topLeftY_ && j >= topLeftX_)
                    cout << '*';
                else
                    cout << ' ';
            cout << endl;
        }
    }

    void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        topLeftX_ = topLeftX;
        topLeftY_ = topLeftY;
        bottomRightX_ = bottomRightX;
        bottomRightY_ = bottomRightY;
    }
private: // defining top/left and bottom/right coordinates 
    int topLeftX_;
    int topLeftY_;
    int bottomRightX_;
    int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
    private LegacyRectangle {
public:
    SquareAdapter(int size) : LegacyRectangle(0, 0, size, size) {};

    int size() { return getBottomRightX(); }

    void draw() override {
        oldDraw();
    }

    void resize(int newSize) {
        this->move(0, 0, newSize, newSize);
    }
};


int main() {
    int size = 0;
    cout << "Enter the size of the square: ";
    cin >> size;

    SquareAdapter square(size);
    square.draw();

    cout << "Enter a new size for the square: ";
    cin >> size;

    square.resize(size);
    square.draw();
}