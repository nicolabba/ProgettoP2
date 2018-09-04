#ifndef NFA_H
#define NFA_H

#include "fa.h"

class NFA : public FA
{
private:
    char epsilon;
    std::list<std::list<std::string>> chiusure;
    void supportChiusure(std::list<std::string> &, Stato*);
    void updateChiusure();
    bool check(StatoFA*, const std::string&);
public:
    NFA(char = '\0',StatoFA* = nullptr);
    bool start(const std::string&);
    char getEpsilon() const;
    void setEpsilon(char value);
};

#endif // NFA_H
