#include "statefa.h"

StateFA::StateFA(const std::string & name, bool final):State(name,final)
{
    trans = new std::vector<Transition*>();
}

Transition *StateFA::getTrans(StateFA * state, char input) const
{
    std::vector<Transition*>::iterator i;
    for(i = trans->begin(); i != trans->end() && ((*i)->getDestination() != state || (*i)->getInput() != input); i++);

    if(i == trans->end())
        return nullptr;
    else
        return (*i);
}

void StateFA::add(StateFA * state, char input)
{
    if(getTrans(state,input) == nullptr)
    {
        trans->push_back(new Transition(state,input));
    }
}

void StateFA::remove(StateFA * state, char input)
{
    bool deleted = false;
    for(std::vector<Transition*>::iterator j = trans->begin();  j != trans->end() && !deleted; j++)
    {
        if((*j)->getDestination() == state && (*j)->getInput() == input)
        {
            trans->erase(j);
            deleted = true;
        }
    }
}

int StateFA::nTrans() const
{
    return trans->size();
}

Transition *StateFA::operator [](int i)
{
    return trans->at(i);
}

