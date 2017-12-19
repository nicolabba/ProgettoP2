#include "colore.h"

bool ColoreRGB::checkType(const Colore &c) const
{
    return typeid(c) == typeid(const ColoreRGB&);
}
ColoreRGB():red(0),green(0),blue(0){}
ColoreRGB(unsigned int r,unsigned int g,unsigned int b)
{
    if(r>255)
        red = 255;
    else
        red = r;
    if(g>255)
        green = 255;
    else
        green = g;
    if(b>255)
        blue = 255;
    else
        blue = b;
}

ColoreRGB(const Colore &c)
{
    if(checkType(c))
    {
        ColoreRGB temp = static_cast<const ColoreRGB&>(c);
        ColoreRGB(temp.red,temp.green,temp.blue);
    }
}

ColoreRGB ColoreRGB::operator +(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreRGB temp = static_cast<const ColoreRGB&>(c);
        return ColoreRGB(red + temp.red, green + temp.green, blue + temp.blue);
    }
}

ColoreRGB ColoreRGB::operator -(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreRGB temp = static_cast<const ColoreRGB&>(c);
        return ColoreRGB(red - temp.red, green - temp.green, blue - temp.blue);
    }
}

ColoreRGB ColoreRGB::operator /(const Colore &c) const
{

    if(checkType(c))
    {
        ColoreRGB temp = static_cast<const ColoreRGB&>(c);
        return ColoreRGB((red + temp.red)/2, (green + temp.green)/2, (blue + temp.blue)/2);
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
    if(checkType(c))
    {
        ColoreRGB temp = static_cast<const ColoreRGB&>(c);
        return (red == temp.red && green == temp.green && blue == temp.blue);
    }
    return false;
}

bool ColoreXYZ::checkType(const Colore &c) const
{
    return typeid(c) == typeid(const ColoreXYZ&);
}

ColoreXYZ():x(0),y(0),z(0){}

ColoreXYZ(int _x, int _y, int _z)
{
    //aggiungere limiti
    x=_x;
    y=_y;
    z=_z;
}

ColoreXYZ(const Colore &c)
{
    if(checkType(c))
    {
        ColoreXYZ temp = static_cast<const ColoreXYZ&>(c);
        ColoreXYZ(temp.x,temp.y,temp.z);
    }
}

ColoreXYZ ColoreXYZ::operator +(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreXYZ temp = static_cast<const ColoreXYZ&>(c);
        return ColoreXYZ(x + temp.x, y + temp.y, z + temp.z);
    }
}

ColoreXYZ ColoreXYZ::operator -(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreXYZ temp = static_cast<const ColoreXYZ&>(c);
        return ColoreXYZ(x - temp.x, y - temp.y, z - temp.z);
    }
}

ColoreXYZ ColoreXYZ::operator /(const Colore &c) const
{

    if(checkType(c))
    {
        ColoreXYZ temp = static_cast<const ColoreXYZ&>(c);
        return ColoreXYZ((x + temp.x)/2, (y + temp.y)/2, (z + temp.z)/2);
    }
}
void ColoreXYZ::add(const Colore &c)
{
    *this = *this + c;
}
void ColoreXYZ::remove(const Colore &c)
{
    *this = *this - c;
}
void ColoreXYZ::media(const Colore &c)
{
    *this = *this / c;
}
ColoreXYZ::operator ==(const Colore &c)
{
    if(checkType(c))
    {
        ColoreXYZ temp = static_cast<const ColoreXYZ&>(c);
        return (x == temp.x && y == temp.y && z == temp.z);
    }
    return false;
}
