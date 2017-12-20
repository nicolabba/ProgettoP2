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

ColoreXYZ(unsigned double _x, unsigned double _y, unsigned double _z)
{
    if(_x>1)
        x = 1;
    else
        x = _x;
    if(_y>1)
        y = 1;
    else
        y = _y;
    if(_z>1)
        z = 1;
    else
        z = _z;
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

ColoreXYZ ColoreRGB::toXYZ() const
{
    double r = this->red / 255.0;
    double g = this->green / 255.0;
    double b = this->blue / 255.0;

    r = ((r > 0.04045) ? pow((r + 0.055) / 1.055, 2.4) : (r / 12.92)) * 100.0;
    g = ((g > 0.04045) ? pow((g + 0.055) / 1.055, 2.4) : (g / 12.92)) * 100.0;
    b = ((b > 0.04045) ? pow((b + 0.055) / 1.055, 2.4) : (b / 12.92)) * 100.0;

    double x = r*0.4360747 + g*0.3850649 + b*0.1430804;
    double y = r*0.2225045 + g*0.7168786 + b*0.0606169;
    double z = r*0.0139322 + g*0.0971045 + b*0.7141733;

    return ColoreXYZ(x,y,z);
}

ColoreRGB ColoreXYZ::toRGB() const
{
    double r =this->x* 3.1338561 +this->y* -1.6168667 +this->z* -0.4906146;
    double g =this->x* -0.9787684 +this->y* 1.9161415 +this->z* 0.0334540;
    double b =this->x* 0.0719453 +this->y* -0.2289914 +this->z* 1.4052427;

    r = ((r > 0.0031308) ? (1.055*pow(r, 1 / 2.4) - 0.055) : (12.92*r)) * 255.0;
    g = ((g > 0.0031308) ? (1.055*pow(g, 1 / 2.4) - 0.055) : (12.92*g)) * 255.0;
    b = ((b > 0.0031308) ? (1.055*pow(b, 1 / 2.4) - 0.055) : (12.92*b)) * 255.0;

    return ColoreRGB(r,g,b);
}

bool ColoreCMY::checkType(const Colore &c) const
{
    return typeid(c) == typeid(const ColoreCMY&);
}

ColoreCMY():cyan(0),magenta(0),yellow(0){}

ColoreCMY(unsigned int c, unsigned int m, unsigned int y)
{
    if(c>255)
        cyan = 255;
    else
        cyan = c;
    if(m>255)
        magenta = 255;
    else
        magenta = m;
    if(y>255)
        yellow = 255;
    else
        yellow = y;
}

ColoreCMY(const Colore &c)
{
    if(checkType(c))
    {
        ColoreCMY temp = static_cast<const ColoreCMY&>(c);
        ColoreCMY(temp.cyan,temp.magenta,temp.yellow);
    }
}

ColoreCMY ColoreCMY::operator +(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreCMY temp = static_cast<const ColoreCMY&>(c);
        return ColoreCMY(cyan + temp.cyan, magenta + temp.magenta, yellow + temp.yellow);
    }
}

ColoreCMY ColoreCMY::operator -(const Colore &c) const
{
    if(checkType(c))
    {
        ColoreCMY temp = static_cast<const ColoreCMY&>(c);
        return ColoreCMY(cyan - temp.cyan, magenta - temp.magenta, yellow - temp.yellow);
    }
}

ColoreCMY ColoreCMY::operator /(const Colore &c) const
{

    if(checkType(c))
    {
        ColoreCMY temp = static_cast<const ColoreCMY&>(c);
        return ColoreCMY((cyan + temp.cyan)/2, (magenta + temp.magenta)/2, (yellow + temp.yellow)/2);
    }
}
void ColoreCMY::add(const Colore &c)
{
    *this = *this + c;
}
void ColoreCMY::remove(const Colore &c)
{
    *this = *this - c;
}
void ColoreCMY::media(const Colore &c)
{
    *this = *this / c;
}
ColoreCMY::operator ==(const Colore &c)
{
    if(checkType(c))
    {
        ColoreCMY temp = static_cast<const ColoreCMY&>(c);
        return (cyan == temp.cyan && magenta == temp.magenta && yellow == temp.yellow);
    }
    return false;
}
ColoreCMY ColoreRGB::toCMY()
{
    return ColoreCMY(255-red,255-green,255-blue);
}
ColoreCMY ColoreXYZ::toCMY()
{
    return toRGB().toCMY();
}
ColoreRGB ColoreCMY::toRGB()
{
    return ColoreRGB(255-cyan,255-magenta,255-yellow);
}
ColoreXYZ ColoreCMY::toXYZ()
{
    return toRGB().toXYZ();
}
