#include "dfa.h"

std::string DFA::getAlfabeto() const
{
    return alfabeto;
}

void DFA::setAlfabeto(const std::string &alfabeto)
{
    this->alfabeto = alfabeto;
}

DFA::DFA():alfabeto("")
{
}

DFA::DFA(const std::string &alfabeto): alfabeto(alfabeto)
{
}

bool DFA::checkAlfa(Stato* s)
{
    int *controllo = new int[alfabeto.length()];
    int pos;
    for(int i = 0; i < s->nTrans(); i++)
    {
        pos = alfabeto.find((*s)[i]);
        if(pos != -1)
            controllo[pos] ++;
        else
            return false;
    }
    for (int i = 0; i < alfabeto.length(); i++)
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
    }
    if(s->finale)
        return true;
    else
        return false;
}

bool DFA::start(std::string)
{
    for(std::list<Stato>::iterator i = stati.begin(); i!= stati.end(); i++)
    {
        if(!checkAlfa(&*i))
            return false;
    }
    return check(partenza,input);
}
