#ifndef DFA_H
#define DFA_H

#include "abstractautoma.h"

class PDA : public AbstractAutoma
{
private:
    std::string stack;

public:
    PDA();
    override bool start(std::string);
    override void addStato(std::string);
    override void removeStato(std::string);
};

#endif // DFA_H
