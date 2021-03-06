#ifndef TRANSIZIONE_H
#define TRANSIZIONE_H

#include "stato.h"

class Stato;
class Transizione
{
private:
    Stato* dest;
    char input;
public:
    Transizione(Stato* s, char i);
    Stato* getDest();
    char getInput();
    virtual ~Transizione();
};

#endif // TRANSIZIONE_H
