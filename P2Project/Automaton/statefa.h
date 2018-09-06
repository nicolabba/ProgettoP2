#ifndef STATEFA_H
#define STATEFA_H

#include "state.h"
#include <string>
#include <vector>
#include "transition.h"

class StateFA : public State
{
private:
    std::vector<Transition*>* trans;
public:
    StateFA(const std::string&, const bool& = false);
    Transition* getTrans(StateFA *, const char&);
    void add(StateFA *, const char&);
    void remove(StateFA *, const char&);
    int nTrans();
    Transition *operator [](int);
};

#endif // STATEFA_H
