#ifndef NFA_H
#define NFA_H

#include "fa.h"

class NFA : public FA
{
private:
    char epsilon;
    std::list<std::list<std::string>*>* closures;
    void supportClosures(std::list<std::string> *, State*);
    void updateClosures();
    bool check(StateFA*, const std::string&);
public:
    NFA(char = '\0',StateFA* = nullptr);
    bool start(const std::string&);
    char getEpsilon() const;
    void setEpsilon(char value);
};

#endif // NFA_H
