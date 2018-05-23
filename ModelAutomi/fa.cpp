#include "fa.h"

FA::FA(StatoFA *s):AbstractAutoma(s)
{

}

StatoFA *FA::getStato(const std::string& s)
{
    std::list<StatoFA>::iterator i = stati.begin();
    while(i != stati.end() && i->getNome() != s)
        i++;
    if (i == stati.end())
        return nullptr;
    else
        return &(*i);
}

StatoFA *FA::operator[](const std::string& s)
{
    return getStato(s);
}

void FA::addStato(const std::string& s)
{
        if(getStato(s) == nullptr)
            stati.push_back(StatoFA(s));
}

void FA::removeStato(const std::string& s)
{
    bool eliminato = false;
    for(std::list<StatoFA>::iterator i = stati.begin();  i != stati.end() && !eliminato; i++)
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

void FA::setStartingState(const std::string& s)
{
    partenza = getStato(s);
}
