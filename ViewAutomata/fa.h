#ifndef FA_H
#define FA_H

#include "abstractautoma.h"
#include <list>
#include "statofa.h"

class FA : public AbstractAutoma
{
protected:
    std::list<StatoFA> stati;
    FA(StatoFA* = nullptr);
public:
    StatoFA* getStato(const std::string &);
    StatoFA* operator[](const std::string &);
    StatoFA* operator[](int);
    int getNStati();
    virtual bool start(const std::string &) = 0;
    void addStato(const std::string &);
    void removeStato(const std::string &);
    void setStartingState(const std::string &);
    virtual ~FA();
    void renameState(const std::string &,const std::string &);
};

#endif // FA_H
