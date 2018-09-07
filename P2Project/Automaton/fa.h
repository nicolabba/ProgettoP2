#ifndef FA_H
#define FA_H

#include "abstractautomaton.h"
#include <list>
#include "statefa.h"

class FA : public AbstractAutomaton
{
protected:
    std::list<StateFA*>* states;
    FA(StateFA* = nullptr);
public:
    StateFA* getState(const std::string &) const;
    StateFA* operator[](const std::string &);
    StateFA* operator[](int);
    int getStatesNumber() const;
    virtual bool start(const std::string &) = 0;
    void addState(const std::string &, bool = false);
    void removeState(const std::string &);
    void setStartingState(const std::string &);
    virtual ~FA();
    void renameState(const std::string &,const std::string &);
    void addTransition(const std::string &,const std::string &, char);
};

#endif // FA_H
