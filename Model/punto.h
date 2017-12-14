#ifndef PUNTO_H
#define PUNTO_H


class Punto
{
private:
    int x;
    int y;
public:
    Punto(int = 0, int = 0); // int -> punto
    bool operator==(const Punto&) const;

    int getX() const;
    int getY() const;

    int getDistance(Punto) const; // distanza tra due punti

    Punto getLocation() const;
    void setLocation(int, int);
};

#endif // PUNTO_H
