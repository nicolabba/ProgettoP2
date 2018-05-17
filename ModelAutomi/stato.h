#ifndef STATO_H
#define STATO_H

#include <vector>
#include <string>
#include "transizione.h"

class Transizione;
class Stato
{
private:
    std::string nome;
    bool finale;
    std::vector<Transizione> trans;
public:
    Stato(std::string n);
    void add(Stato*, char);
    void remove(Stato*,char);
    virtual Transizione *getTrans(Stato*, char);
    int nTrans();
    Transizione* operator[](int);
    std::string getNome();
    bool isFinale();
    void setFinale(bool);
};

#endif // STATO_H
