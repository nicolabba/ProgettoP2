#ifndef PUNTO_H
#define PUNTO_H

class Punto
{
private:
    double x;
    double y;
public:
    Punto(double = 0, double = 0); // double -> punto
    bool operator==(const Punto&) const;


    double getX() const;
    double getY() const;

    double getDistance(const Punto&) const; // distanza tra due punti
    static double getDistance(const Punto&, const Punto&);

    Punto* getLocation() const;
    void setLocation(double, double);
};

#endif // PUNTO_H
