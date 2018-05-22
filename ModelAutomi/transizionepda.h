#ifndef TRANSIZIONEPDA_H
#define TRANSIZIONEPDA_H

#include "transizione.h"

class TransizionePDA : public Transizione
{
private:
    char head;
    char newHead[2];
public:
    TransizionePDA(StatoPDA *,char,char,char[2]);
    char getHead();
    char[2] getNewHead();
};

#endif // TRANSIZIONEPDA_H
