#ifndef ABSTRACTAUTOMA_H
#define ABSTRACTAUTOMA_H

#include "stato.h"
#include <list>
#include <string>

class AbstractAutoma
{
protected:
    std::list<Stato> stati;
    Stato* partenza;
    AbstractAutoma();
public:
    virtual bool start(std::string) = 0;
    virtual void addStato(std::string);
    virtual void removeStato(std::string);
    Stato* getStato(std::string);
    Stato* operator [](std::string);
    void setStartingState(std::string);
};

#endif // ABSTRACTAUTOMA_H
