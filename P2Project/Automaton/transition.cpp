#include "transition.h"

State *Transition::getDestination()
{
    return destination;
}

char Transition::getInput()
{
    return input;
}

Transition::~Transition()
{

}

Transition::Transition(State *s, char i):destination(s), input(i)
{

}
