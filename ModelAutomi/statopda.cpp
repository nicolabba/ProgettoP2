#include "statopda.h"

StatoPDA::StatoPDA(const std::string & nome, const bool& finale):Stato(nome,finale)
{

}

Transizione *StatoPDA::getTrans(StatoPDA * stato, const char & input, const char & head, char* newHead)
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

void StatoPDA::add(StatoPDA * stato, const char& input, const char& head, char* newHead)
{
    if(getTrans(stato,input,head,newHead) == nullptr)
    {
        trans.push_back(TransizionePDA(stato,input,head,newHead));
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
