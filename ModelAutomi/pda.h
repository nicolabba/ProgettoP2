#ifndef PDA_H
#define PDA_H

#include "abstractautoma.h"
#include "statopda.h"

class PDA : public AbstractAutoma
{
protected:
    std::list<StatoPDA> stati;
    PDA(StatoPDA * = nullptr);
public:
    StatoPDA* getStato(const std::string &);
    StatoPDA* operator[](const std::string &);
    virtual bool start(const std::string &) = 0;
    void addStato(const std::string &);
    void removeStato(const std::string &);
    void setStartingState(const std::string &);
    virtual ~PDA();
    void renameState(const std::string &,const std::string &);
};

#endif // PDA_H
