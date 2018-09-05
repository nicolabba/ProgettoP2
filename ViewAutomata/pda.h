#ifndef PDA_H
#define PDA_H

#include "abstractautoma.h"
#include "statopda.h"

class PDA : public AbstractAutoma
{
private:
    std::list<StatoPDA*>* stati;
    char epsilon;
    std::list<std::list<std::string>*>* chiusure;
    void supportChiusure(std::list<std::string> * , Stato* );
    void updateChiusure();
    bool check(StatoPDA*, const std::string&, const std::string&);
public:
    PDA(char = '\0', StatoPDA * = nullptr);
    StatoPDA* getStato(const std::string &);
    StatoPDA* operator[](const std::string &);
    StatoPDA* operator[](int);
    int getNStati();
    void addStato(const std::string &, bool = false);
    void removeStato(const std::string &);
    void setStartingState(const std::string &);
    virtual ~PDA();
    void renameState(const std::string &,const std::string &);
    void addTransizione(const std::string &,const std::string &, char, char, std::string);
    bool start(const std::string &);
    char getEpsilon() const;
    void setEpsilon(char value);





public:
};

#endif // PDA_H
