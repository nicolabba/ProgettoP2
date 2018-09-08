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
    StateFA(const std::string&, bool = false);
    Transition* getTrans(StateFA *, char) const;
    void add(StateFA *, char);
    void remove(StateFA *, char);
    int nTrans() const;
    Transition *operator [](int);
};

#endif // STATEFA_H
