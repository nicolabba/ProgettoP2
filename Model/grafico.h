#ifndef GRAFICO_H
#define GRAFICO_H
#include <vector>
#include <punto.h>
#include <list>

using std::vector;
using std::list;

class Grafico
{
private:
    list<Punto>* idp;

public:
    Grafico();
    Grafico(list<Punto>*);
    Grafico(const Grafico&);
    ~Grafico();
    Grafico& operator=(const Grafico&);
    void remove(const Punto&);
    bool search(const Punto&) const;
    void insert(const Punto&);

    long getArea() const;
    long size() const;
};

#endif // GRAFICO_H
