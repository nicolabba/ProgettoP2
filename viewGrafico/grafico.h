#ifndef GRAFICO_H
#define GRAFICO_H
#include <qvector.h>
#include <punto.h>
#include <list>

using std::vector;
using std::list;

class Grafico
{
private:
    list<Punto>* idp;
    static long double getPartialArea(const Punto&, const Punto&);
    static long double getAreaTri(const Punto&, const Punto&);
    static long double getAreaRet(const Punto&, const Punto&);
public:
    Grafico();
    Grafico(list<Punto>*);
    Grafico(const Grafico&);
    ~Grafico();
    Grafico& operator=(const Grafico&);
    list<Punto>* clone() const;
    void remove(const Punto&);
    bool search(const Punto&) const;
    bool insert(const Punto&);
    QVector<double> getXvalues() const;
    QVector<double> getYvalues() const;
    long double getArea() const;
    long double getLenght() const;
    long double size() const;
    double getMaxX() const;
    double getMinX() const;
    double getMaxY() const;
    Punto* getMax() const;
    Punto* getMin() const;
};

#endif // GRAFICO_H
