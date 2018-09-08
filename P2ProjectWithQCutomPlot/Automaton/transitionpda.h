#ifndef TRANSITIONPDA_H
#define TRANSITIONPDA_H

#include "transition.h"
#include "statepda.h"

class StatePDA;
class TransitionPDA : public Transition
{
private:
    char head;
    std::string newHead;
public:
    TransitionPDA(StatePDA *,char,char,const std::string&);
    char getHead() const;
    std::string getNewHead() const;
};

#endif // TRANSITIONPDA_H
