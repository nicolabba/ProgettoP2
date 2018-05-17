#include "transizione.h"

bool Transizione::isNull()
{
    return (dest==nullptr && input == '\0');
}

Stato *Transizione::getDest()
{
    return dest;
}

char Transizione::getInput()
{
    return input;
}

Transizione::Transizione(Stato *s, char i):dest(s), input(i)
{

}
