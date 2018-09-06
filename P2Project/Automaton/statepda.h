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
    StatePDA(const std::string &, const bool& = false);
    TransitionPDA *getTrans(StatePDA*, const char&,const char&,const std::string&);
    void add(StatePDA*, const char&, const char&, const std::string&);
    void remove(StatePDA*,const char&, const char&, const std::string&);
    int nTrans();
    Transition *operator [](int);
};

#endif // STATEPDA_H
