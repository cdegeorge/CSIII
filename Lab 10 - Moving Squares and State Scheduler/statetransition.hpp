// Class definitions of Process and the different states
// CS44001 Assignment 10 - Adapter Moving Square
// Connor DeGeorge
// 4/6/20

#ifndef STATETRANSITION_HPP
#define STATETRANSITION_HPP

#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string; using std::to_string;

class State;

// context
class Process {
public:
    Process();

    void admitted();
    void schedulerDispatch();
    void interrupt();
    void eventWait();
    void eventCompletion();
    void exit();
    string report();
    Process* clone() { return new Process(); }

    // part of implementation of state pattern
    void changeState(State* s) { state_ = s; }
private:
    State* state_;
    int id_;
    static int nextid_;
};

// absract state
class State {
public:
    virtual void admitted(Process*) {}
    virtual void schedulerDispatch(Process*) {}
    virtual void interrupt(Process*) {}
    virtual void eventWait(Process*) {}
    virtual void eventCompletion(Process*) {}
    virtual void exit(Process*) {}
    virtual string report() = 0;

    void changeState(Process* p, State* s) { p->changeState(s); }
};

class New : public State {
public:
    static State* instance() {
        static State* onlyInstance = new New;
        return onlyInstance;
    }

    void admitted(Process*) override;
    string report() override { return "new"; }
private:
    New() {}
};


class Ready : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }

    void schedulerDispatch(Process*) override;
    string report() override { return "ready"; }
private:
    Ready() {}
};


class Running : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Running;
        return onlyInstance;
    }

    void interrupt(Process*) override;
    void eventWait(Process*) override;
    void exit(Process*) override;
    string report() override { return "running"; }
private:
    Running() {}
};

class Waiting : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Waiting;
        return onlyInstance;
    }

    void eventCompletion(Process*) override;
    string report() override { return "waiting"; }
private:
    Waiting() {}
};

class Terminated : public State {
public:
    static State* instance() {
        static State* onlyInstance = new Terminated;
        return onlyInstance;
    }
    string report() override { return "terminated"; }
private:
    Terminated() {}
};

#endif // STATETRANSITION_HPP