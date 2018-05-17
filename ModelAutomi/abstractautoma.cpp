#include "abstractautoma.h"

void AbstractAutoma::removeStato(std::string s)
{
    bool eliminato = false;
    for(std::list<Stato>::iterator i = stati.begin();  i != stati.end() && !eliminato; i++)
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

AbstractAutoma::AbstractAutoma():partenza(nullptr)
{
}

void AbstractAutoma::addStato(std::string s)
{
    if(getStato(s) == nullptr)
        stati.push_back(Stato(s));
}

Stato* AbstractAutoma::getStato(std::string s)
{
    std::list<Stato>::iterator i = stati.begin();
    while(i != stati.end() && i->getNome() != s)
        i++;
    if (i == stati.end())
       return nullptr;
    else
       return &(*i);
}

Stato* AbstractAutoma::operator [](std::string s)
{
    return getStato(s);
}

void AbstractAutoma::setStartingState(std::string s)
{
    partenza = getStato(s);
}
