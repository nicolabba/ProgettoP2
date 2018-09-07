#ifndef ABSTRACTAUTOMATON_H
#define ABSTRACTAUTOMATON_H

#include "state.h"
#include <list>
#include <string>

class AbstractAutomaton
{
protected:
    State* startingState;
public:
    virtual bool start(const std::string&) = 0;
    virtual void addState(const std::string&, bool) = 0;
    virtual void removeState(const std::string&) = 0;
    virtual void setStartingState(const std::string&) = 0;
    virtual void renameState(const std::string&, const std::string&) = 0;
    State* getStartingState() const;
    //Stato* getStato(std::string);
    //Stato* operator [](std::string);
    virtual ~AbstractAutomaton();
};

#endif // ABSTRACTAUTOMATON_H
