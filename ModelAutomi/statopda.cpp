#include "statopda.h"

StatoPDA::StatoPDA(const std::string & nome, const bool& finale):Stato(nome,finale)
{

}

TransizionePDA *StatoPDA::getTrans(StatoPDA * stato, const char & input, const char & head, const std::string& newHead)
{
    unsigned int j = 0;
    while(j<trans.size() && (trans[j].getDest() != stato || trans[j].getInput() != input ||
                             trans[j].getHead() != head || trans[j].getNewHead()[0] != newHead[0] ||
                             trans[j].getNewHead()[1] != newHead[1]))
        j++;
    if(j == trans.size())
        return nullptr;
    else
        return &trans[j];
}

void StatoPDA::add(StatoPDA * stato, const char& input, const char& head, const std::string& newHead)
{
    if(newHead.size() <= 1 || (newHead.size() == 2 && head != '/0' && newHead[0] != '/0')) //accetto: s/s, s/e, e/s, e/e, s/ss
        if(getTrans(stato,input,head,newHead) == nullptr)
        {
            trans.push_back(TransizionePDA(stato,input,head,newHead));
        }
}

void StatoPDA::remove(StatoPDA * stato, const char & input, const char & head, const std::string & newHead)
{
    bool eliminato = false;
    for(std::vector<TransizionePDA>::iterator j = trans.begin();  j != trans.end() && !eliminato; j++)
    {
        if(j->getDest() == stato && j->getInput() == input && j->getHead() == head && j->getNewHead() == newHead)
        {
            trans.erase(j);
            eliminato = true;
        }
    }
}

int StatoPDA::nTrans()
{
    return trans.size();
}

Transizione *StatoPDA::operator [](int i)
{
    return &trans[i];
}
