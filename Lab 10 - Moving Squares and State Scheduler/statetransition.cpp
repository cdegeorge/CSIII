// Class Implementation of Process and the different states
// CS44001 Assignment 10 - Adapter Moving Square
// Connor DeGeorge
// 4/6/20

#include "statetransition.hpp"

// Process definitions
Process::Process() : state_(New::instance()), id_(nextid_) { ++nextid_; }
void Process::admitted() { state_->admitted(this); }
void Process::schedulerDispatch() { state_->schedulerDispatch(this); }
void Process::interrupt() { state_->interrupt(this); }
void Process::eventWait() { state_->eventWait(this); }
void Process::eventCompletion() { state_->eventCompletion(this); }
void Process::exit() { state_->exit(this); }
string Process::report() { return "Process " + to_string(id_) + " is " + state_->report(); }
int Process::nextid_ = 0;

// Handles/behaviors
void New::admitted(Process* p) { changeState(p, Ready::instance()); }
void Ready::schedulerDispatch(Process* p) { changeState(p, Running::instance()); }
void Running::interrupt(Process* p) { changeState(p, Ready::instance()); }
void Running::eventWait(Process* p) { changeState(p, Waiting::instance()); }
void Running::exit(Process* p) { changeState(p, Terminated::instance()); }
void Waiting::eventCompletion(Process* p) { changeState(p, Ready::instance()); }