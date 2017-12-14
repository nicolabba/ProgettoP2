#include "colore.h"
Colore::Colore():prim1(), prim2(), prim3(){}
Colore::Colore(int _prim1, int _prim2, int _prim3):prim1(_prim1>MIN?_prim1<MAX?_prim1:MAX:MIN),
                                                   prim2(_prim2>MIN?_prim2<MAX?_prim2:MAX:MIN),
                                                   prim3(_prim3>MIN?_prim3<MAX?_prim3:MAX:MIN){}
Colore::Colore(const Colore &c)
{
    Colore(c.prim1,c.prim2,c.prim3);
}
Colore Colore::operator +(const Colore &c)
{
    return Colore(prim1 + c.prim1,prim2 + c.prim2,prim3 + c.prim3);
}
Colore Colore::operator -(const Colore &c)
{
    return Colore(prim1 - c.prim1,prim2 - c.prim2,prim3 - c.prim3);
}
Colore Colore::operator /(const Colore &c)
{
    return Colore((prim1 + c.prim1) / 2,(prim2 + c.prim2) / 2,(prim3 + c.prim3) / 2);
}
bool Colore::operator ==(const Colore& c)
{
    return (prim1 == c.prim1 && prim2 == c.prim2 && prim3 == c.prim3);
}
void Colore::add(const Colore &c)
{
    *this = *this + c;
}
void Colore::remove(const Colore &c)
{
    *this = *this + c;
}
void Colore::media(const Colore &c)
{
    *this = *this + c;
}
void Colore::setShade(int i, int amount)
{
    switch (i) {
    case 1:
        if(amount > MIN)
            if(amount < MAX)
                prim1 = amount;
            else
                prim1 = MAX;
        else
            prim1 = MIN;
        break;
    case 2:
        if(amount > MIN)
            if(amount < MAX)
                prim2 = amount;
            else
                prim2 = MAX;
        else
            prim2 = MIN;
        break;
    case 3:
        if(amount > MIN)
            if(amount < MAX)
                prim3 = amount;
            else
                prim3 = MAX;
        else
            prim3 = MIN;
        break;
    default:
        break;
    }
}
int Colore::getShade(int i) const
{
    switch (i) {
    case 1:
        return prim1;
        break;
    case 2:
        return prim2;
        break;
    case 3:
        return prim3;
        break;
    }
}

bool ColoreRGB::checkType(const Colore &c) const
{
    return typeid(c) == typeid(const ColoreRGB&);
}
ColoreRGB()
{
    Colore();
}

ColoreRGB(int red, int green, int blue)
{
    Colore(red,green,blue);
}

ColoreRGB(const Colore &c)
{
    if(checkType(c))
    {
        Colore(c);
    }
}

ColoreRGB ColoreRGB::operator +(const Colore &c) const
{
    if(checkType(c))
    {
        return static_cast<const ColoreRGB&>(Colore::operator +(c));
    }
}

ColoreRGB ColoreRGB::operator -(const Colore &c) const
{
    if(checkType(c))
    {
        return static_cast<const ColoreRGB&>(Colore::operator -(c));
    }
}

ColoreRGB ColoreRGB::operator /(const Colore &c) const
{
    if(checkType(c))
    {
        return static_cast<const ColoreRGB&>(Colore::operator /(c));
    }
}
void ColoreRGB::add(const Colore &c)
{
    *this = *this + c;
}
void ColoreRGB::remove(const Colore &c)
{
    *this = *this - c;
}
void ColoreRGB::media(const Colore &c)
{
    *this = *this / c;
}
int ColoreRGB::getShade(Primari p) const
{
    return Colore::getShade((int)p);
}
void ColoreRGB::setShade(Primari p, int amount)
{
    Colore::setShade((int)p, amount);
}
ColoreRGB::operator ==(const Colore &c)
{
    return (checkType(c) && Colore::operator ==(c));
}
