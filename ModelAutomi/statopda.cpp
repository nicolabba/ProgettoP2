#include "statopda.h"

StatoPDA::StatoPDA(const std::string &n):nome(n),finale(false){}

Transizione* StatoPDA::getTrans(Stato* s, char i, char h, char[2] nh)
{
  unsigned int j = 0;

  while(j<trans.size() && (trans[j].getDest() != s || trans[j].getInput() != i
        || trans[j].getHead() != h || trans[j].getNewHead()[0] != nh[0]
        || trans[j].getNewHead()[1] != nh[1]))
      j++;
  if(j == trans.size())
      return nullptr;
  else
      return &trans[j];
}


int StatoPDA::nTrans()
{
    return trans.size();
}

Transizione* StatoPDA::operator[](int i)
{
    return &trans[i];
}

std::string StatoPDA::getNome()
{
    return nome;
}

bool StatoPDA::isFinale()
{
    return finale;
}

void StatoPDA::setFinale(bool f)
{
    finale = f;
}


void StatoPDA::add(Stato* s,char i, char h, char[2] nh)
{
    if(getTrans(s,i, h, nh) == nullptr)
    {
        trans.push_back(TransizionePDA(s,i, h, nh));
    }
}
void StatoPDA::remove(Stato* s, char i, char h, char[2] nh)
{
    bool eliminato = false;
    for(std::vector<Transizione>::iterator j = trans.begin();  j != trans.end() && !eliminato; j++)
    {
        if(j->getDest() == s && j->getInput() == i
        && j->getHead() == h && j->getNewHead()[0] == nh[0]
        && j->getNewHead()[1] == nh[1])
        {
            trans.erase(j);
            eliminato = true;
        }
    }
}
