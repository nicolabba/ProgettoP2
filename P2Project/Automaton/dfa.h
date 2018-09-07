#ifndef DFA_H
#define DFA_H

#include "fa.h"

class DFA : public FA
{
private:
    std::string alphabet;
    bool checkAlphabet(State *s) const;
    bool check(State *s,const std::string &input) const;
public:
    DFA(const std::string& = "", StateFA* = nullptr);
    std::string getAlphabet() const;
    void setAlphabet(const std::string &alphabet);
    bool start(const std::string &);
};

#endif // DFA_H
