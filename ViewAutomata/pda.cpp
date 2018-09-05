#include "pda.h"

PDA::PDA(char epsilon, StatoPDA *s):epsilon(epsilon)
{
    partenza = s;
    stati = new std::list<StatoPDA*>();
}

StatoPDA *PDA::getStato(const std::string& s)
{
    std::list<StatoPDA*>::iterator i = stati->begin();
    while(i != stati->end() && (*i)->getNome() != s)
        i++;
    if (i == stati->end())
        return nullptr;
    else
        return (*i);
}

StatoPDA *PDA::operator[](const std::string& s)
{
    return getStato(s);
}

StatoPDA *PDA::operator[](int val)
{
    int count = 0;
    for(std::list<StatoPDA*>::iterator i = stati->begin(); i != stati->end(); i++)
    {
        if(count == val)
            return (*i);
        count++;
    }
    return nullptr;
}


int PDA::getNStati()
{
    return stati->size();
}

void PDA::addStato(const std::string& s, bool finale)
{
        if(getStato(s) == nullptr)
            stati->push_back(new StatoPDA(s, finale));
}

void PDA::removeStato(const std::string& s)
{
    bool eliminato = false;

    for(std::list<StatoPDA*>::iterator i = stati->begin();  i != stati->end(); i++)
    {

        for(int j = 0; j < (*i)->nTrans(); j++)
        {
            TransizionePDA* temp = static_cast<TransizionePDA*>((*i)->operator [](j));
            if(temp->getDest()->getNome() == s)
                (*i)->remove(dynamic_cast<StatoPDA*>(temp->getDest()),temp->getInput(),temp->getHead(),temp->getNewHead());
        }
    }
    for(std::list<StatoPDA*>::iterator i = stati->begin();  i != stati->end() && !eliminato; i++)
    {
        if((*i)->getNome() == s)
        {
            if(partenza->getNome() == s)
                partenza = nullptr;
            stati->erase(i);
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
    for(std::list<StatoPDA*>::iterator i = stati->begin(); i != stati->end() && !trovato; i++)
    {
        if((*i)->getNome() == newName)
            trovato = true;
        else if((*i)->getNome() == oldName)
            s = (*i);
    }
    if(!trovato && s)
    {
        s->rename(newName);
    }
}

void PDA::addTransizione(const std::string & da, const std::string & a, char input, char head, std::string newHead)
{
    StatoPDA* daStato = getStato(da);
    StatoPDA* aStato = getStato(a);
    if (daStato && aStato)
        daStato->add(aStato,input,head,newHead);
}


char PDA::getEpsilon() const
{
    return epsilon;
}

void PDA::setEpsilon(char value)
{
    epsilon = value;
}

void PDA::supportChiusure(std::list<std::string> * curr, Stato* s)
{
    bool presente;
    for (int i = 0; i<s->nTrans(); i++)
    {
        if((*s)[i]->getInput() == epsilon)
        {
            presente = false;
            for(std::list<std::string>::iterator j = curr->begin(); j!=curr->end() && !presente; j++)
            {
                if(*j == (*s)[i]->getDest()->getNome())
                    presente = true;
            }
            if(!presente)
            {
                curr->push_back((*s)[i]->getDest()->getNome());
                supportChiusure(curr,(*s)[i]->getDest());
            }
        }
    }
}

void PDA::updateChiusure()
{
    std::list<std::string>* curr;
    chiusure->clear();
    for (std::list<StatoPDA*>::iterator i = stati->begin(); i != stati->end(); i++)
    {
        curr = new std::list<std::string>();
        curr->push_back((*i)->getNome());
        supportChiusure(curr,*i);
        chiusure->push_back(curr);
    }
}


bool PDA::check(StatoPDA * s, const std::string & input, const std::string& stack)
{
    std::string tempStack;
    TransizionePDA *tempTrans;
    std::list<StatoPDA*>* chiusuraCorr = new std::list<StatoPDA*>();
    for(std::list<std::list<std::string>*>::iterator i = chiusure->begin(); i != chiusure->end(); i++)
    {
        if((*i)->front() == s->getNome())
        {
            for(std::list<std::string>::iterator j = (*i)->begin(); j != (*i)->end(); j++)
            {
                chiusuraCorr->push_back(getStato(*j));
            }
        }
    }
    if(input.length() == 0)
    {
        if(stack == "")
            for(std::list<StatoPDA*>::iterator i = chiusuraCorr->begin(); i != chiusuraCorr->end(); i++)
                if((*i)->isFinale())
                    return true;
    }
    else
    {
        for(std::list<StatoPDA*>::iterator i = chiusuraCorr->begin(); i != chiusuraCorr->end(); i++)
        {
            for(int t = 0; t < (*i)->nTrans(); t++)
            {
                tempTrans = static_cast<TransizionePDA*>((*i)->operator [](t));
                if(tempTrans->getInput() == input[0] && (tempTrans->getHead() == stack[0] || tempTrans->getHead() == epsilon))
                {
                    tempStack = stack;
                    if(tempTrans->getHead() != epsilon)
                    {
                        tempStack = tempStack.substr(1,tempStack.length()-1);
                        if(tempTrans->getNewHead().length() != 0)
                        {
                            tempStack = tempTrans->getNewHead()[0] + tempStack;
                            if(tempTrans->getNewHead().length() == 2)
                                tempStack = tempTrans->getNewHead()[1] + tempStack;
                        }
                    }
                    else if(tempTrans->getNewHead().length() == 1)
                    {
                        tempStack = tempTrans->getNewHead()[0] + tempStack;
                    }
                    if(check(dynamic_cast<StatoPDA*>(tempTrans->getDest()),input.substr(1,input.length()-1),tempStack))
                        return true;
                    //delete tempTrans;
                }
            }
        }
    }
    return false;
}

bool PDA::start(const std::string & input)
{

    updateChiusure();
    if(partenza)
        return check(dynamic_cast<StatoPDA*>(partenza), input, "");
    else
        return false;
}
