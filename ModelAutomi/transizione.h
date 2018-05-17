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
    bool isNull();
    Transizione(Stato* s, char i);
    Stato* getDest();
    char getInput();
};

#endif // TRANSIZIONE_H
