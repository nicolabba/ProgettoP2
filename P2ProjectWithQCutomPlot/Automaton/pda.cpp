#include "pda.h"

PDA::PDA(char epsilon, StatePDA *s):epsilon(epsilon)
{
    startingState = s;
    states = new std::list<StatePDA*>();
    closures = new std::list<std::list<std::string>*>();
}

StatePDA *PDA::getState(const std::string& s) const
{
    std::list<StatePDA*>::iterator i = states->begin();
    while(i != states->end() && (*i)->getName() != s)
        i++;
    if (i == states->end())
        return nullptr;
    else
        return (*i);
}

StatePDA *PDA::operator[](const std::string& s)
{
    return getState(s);
}

StatePDA *PDA::operator[](int val)
{
    int count = 0;
    for(std::list<StatePDA*>::iterator i = states->begin(); i != states->end(); i++)
    {
        if(count == val)
            return (*i);
        count++;
    }
    return nullptr;
}


int PDA::getStatesNumber() const
{
    return states->size();
}

void PDA::addState(const std::string& s, bool final)
{
        if(getState(s) == nullptr)
            states->push_back(new StatePDA(s, final));
}

void PDA::removeState(const std::string& s)
{
    bool deleted = false;

    for(std::list<StatePDA*>::iterator i = states->begin();  i != states->end(); i++)
    {

        for(int j = 0; j < (*i)->nTrans(); j++)
        {
            TransitionPDA* temp = static_cast<TransitionPDA*>((*i)->operator [](j));
            if(temp->getDestination()->getName() == s)
                (*i)->remove(dynamic_cast<StatePDA*>(temp->getDestination()),temp->getInput(),temp->getHead(),temp->getNewHead());
        }
    }
    for(std::list<StatePDA*>::iterator i = states->begin();  i != states->end() && !deleted; i++)
    {
        if((*i)->getName() == s)
        {
            if(startingState->getName() == s)
                startingState = nullptr;
            states->erase(i);
            deleted = true;
        }
    }
}

void PDA::setStartingState(const std::string& s)
{
    startingState = getState(s);
}

PDA::~PDA()
{

}

void PDA::renameState(const std::string & oldName, const std::string & newName)
{
    StatePDA* s = nullptr;
    bool found = false;
    for(std::list<StatePDA*>::iterator i = states->begin(); i != states->end() && !found; i++)
    {
        if((*i)->getName() == newName)
            found = true;
        else if((*i)->getName() == oldName)
            s = (*i);
    }
    if(!found && s)
    {
        s->rename(newName);
    }
}

void PDA::addTransition(const std::string & from, const std::string & to, char input, char head, std::string newHead)
{
    StatePDA* fromState = getState(from);
    StatePDA* toState = getState(to);
    if (fromState && toState)
        fromState->add(toState,input,head,newHead);
}


char PDA::getEpsilon() const
{
    return epsilon;
}

void PDA::setEpsilon(char value)
{
    epsilon = value;
}

void PDA::supportClosures(std::list<std::string> * curr, State* s) const
{
    bool present;
    for (int i = 0; i<s->nTrans(); i++)
    {
        if((*s)[i]->getInput() == epsilon)
        {
            present = false;
            for(std::list<std::string>::iterator j = curr->begin(); j!=curr->end() && !present; j++)
            {
                if(*j == (*s)[i]->getDestination()->getName())
                    present = true;
            }
            if(!present)
            {
                curr->push_back((*s)[i]->getDestination()->getName());
                supportClosures(curr,(*s)[i]->getDestination());
            }
        }
    }
}

void PDA::updateClosures()
{
    std::list<std::string>* curr;
    closures->clear();
    for (std::list<StatePDA*>::iterator i = states->begin(); i != states->end(); i++)
    {
        curr = new std::list<std::string>();
        curr->push_back((*i)->getName());
        supportClosures(curr,*i);
        closures->push_back(curr);
    }
}


bool PDA::check(StatePDA * s, const std::string & input, const std::string& stack) const
{
    std::string tempStack;
    TransitionPDA *tempTrans;
    std::list<StatePDA*>* currentClosure = new std::list<StatePDA*>();
    for(std::list<std::list<std::string>*>::iterator i = closures->begin(); i != closures->end(); i++)
    {
        if((*i)->front() == s->getName())
        {
            for(std::list<std::string>::iterator j = (*i)->begin(); j != (*i)->end(); j++)
            {
                currentClosure->push_back(getState(*j));
            }
        }
    }
    if(input.length() == 0)
    {
        if(stack == "")
            for(std::list<StatePDA*>::iterator i = currentClosure->begin(); i != currentClosure->end(); i++)
                if((*i)->isFinal())
                    return true;
        for(std::list<StatePDA*>::iterator i = currentClosure->begin(); i != currentClosure->end(); i++)
        {
            for(int t = 0; t < (*i)->nTrans(); t++)
            {
                tempTrans = static_cast<TransitionPDA*>((*i)->operator [](t));
                if(tempTrans->getInput() == epsilon && tempTrans->getHead() == stack[0])
                {
                    tempStack = stack;
                    if(tempTrans->getHead() != epsilon)
                    {
                        tempStack = tempStack.substr(1,tempStack.length()-1);
                        if(tempTrans->getNewHead()[0] != epsilon)
                        {
                            tempStack = tempTrans->getNewHead() + tempStack;
                        }
                    }
                    else
                    {
                        if(tempTrans->getNewHead()[0] != epsilon)
                        {
                            tempStack = tempTrans->getNewHead()[0] + tempStack;
                        }
                    }
                    if(check(dynamic_cast<StatePDA*>(tempTrans->getDestination()),tempTrans->getInput()==epsilon?input:input.substr(1,input.length()-1),tempStack))
                        return true;
                }
            }
        }
    }
    else
    {
        for(std::list<StatePDA*>::iterator i = currentClosure->begin(); i != currentClosure->end(); i++)
        {
            for(int t = 0; t < (*i)->nTrans(); t++)
            {
                tempTrans = static_cast<TransitionPDA*>((*i)->operator [](t));
                if((tempTrans->getInput() == input[0] && tempTrans->getHead() == stack[0]) || tempTrans->getHead() == epsilon)
                {
                    tempStack = stack;
                    if(tempTrans->getHead() != epsilon)
                    {
                        tempStack = tempStack.substr(1,tempStack.length()-1);
                        if(tempTrans->getNewHead()[0] != epsilon) // !!!!!
                        {
                            tempStack = tempTrans->getNewHead() + tempStack;
                        }
                    }
                    else if(tempTrans->getNewHead().length() == 1)
                    {
                        if(tempTrans->getNewHead()[0] != epsilon) // !!!!!
                        {
                            tempStack = tempTrans->getNewHead()[0] + tempStack;
                        }
                    }
                    if(check(dynamic_cast<StatePDA*>(tempTrans->getDestination()),tempTrans->getInput()==epsilon?input:input.substr(1,input.length()-1),tempStack))
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

    updateClosures();
    if(startingState)
        return check(dynamic_cast<StatePDA*>(startingState), input, "");
    else
        return false;
}
