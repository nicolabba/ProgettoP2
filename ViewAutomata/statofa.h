#ifndef STATOFA_H
#define STATOFA_H

#include "stato.h"
#include <string>
#include <vector>
#include "transizione.h"

class StatoFA : public Stato
{
private:
    std::vector<Transizione*> trans;
public:
    StatoFA(const std::string&, const bool& = false);
    Transizione* getTrans(StatoFA *, const char&);
    void add(StatoFA *, const char&);
    void remove(StatoFA *, const char&);
    int nTrans();
    Transizione *operator [](int);
};

#endif // STATOFA_H
