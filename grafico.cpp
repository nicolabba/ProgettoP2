#include "grafico.h"
#include <algorithm>

//MEMO: ricorda di cambiare idp con pointCollection

Grafico::Grafico() : idp(new list<Punto>())
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
        idp = new list<Punto>();
        list<Punto>::iterator it;
        for(it = g.idp->begin(); it != g.idp->end(); ++it)
            idp->push_back(*it);;
    }
    return *this;
}

Grafico::~Grafico()
{
    delete idp;
}

long Grafico::size() const
{
    return idp -> size();
}

bool Grafico::search(const Punto& p) const
{
    /*
    questo metodo va bene ma secondo me è migliorabile
    perchè alla fine parliamo di una lista ordinata
    quindi in teoria possiamo fare binary search
*/
    auto it = std::find(idp->begin(),idp->end(),p); //find ritorna p se lo trova altrimenti ritorna idp->end()
    return *it == p;
}

void Grafico::insert(const Punto& p)
{    
    if(search(p))
    {
        list<Punto>::iterator it = idp->begin();
        while(it != idp->end() && p.getX() < it->getX()) it++;
        idp->insert(it,p); // it dovrebbe puntare alla posizione giusta in ogni caso
    }
}

void Grafico::remove(const Punto& p)
{
    if(search(p))
        idp->remove(p);
}

long Grafico::getArea() const
{
    //MANCA L' AREA PERCHE' E' UN CASINO
    return 0;
}
