#ifndef STATOPDA_H
#define STATOPDA_H

#include "stato.h"
#include <vector>
#include <string>
#include "transizionepda.h"

class TransizionePDA;
class StatoPDA : public Stato
{
private:
    std::vector<TransizionePDA> trans;
public:
    StatoPDA(const std::string &, const bool& = false);
    Transizione *getTrans(StatoPDA*, const char&,const char&,char[2]);
    void add(StatoPDA*, const char&, const char&, char[2]);
    void remove(StatoPDA*,const char&, const char&, char[2]);
    int nTrans();
    Transizione *operator [](int);
};

#endif // STATOPDA_H
