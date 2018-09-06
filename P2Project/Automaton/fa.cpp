#include "fa.h"

FA::FA(StateFA *s)
{
    startingState = s;
    states = new std::list<StateFA*>();
}

StateFA *FA::getState(const std::string& s)
{
    std::list<StateFA*>::iterator i = states->begin();
    while(i != states->end() && (*i)->getName() != s)
        i++;
    if (i == states->end())
        return nullptr;
    else
        return (*i);
}

StateFA *FA::operator[](const std::string& s)
{
    return getState(s);
}

StateFA *FA::operator[](int val)
{
    int count = 0;
    for(std::list<StateFA*>::iterator i = states->begin(); i != states->end(); i++)
    {
        if(count == val)
            return (*i);
        count++;
    }
    return nullptr;
}

int FA::getStatesNumber()
{
    return states->size();
}

void FA::addState(const std::string& s, bool final)
{
        if(getState(s) == nullptr)
            states->push_back(new StateFA(s,final));
}

void FA::removeState(const std::string& s)
{
    bool deleted = false;
    for(std::list<StateFA*>::iterator i = states->begin();  i != states->end() && !deleted; i++)
    {
        for(int j = 0; j < (*i)->nTrans(); j++)
        {
            Transition* temp = (*i)->operator [](j);
            if(temp->getDestination()->getName() == s)
                (*i)->remove(dynamic_cast<StateFA*>(temp->getDestination()), temp->getInput());
        }
    }
    for(std::list<StateFA*>::iterator i = states->begin();  i != states->end() && !deleted; i++)
    {
        if((*i)->getName() == s)
        {
            if(startingState->getName() == s)
                startingState = nullptr;
            states->erase(i);
            deleted = true;
        }
    }
}

void FA::setStartingState(const std::string& s)
{
    startingState = getState(s);
}

FA::~FA()
{

}

void FA::renameState(const std::string & oldName, const std::string & newName)
{
    StateFA* s = nullptr;
    bool found = false;
    for(std::list<StateFA*>::iterator i = states->begin(); i != states->end() && !found; i++)
    {
        if((*i)->getName() == newName)
            found = true;
        else if((*i)->getName() == oldName)
            s = (*i);
    }
    if(!found && s)
    {
        s->rename(newName);
    }
}

void FA::addTransition(const std::string & da, const std::string & a, char input)
{
    StateFA* fromState = getState(da);
    StateFA* toState = getState(a);
    if (fromState && toState)
        fromState->add(toState,input);
}

