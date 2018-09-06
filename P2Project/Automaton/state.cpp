#include "state.h"

State::State(const std::string & n, const bool & f):name(n),final(f)
{

}

std::string State::getName()
{
    return name;
}

void State::rename(const std::string & newNome)
{
     name = newNome;
}

bool State::isFinal()
{
    return final;
}

void State::setFinal(bool f)
{
    final = f;
}


