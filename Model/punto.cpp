#include "punto.h"
#include <math.h>

Punto::Punto(double _x, double _y) : x(_x), y(_y)
{

}
bool Punto::operator ==(const Punto& p) const
{
    return x == p.x;
}

double Punto::getX() const
{
    return x;
}

double Punto::getY() const
{
    return y;
}

double Punto::getDistance(const Punto& p) const
{
    return sqrt(pow(x - p.x,2) + pow(y - p.y,2));
}

double Punto::getDistance(const Punto& p1, const Punto& p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Punto* Punto::getLocation() const
{
    return new Punto(x,y);
}

void Punto::setLocation(double _x = 0, double _y = 0)
{
    x = _x;
    y = _y;
}
