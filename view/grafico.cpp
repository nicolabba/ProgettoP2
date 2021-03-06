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
    if(!search(p))
    {        
        list<Punto>::iterator it = idp->begin();
        while(it != idp->end() && p.getX() > it->getX()) it++;
        idp->insert(it,p); // it dovrebbe puntare alla posizione giusta in ogni caso
    }
}

void Grafico::remove(const Punto& p)
{
    if(search(p))
        idp->remove(p);
}

long Grafico::getAreaTri(const Punto & p1, const Punto & p2)
{
    Punto p3 = p1.getY()<p2.getY()?Punto(p1.getX(),p2.getY()):Punto(p2.getX(),p1.getY());
    return (p3.getDistance(p1) * p3.getDistance(p2))/2;
}

long Grafico::getAreaRet(const Punto & p1, const Punto & p2)
{
    return (p2.getX() - p1.getX()) * (p1.getY()<p2.getY()?p1.getY():p2.getY());
}

long Grafico::getPartialArea(const Punto & p1, const Punto & p2)
{
    return getAreaTri(p1,p2) + getAreaRet(p1,p2);
}

long Grafico::getArea() const
{
    long area = 0;
    int i = 0;
    auto it = idp->begin();
    while(i < size() -1)
    {
        area += getPartialArea(*it,*(std::next(it,1)));
        it++;
        i++;
    }
    return area;
}
