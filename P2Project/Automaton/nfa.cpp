#include "nfa.h"

char NFA::getEpsilon() const
{
    return epsilon;
}

void NFA::setEpsilon(char value)
{
    epsilon = value;
}

void NFA::supportClosures(std::list<std::string> * curr, State* s)
{
    bool present;
    for (int i = 0; i<s->nTrans(); i++)
    {
        if((*s)[i]->getInput() == epsilon)
        {
            present = false;
            for(std::list<std::string>::iterator j = curr->begin(); j!=curr->end() && !present; j++)
            {
                if(*j == (*s)[i]->getDestination()->getName())
                    present = true;
            }
            if(!present)
            {
                curr->push_back((*s)[i]->getDestination()->getName());
                supportClosures(curr,(*s)[i]->getDestination());
            }
        }
    }
}

void NFA::updateClosures()
{
    std::list<std::string>* curr;
    closures->clear();
    for (std::list<StateFA*>::iterator i = states->begin(); i != states->end(); i++)
    {
        curr = new std::list<std::string>();
        curr->push_back((*i)->getName());
        supportClosures(curr,*i);
        closures->push_back(curr);
    }
}

bool NFA::check(StateFA* s, const std::string& input)
{
    std::list<StateFA> currentClosure = std::list<StateFA>();
    for(std::list<std::list<std::string>*>::iterator i = closures->begin(); i != closures->end(); i++)
    {
        if((*i)->front() == s->getName())
        {
            for(std::list<std::string>::iterator j = (*i)->begin(); j != (*i)->end(); j++)
            {
                currentClosure.push_back(*getState(*j));
            }
        }
    }
    if(input.length() == 0)
    {
        for(std::list<StateFA>::iterator i = currentClosure.begin(); i != currentClosure.end(); i++)
        {
            if(i->isFinal())
                return true;
        }
    }
    else
    {
        for(std::list<StateFA>::iterator i = currentClosure.begin(); i != currentClosure.end(); i++)
        {
            for(int t = 0; t < i->nTrans(); t++)
            {
                if((*i)[t]->getInput() == input[0])
                {
                    if(check(dynamic_cast<StateFA*>((*i)[t]->getDestination()),input.substr(1,input.length()-1)))
                        return true;
                }
            }
        }
    }
    return false;
}

NFA::NFA(char epsilon, StateFA * starting):FA(starting), epsilon(epsilon)
{
    closures = new std::list<std::list<std::string>*>();
}

bool NFA::start(const std::string& input)
{
    updateClosures();
    if(startingState)
        return check(dynamic_cast<StateFA*>(startingState), input);
    else
        return false;
}
