#ifndef STATOPDA_H
#define STATOPDA_H

#include <vector>
#include <string>
#include "transizionepda.h"

class TransizionePDA;

class StatoPDA
{
private:
  std::string nome;
  bool finale;
  std::vector<TransizionePDA> trans;
public:
    StatoPDA(const std::string &n);
    void add(StatoPDA*, char, char, char[2]);
    void remove(StatoPDA*,char, char, char[2]);
    Transizione *getTrans(Stato*, char, char, char[2]);
    int nTrans();
    Transizione* operator[](int);
    std::string getNome();
    bool isFinale();
    void setFinale(bool);
};

#endif // STATO_H
