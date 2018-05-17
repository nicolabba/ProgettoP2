#include "nfa.h"

void supportChiusure(std::list<std::string> & curr, Stato* s)
{
    bool presente;
    for (int i = 0; i<s->nTrans(); i++)
    {
        if((*s)[i]->getInput() == '\0')
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

void NFA::updateChiusure()
{
    std::list<std::string> curr;
    chiusure = std::list<std::list<std::string>>();
    for (std::list<Stato>::iterator i = stati.begin(); i != stati.end(); i++)
    {
        curr = std::list<std::string>();
        curr.push_back(i->getNome());
        supportChiusure(curr,&*i);
        chiusure.push_back(curr);
    }
}

NFA::NFA():AbstractAutoma()
{
}

bool NFA::start(std::string input)
{
    updateChiusure();
    if(partenza)
        return check(partenza, input);
    else
        return false;
}

bool NFA::check(Stato* s, std::string input)
{
    std::list<Stato> chiusuraCorr = std::list<Stato>();
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
        for(std::list<Stato>::iterator i = chiusuraCorr.begin(); i != chiusuraCorr.end(); i++)
        {
            if(i->isFinale())
                return true;
        }
    }
    else
    {
        for(std::list<Stato>::iterator i = chiusuraCorr.begin(); i != chiusuraCorr.end(); i++)
        {
            for(int t = 0; t < i->nTrans(); t++)
            {
                if((*i)[t]->getInput() == input[0])
                {
                    if(check((*i)[t]->getDest(),input.substr(1,input.length()-1)))
                        return true;
                }
            }
        }
    }
    return false;
}
