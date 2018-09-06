#ifndef PDA_H
#define PDA_H

#include "abstractautomaton.h"
#include "statepda.h"

class PDA : public AbstractAutomaton
{
private:
    std::list<StatePDA*>* states;
    char epsilon;
    std::list<std::list<std::string>*>* closures;
    void supportClosures(std::list<std::string> * , State* );
    void updateClosures();
    bool check(StatePDA*, const std::string&, const std::string&);
public:
    PDA(char = '\0', StatePDA * = nullptr);
    StatePDA* getState(const std::string &);
    StatePDA* operator[](const std::string &);
    StatePDA* operator[](int);
    int getStatesNumber();
    void addState(const std::string &, bool = false);
    void removeState(const std::string &);
    void setStartingState(const std::string &);
    virtual ~PDA();
    void renameState(const std::string &,const std::string &);
    void addTransition(const std::string &,const std::string &, char, char, std::string);
    bool start(const std::string &);
    char getEpsilon() const;
    void setEpsilon(char);
};

#endif // PDA_H
