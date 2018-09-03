#ifndef DFA_H
#define DFA_H

#include "fa.h"

class DFA : public FA
{
private:
    std::string alfabeto;
    bool checkAlfa(Stato *s);
    bool check(Stato *s,const std::string &input);
public:
    DFA(const std::string& = "", StatoFA* = nullptr);
    std::string getAlfabeto() const;
    void setAlfabeto(const std::string &alfabeto);
    bool start(const std::string &);
};

#endif // DFA_H
