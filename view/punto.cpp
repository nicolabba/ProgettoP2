#include "punto.h"
#include <math.h>

Punto::Punto(int _x, int _y) : x(_x), y(_y)
{

}
bool Punto::operator ==(const Punto& p) const
{
    return x == p.x && y == p.y;
}

int Punto::getX() const
{
    return x;
}

int Punto::getY() const
{
    return y;
}

int Punto::getDistance(const Punto& p) const
{
    return sqrt(pow(x - p.x,2) + pow(y - p.y,2));
}

int Punto::getDistance(const Punto& p1, const Punto& p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

Punto* Punto::getLocation() const
{
    return new Punto(x,y);
}

void Punto::setLocation(int _x = 0, int _y = 0)
{
    x = _x;
    y = _y;
}
