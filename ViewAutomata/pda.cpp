#include "pda.h"

PDA::PDA(StatoPDA *s)
{
    partenza = s;
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

StatoPDA *PDA::operator[](int val)
{
    int count = 0;
    for(std::list<StatoPDA>::iterator i = stati.begin(); i != stati.end(); i++)
    {
        if(count == val)
            return &(*i);
        count++;
    }
    return nullptr;
}


int PDA::getNStati()
{
    return stati.size();
}

void PDA::addStato(const std::string& s)
{
        if(getStato(s) == nullptr)
            stati.push_back(StatoPDA(s));
}

void PDA::removeStato(const std::string& s)
{
    bool eliminato = false;

    for(std::list<StatoPDA>::iterator i = stati.begin();  i != stati.end(); i++)
    {

        for(int j = 0; j < i->nTrans(); j++)
        {
            TransizionePDA* temp = static_cast<TransizionePDA*>(i->operator [](j));
            if(temp->getDest()->getNome() == s)
                i->remove(dynamic_cast<StatoPDA*>(temp->getDest()),temp->getInput(),temp->getHead(),temp->getNewHead());
        }
    }
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

PDA::~PDA()
{

}

void PDA::renameState(const std::string & oldName, const std::string & newName)
{
    StatoPDA* s = nullptr;
    bool trovato = false;
    for(std::list<StatoPDA>::iterator i = stati.begin(); i != stati.end() && !trovato; i++)
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
