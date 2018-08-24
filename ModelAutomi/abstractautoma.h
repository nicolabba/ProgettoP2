#ifndef ABSTRACTAUTOMA_H
#define ABSTRACTAUTOMA_H

#include "stato.h"
#include <list>
#include <string>

class AbstractAutoma
{
protected:
    Stato* partenza;
public:
    virtual bool start(const std::string&) = 0;
    virtual void addStato(const std::string&) = 0;
    virtual void removeStato(const std::string&) = 0;
    virtual void setStartingState(const std::string&) = 0;
    virtual void renameState(const std::string&, const std::string&) = 0;
    Stato* getStartingState();
    //Stato* getStato(std::string);
    //Stato* operator [](std::string);
    virtual ~AbstractAutoma();
};

#endif // ABSTRACTAUTOMA_H
