#include "transizione.h"

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
