#include "pda.h"

PDA::PDA(StatoPDA *s):AbstractAutoma(s)
{
}

StatoPDA *PDA::getStato(const std::string& s)
{
    std::list<StatoPDA>::iterator i = stati.begin();
    while(i != stati.end() && i->getNome() != s)
        i++;
    if (i == stati.end())
        return nullptr;
    else
        return &(*i);
}

StatoPDA *PDA::operator[](const std::string& s)
{
    return getStato(s);
}

void PDA::addStato(const std::string& s)
{
        if(getStato(s) == nullptr)
            stati.push_back(StatoPDA(s));
}

void PDA::removeStato(const std::string& s)
{
    bool eliminato = false;
    for(std::list<StatoPDA>::iterator i = stati.begin();  i != stati.end() && !eliminato; i++)
    {
        if(i->getNome() == s)
        {
            if(partenza->getNome() == s)
                partenza = nullptr;
            stati.erase(i);
            eliminato = true;
        }
    }
}

void PDA::setStartingState(const std::string& s)
{
    partenza = getStato(s);
}
