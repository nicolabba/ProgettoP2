#include "statepda.h"

StatePDA::StatePDA(const std::string & name, bool final):State(name,final)
{
    trans = new std::vector<TransitionPDA*>();
}

TransitionPDA *StatePDA::getTrans(StatePDA * state, char input, char head, const std::string& newHead)
{
    std::vector<TransitionPDA*>::iterator i;
    for(i = trans->begin(); i != trans->end() && ((*i)->getDestination() != state || (*i)->getInput() != input ||
                             (*i)->getHead() != head || (*i)->getNewHead() != newHead); i++);
    if(i == trans->end())
        return nullptr;
    else
        return (*i);
}

void StatePDA::add(StatePDA * state, char input, char head, const std::string& newHead)
{
    //if(newHead.size() <= 1 || (newHead.size() == 2 && head != '\0' && newHead[0] != '\0')) //accetto: s/s, s/e, e/s, e/e, s/ss
        if(getTrans(state,input,head,newHead) == nullptr)
        {
            trans->push_back(new TransitionPDA(state,input,head,newHead));
        }
}

void StatePDA::remove(StatePDA * state, char input, char head, const std::string & newHead)
{
    bool deleted = false;
    for(std::vector<TransitionPDA*>::iterator j = trans->begin();  j != trans->end() && !deleted; j++)
    {
        if((*j)->getDestination() == state && (*j)->getInput() == input && (*j)->getHead() == head && (*j)->getNewHead() == newHead)
        {
            trans->erase(j);
            deleted = true;
        }
    }
}

int StatePDA::nTrans() const
{
    return trans->size();
}

Transition *StatePDA::operator [](int i)
{
    return trans->at(i);
}
