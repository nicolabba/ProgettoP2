#include "fa.h"

FA::FA(StatoFA *s)
{
    partenza = s;
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

StatoFA *FA::operator[](int val)
{
    int count = 0;
    for(std::list<StatoFA>::iterator i = stati.begin(); i != stati.end(); i++)
    {
        if(count == val)
            return &(*i);
        count++;
    }
    return nullptr;
}

int FA::getNStati()
{
    return stati.size();
}

void FA::addStato(const std::string& s, bool finale)
{
        if(getStato(s) == nullptr)
            stati.push_back(StatoFA(s,finale));
}

void FA::removeStato(const std::string& s)
{
    bool eliminato = false;
    for(std::list<StatoFA>::iterator i = stati.begin();  i != stati.end() && !eliminato; i++)
    {
        for(int j = 0; j < i->nTrans(); j++)
        {
            Transizione* temp = i->operator [](j);
            if(temp->getDest()->getNome() == s)
                i->remove(dynamic_cast<StatoFA*>(temp->getDest()), temp->getInput());
        }
    }
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

FA::~FA()
{

}

void FA::renameState(const std::string & oldName, const std::string & newName)
{
    StatoFA* s = nullptr;
    bool trovato = false;
    for(std::list<StatoFA>::iterator i = stati.begin(); i != stati.end() && !trovato; i++)
    {
        if(i->getNome() == newName)
            trovato = true;
        else if(i->getNome() == oldName)
            s = &(*i);
    }
    if(!trovato && s)
    {
        s->rename(newName);
    }
}

