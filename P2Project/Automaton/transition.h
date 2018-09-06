#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

class State;
class Transition
{
private:
    State* destination;
    char input;
public:
    Transition(State* s, char i);
    State* getDestination();
    char getInput();
    virtual ~Transition();
};

#endif // TRANSITION_H
