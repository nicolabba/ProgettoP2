#ifndef ABSTRACTAUTOMA_H
#define ABSTRACTAUTOMA_H

#include "stato.h"
#include <list>
#include <string>

class AbstractAutoma
{
protected:
    Stato* partenza;
    AbstractAutoma(Stato* = nullptr);
public:
    virtual bool start(const std::string&) = 0;
    virtual void addStato(const std::string&) = 0;
    virtual void removeStato(const std::string&) = 0;
    virtual void setStartingState(const std::string&) = 0;
    //Stato* getStato(std::string);
    //Stato* operator [](std::string);
};

#endif // ABSTRACTAUTOMA_H
