#ifndef DFA_H
#define DFA_H

#include "abstractautoma.h"

class DFA : public AbstractAutoma
{
private:
    std::string alfabeto;
    bool checkAlfa(Stato *s);
    bool check(Stato *s,const std::string &input);
public:
    DFA();
    DFA(const std::string &alfabeto);
    bool start(std::string);
    std::string getAlfabeto() const;
    void setAlfabeto(const std::string &alfabeto);
};

#endif // DFA_H
