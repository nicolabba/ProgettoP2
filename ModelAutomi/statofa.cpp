#include "statofa.h"

StatoFA::StatoFA(const std::string & nome, const bool& finale):Stato(nome,finale)
{

}

Transizione *StatoFA::getTrans(StatoFA * stato, const char & input)
{
    unsigned int j = 0;
    while(j<trans.size() && (trans[j].getDest() != stato || trans[j].getInput() != input))
        j++;
    if(j == trans.size())
        return nullptr;
    else
        return &trans[j];
}

void StatoFA::add(StatoFA * stato, const char & input)
{
    if(getTrans(stato,input) == nullptr)
    {
        trans.push_back(Transizione(stato,input));
    }
}

void StatoFA::remove(StatoFA * stato, const char & input)
{
    bool eliminato = false;
    for(std::vector<Transizione>::iterator j = trans.begin();  j != trans.end() && !eliminato; j++)
    {
        if(j->getDest() == stato && j->getInput() == input)
        {
            trans.erase(j);
            eliminato = true;
        }
    }
}

int StatoFA::nTrans()
{
    return trans.size();
}

Transizione *StatoFA::operator [](int i)
{
    return &trans[i];
}

