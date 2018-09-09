#include "grafico.h"
#include <algorithm>

Grafico::Grafico() : idp(new list<Punto*>())
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
        idp = new list<Punto*>();
        list<Punto*>::iterator it;
        for(it = g.idp->begin(); it != g.idp->end(); ++it)
            idp->push_back(*it);;
    }
    return *this;
}

Grafico::~Grafico()
{
    auto it = idp->begin();
    while(it != idp->end()){remove(*it);}
    delete idp;
}

int Grafico::size() const
{
    return idp -> size();
}

list<Punto*>* Grafico::clone() const
{
    list<Punto*> *tmp = new list<Punto*>();
    auto it = idp->begin();
    while(it != idp->end()){
        tmp->push_back(*it);
        it++;
    }
    return tmp;
}

bool Grafico::search(const Punto* p) const
{
    auto it = idp->begin();
    if(this->size() == 0) return false;
    while(it != idp->end() && !((*(*it)) == *p)) {it++;}
    if(it != idp->end()) return true;
    else return *(idp->back()) == *p;
}

bool Grafico::insert(const Punto* p)
{    
    if(!search(p))
    {
        auto it = idp->begin();
        while(it != idp->end() && p->getX() > (*it)->getX()) it++;
            idp->insert(it, new Punto(p->getX(),p->getY()));
        return true;
    }
    return false;
}

void Grafico::remove(Punto* p)
{
    if(search(p))
    {
        auto it = idp->begin();
        while(it != idp->end() && !((*(*it)) == *p)) {it++;}
        delete *it;
        idp->erase(it);
    }
}

long double Grafico::getAreaTri(const Punto * p1, const Punto * p2)
{
    Punto p3 = p1->getY()<p2->getY()? Punto(p1->getX(),p2->getY()) : Punto(p2->getX(),p1->getY());
    return (p3.getDistance(*p1) * p3.getDistance(*p2))/2;
}

long double Grafico::getAreaRet(const Punto * p1, const Punto * p2)
{
    if(p1->getY() == p2->getY())
        return abs(p2->getX() - p1->getX()) * abs(p2->getY());
    return -1;
}

long double Grafico::getPartialArea(const Punto * p1, const Punto * p2)
{    
    double partArea = 0;
    if(p1->getY() == p2->getY())
        partArea += getAreaRet(p1,p2);
    else
    {
        bool p1Closer;
        if(p1.getY < 0 || p2.getY < 0)
            p1Closet = p1->getY() > p2->getY();
        else
            p1Closer = p1->getY() < p2->getY();
        
        if (p1Closer)
            partArea += getAreaRet(p1,new Punto(p2->getX(), p1->getY()));
        else
            partArea += getAreaRet(new Punto(p1->getX(),p2->getY()),p2);
        partArea += getAreaTri(p1,p2);
    }
    return partArea;
}

long double Grafico::getArea() const
{
    long double area = 0;
    int i = 0;
    auto it = idp->begin();
    while(i < size()-1)
    {
        Punto* p1 = *it;
        Punto* p2 = *(std::next(it,1));
        if(p1->getY() * p2->getY() < 0){
            double x = (-(p2->getX()-p1->getX())*p1->getY())/(p2->getY()-p1->getY()) + p1->getX();
            area += getPartialArea(p1,new Punto(x,0));
            area += getPartialArea(new Punto(x,0),p2);
        }
        else
            area += getPartialArea(p1,p2);
        it++;
        i++;
    }
    return area;
}

QVector<double> Grafico::getXvalues() const
{
    vector<double> q;
    list<Punto*>::iterator it = idp->begin();
    while(it != idp->end()){
        q.push_back((*it) -> getX());
        it++;
    }

    return QVector<double>::fromStdVector(q);
}

QVector<double> Grafico::getYvalues() const
{
    vector<double> q;
    list<Punto*>::iterator it = idp->begin();
    while(it != idp->end()){
        q.push_back((*it) -> getY());
        it++;
    }
    return QVector<double>::fromStdVector(q);
}

double Grafico::getMaxX() const
{
    auto i = idp->back();
    return i->getX();
}
double Grafico::getMinX() const
{
    auto i = idp->front();
    return i->getX();
}
double Grafico::getMaxY() const
{
    auto it = idp -> begin();
    double max = (*it)->getY(), tmp;
    while(it != idp->end()){
        tmp = (*it) -> getY();
        if(tmp > max) max = tmp;
        it++;
    }
    return max;
}

long double Grafico::getLenght() const
{
    long double tmp = 0;
    int i = 0;
    auto it = idp -> begin();
    while(i < size() -1){
        tmp += (*it) -> getDistance(**it,**std::next(it,1));
        it++;
        i++;
    }
    return tmp;
}

Punto* Grafico::getMax() const
{
    auto it = idp->begin();
    Punto* p = new Punto((*it)->getX(), (*it)->getY());
    it++;
    while(it != idp->end()){
        if((*it)->getY() > p->getY()){
            delete p;
            p = new Punto((*it)->getX(), (*it)->getY());
        }
        it++;
    }
    return p;
}

Punto* Grafico::getMin() const
{
    auto it = idp->begin();
    Punto* p = new Punto((*it)->getX(), (*it)->getY());
    it++;
    while(it != idp->end()){
        if((*it)->getY() < p->getY()){
            delete p;
            p = new Punto((*it)->getX(), (*it)->getY());
        }
        it++;
    }
    return p;
}
