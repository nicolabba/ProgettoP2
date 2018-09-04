#include "npda.h"

char NPDA::getEpsilon() const
{
    return epsilon;
}

void NPDA::setEpsilon(char value)
{
    epsilon = value;
}

void NPDA::supportChiusure(std::list<std::string> & curr, Stato* s)
{
    bool presente;
    for (int i = 0; i<s->nTrans(); i++)
    {
        if((*s)[i]->getInput() == epsilon)
        {
            presente = false;
            for(std::list<std::string>::iterator j = curr.begin(); j!=curr.end() && !presente; j++)
            {
                if(*j == (*s)[i]->getDest()->getNome())
                    presente = true;
            }
            if(!presente)
            {
                curr.push_back((*s)[i]->getDest()->getNome());
                supportChiusure(curr,(*s)[i]->getDest());
            }
        }
    }
}

void NPDA::updateChiusure()
{
    std::list<std::string> curr;
    chiusure.clear();
    for (std::list<StatoPDA>::iterator i = stati.begin(); i != stati.end(); i++)
    {
        curr = std::list<std::string>();
        curr.push_back(i->getNome());
        supportChiusure(curr,&*i);
        chiusure.push_back(curr);
    }
}



NPDA::NPDA(char epsilon, StatoPDA * partenza):PDA(partenza), epsilon(epsilon)
{

}

bool NPDA::check(StatoPDA * s, const std::string & input, const std::string& stack)
{
    std::string tempStack;
    TransizionePDA *tempTrans;
    std::list<StatoPDA> chiusuraCorr = std::list<StatoPDA>();
    for(std::list<std::list<std::string>>::iterator i = chiusure.begin(); i != chiusure.end(); i++)
    {
        if(i->front() == s->getNome())
        {
            for(std::list<std::string>::iterator j = i->begin(); j != i->end(); j++)
            {
                chiusuraCorr.push_back(*getStato(*j));
            }
        }
    }
    if(input.length() == 0)
    {
        if(stack == "")
            for(std::list<StatoPDA>::iterator i = chiusuraCorr.begin(); i != chiusuraCorr.end(); i++)
                if(i->isFinale())
                    return true;
    }
    else
    {
        for(std::list<StatoPDA>::iterator i = chiusuraCorr.begin(); i != chiusuraCorr.end(); i++)
        {
            for(int t = 0; t < i->nTrans(); t++)
            {
                tempTrans = static_cast<TransizionePDA*>((*i)[t]);
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

bool NPDA::start(const std::string & input)
{

    updateChiusure();
    if(partenza)
        return check(dynamic_cast<StatoPDA*>(partenza), input, "");
    else
        return false;
}
