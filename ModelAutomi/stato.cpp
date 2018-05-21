#include "stato.h"

Stato::Stato(std::string n):nome(n),finale(false)
{
    //trans = new std::list<Transizione>();
}

Transizione* Stato::getTrans(Stato* s, char i)
{
    unsigned int j = 0;
    while(j<trans.size() && (trans[j].getDest() != s || trans[j].getInput() != i))
        j++;
    if(j == trans.size())
        return nullptr;
    else
        return &trans[j];
}

int Stato::nTrans()
{
    return trans.size();
}

Transizione* Stato::operator[](int i)
{
    return &trans[i];
}

std::string Stato::getNome()
{
    return nome;
}

bool Stato::isFinale()
{
    return finale;
}

void Stato::setFinale(bool f)
{
    finale = f;
}

void Stato::add(Stato* s, char i)
{
    if(getTrans(s,i) == nullptr)
    {
        trans.push_back(Transizione(s,i));
    }
}

void Stato::remove(Stato* s, char i)
{
    bool eliminato = false;
    for(std::vector<Transizione>::iterator j = trans.begin();  j != trans.end() && !eliminato; j++)
    {
        if(j->getDest() == s && j->getInput() == i)
        {
            trans.erase(j);
            eliminato = true;
        }
    }
}

