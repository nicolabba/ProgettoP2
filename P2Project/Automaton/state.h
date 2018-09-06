#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include "transition.h"

class Transition;
class State
{
private:
    std::string name;
    bool final;
protected:
    State(const std::string&,const bool& = false);
public:
    virtual int nTrans() = 0;
    virtual Transition* operator[](int) = 0;
    std::string getName();
    void rename(const std::string&);
    bool isFinal();
    void setFinal(bool);
};

#endif // STATE_H
