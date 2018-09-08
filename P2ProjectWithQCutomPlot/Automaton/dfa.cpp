#include "dfa.h"

bool DFA::checkAlphabet(State* s) const
{
    std::vector<int> control = std::vector<int>(alphabet.length());
    int pos;
    for(int i = 0; i < s->nTrans(); i++)
    {
        pos = alphabet.find((*s)[i]->getInput());
        if(pos != -1)
            control[pos] ++;
        else
            return false;
    }
    for (unsigned int i = 0; i < alphabet.length(); i++)
    {
        if(control[i] != 1)
            return false;
    }
    return true;
}

bool DFA::check(State *s, const std::string &input) const
{
    if(input.length()!=0)
    {
        for(int i = 0; i < s->nTrans(); i++)
        {
            if((*s)[i]->getInput() == input[0])
                return check((*s)[i]->getDestination(), input.substr(1,input.length()-1));
        }
        return false;
    }
    if(s->isFinal())
        return true;
    else
        return false;
}

DFA::DFA(const std::string &alphabet, StateFA* starting): FA(starting), alphabet(alphabet)
{
}

std::string DFA::getAlphabet() const
{
    return alphabet;
}

void DFA::setAlphabet(const std::string &alphabet)
{
    this->alphabet = alphabet;
}

bool DFA::start(const std::string& input)
{
    for(std::list<StateFA*>::iterator i = states->begin(); i!= states->end(); i++)
    {
        if(!checkAlphabet(*i))
            return false;
    }
    return check(startingState,input);
}
