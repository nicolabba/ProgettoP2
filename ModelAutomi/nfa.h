#ifndef NFA_H
#define NFA_H

#include "abstractautoma.h"

class NFA : public AbstractAutoma
{
private:
    std::list<std::list<std::string>> chiusure;
    void updateChiusure();
    bool check(Stato*, std::string);
public:
    NFA();
    bool start(std::string);
};

#endif // NFA_H
