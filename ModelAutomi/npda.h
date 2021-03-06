#ifndef NPDA_H
#define NPDA_H

#include "pda.h"

class NPDA : public PDA
{
private:
    std::list<std::list<std::string>> chiusure;
    void supportChiusure(std::list<std::string> & , Stato* );
    void updateChiusure();
    bool check(StatoPDA*, const std::string&, const std::string&);
public:
    NPDA(StatoPDA* = nullptr);
    bool start(const std::string &);
};

#endif // NPDA_H
