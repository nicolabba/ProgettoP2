#include "transition.h"

State *Transition::getDestination() const
{
    return destination;
}

char Transition::getInput() const
{
    return input;
}

Transition::~Transition()
{

}

Transition::Transition(State *s, char i):destination(s), input(i)
{

}
