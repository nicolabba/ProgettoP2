#include "statofa.h"

StatoFA::StatoFA(const std::string & nome, const bool& finale):Stato(nome,finale)
{
    trans = new std::vector<Transizione*>();
}

Transizione *StatoFA::getTrans(StatoFA * stato, const char & input)
{
    std::vector<Transizione*>::iterator i;
    for(i = trans->begin(); i != trans->end() && ((*i)->getDest() != stato || (*i)->getInput() != input); i++);

    if(i == trans->end())
        return nullptr;
    else
        return (*i);
}

void StatoFA::add(StatoFA * stato, const char & input)
{
    if(getTrans(stato,input) == nullptr)
    {
        trans->push_back(new Transizione(stato,input));
    }
}

void StatoFA::remove(StatoFA * stato, const char & input)
{
    bool eliminato = false;
    for(std::vector<Transizione*>::iterator j = trans->begin();  j != trans->end() && !eliminato; j++)
    {
        if((*j)->getDest() == stato && (*j)->getInput() == input)
        {
            trans->erase(j);
            eliminato = true;
        }
    }
}

int StatoFA::nTrans()
{
    return trans->size();
}

Transizione *StatoFA::operator [](int i)
{
    return trans->at(i);
}

