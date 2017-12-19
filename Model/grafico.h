#ifndef GRAFICO_H
#define GRAFICO_H
#include <vector>
#include <punto.h>

using std::vector;

class Grafico
{
private:
    vector<Punto>* idp;

public:
    Grafico();
    Grafico(vector<Punto>*);
    Grafico(const Grafico&);
    ~Grafico();
    Grafico& operator=(const Grafico&);
    Punto& operator[](const int&) const;
    void remove(int x, int y);
    int search(int x, int y) const;
    void insert(int x, int y);

    long getArea() const;
    long size() const;
};

#endif // GRAFICO_H
