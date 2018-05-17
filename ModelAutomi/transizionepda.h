#ifndef TRANSIZIONEPDA_H
#define TRANSIZIONEPDA_H

#include "transizione.h"

class TransizionePDA : public Transizione
{
private:
    char head;
    char newHead[2];
public:
    TransizionePDA(Stato *,char,char,char[2]);
};

#endif // TRANSIZIONEPDA_H
