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

int Punto::getDistance(Punto p) const
{
    return sqrt(pow(x - p.x,2) + pow(y - p.y,2));
}

Punto Punto::getLocation() const
{
    return Punto(x,y);
}

void Punto::setLocation(int _x = 0, int _y = 0)
{
    x = _x;
    y = _y;
}
