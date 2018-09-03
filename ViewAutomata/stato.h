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
protected:
    Stato(const std::string&,const bool& = false);
public:
    virtual int nTrans() = 0;
    virtual Transizione* operator[](int) = 0;
    std::string getNome();
    void rename(const std::string&);
    bool isFinale();
    void setFinale(bool);
};

#endif // STATO_H
