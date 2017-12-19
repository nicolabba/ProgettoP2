#include "grafico.h"

//MEMO: ricorda di cambiare idp con pointCollection

Grafico::Grafico() : idp(new vector<Punto>())
{

}

Grafico::Grafico(const Grafico& g) : idp(g.idp)
{

}

Grafico& Grafico::operator=(const Grafico& g)
{
    if(this != &g)
    {
        delete idp;
        idp = new vector<Punto>();
        for(unsigned int i = 0; i < g.idp -> size(); i++)
            idp -> push_back(g.idp->at(i));
    }
    return *this;
}

Grafico::~Grafico()
{
    delete idp;
}

Punto& Grafico::operator [](const int& i) const
{
    return idp->at(i);
}

long Grafico::size() const
{
    return idp -> size();
}

int Grafico::search(int x, int y) const
{
    Punto p(x,y);
    unsigned int tmp = 0;
    while(tmp < idp -> size() && !(idp->at(tmp) == p)) tmp++;
    if(tmp < idp -> size()) return tmp;
    return -1;
}

void Grafico::insert(int x, int y)
{
    int res = search(x,y);
    if(res != -1)
    {
        Punto p(x,y);
        idp -> push_back(x);
    }
}

void Grafico::remove(int x, int y)
{
    int res = search(x,y);
    if(res != -1)
    {
        idp ->erase(idp->begin() + res);
    }
}

long Grafico::getArea() const
{
    //MANCA L' AREA PERCHE' E' UN CASINO
    return 0;
}
