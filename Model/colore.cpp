#include "colore.h"

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
ColoreRGB::operator ==(const Colore &c)
{
    return (checkType(c) && Colore::operator ==(c));
}
