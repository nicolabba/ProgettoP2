#include "dfa.h"

bool DFA::checkAlfa(Stato* s)
{
    std::vector<int> controllo = std::vector<int>(alfabeto.length());
    int pos;
    for(int i = 0; i < s->nTrans(); i++)
    {
        pos = alfabeto.find((*s)[i]->getInput());
        if(pos != -1)
            controllo[pos] ++;
        else
            return false;
    }
    for (unsigned int i = 0; i < alfabeto.length(); i++)
    {
        if(controllo[i] != 1)
            return false;
    }
    return true;
}

bool DFA::check(Stato *s, const std::string &input)
{
    if(input.length()!=0)
    {
        for(int i = 0; i < s->nTrans(); i++)
        {
            if((*s)[i]->getInput() == input[0])
                return check((*s)[i]->getDest(), input.substr(1,input.length()-1));
        }
        return false;
    }
    if(s->isFinale())
        return true;
    else
        return false;
}

DFA::DFA(const std::string &alfabeto, StatoFA* partenza): FA(partenza), alfabeto(alfabeto)
{
}

std::string DFA::getAlfabeto() const
{
    return alfabeto;
}

void DFA::setAlfabeto(const std::string &alfabeto)
{
    this->alfabeto = alfabeto;
}

bool DFA::start(const std::string& input)
{
    for(std::list<StatoFA>::iterator i = stati.begin(); i!= stati.end(); i++)
    {
        if(!checkAlfa(&*i))
            return false;
    }
    return check(partenza,input);
}
