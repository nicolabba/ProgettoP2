#ifndef NFA_H
#define NFA_H

#include "fa.h"

class NFA : public FA
{
private:
    std::list<std::list<std::string>> chiusure;
    void updateChiusure();
    bool check(StatoFA*, std::string);
public:
    NFA(StatoFA* = nullptr);
    bool start(const std::string&);
};

#endif // NFA_H
