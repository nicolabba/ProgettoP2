#ifndef STATEPDA_H
#define STATEPDA_H

#include "state.h"
#include <vector>
#include <string>
#include "transitionpda.h"

class TransitionPDA;
class StatePDA : public State
{
private:
    std::vector<TransitionPDA*>* trans;
public:
    StatePDA(const std::string &, bool = false);
    TransitionPDA *getTrans(StatePDA*, char,char,const std::string&);
    void add(StatePDA*, char, char, const std::string&);
    void remove(StatePDA*,char, char, const std::string&);
    int nTrans() const;
    Transition *operator [](int);
};

#endif // STATEPDA_H
