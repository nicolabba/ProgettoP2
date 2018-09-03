#ifndef TRANSIZIONEPDA_H
#define TRANSIZIONEPDA_H

#include "transizione.h"
#include "statopda.h"

class StatoPDA;
class TransizionePDA : public Transizione
{
private:
    char head;
    std::string newHead;
public:
    TransizionePDA(StatoPDA *,char,char,const std::string&);
    char getHead();
    std::string getNewHead();
};

#endif // TRANSIZIONEPDA_H
