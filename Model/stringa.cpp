#include "stringa.h"
#include <string>
#include <iostream>
#include <vector>

char* Stringa::copy() const
{
    if(dim==0)
        return 0;
    char* ret = new char[dim];
    for(unsigned int i=0; i<dim; ++i)
        ret[i]=a[i];
    return ret;
}
unsigned int Stringa::size() const
{
    return dim;
}

Stringa::Stringa() : a(0), dim(0){}
Stringa::Stringa(const Stringa& s): a(s.copy()), dim(s.dim) {}
Stringa::Stringa(char *c, unsigned int _dim)
{
    if(_dim>0)
    {
        dim = _dim;
        a = new char[dim];
        for(unsigned int i = 0; i<dim; i++)
            a[i] = c[i];
    }
}
Stringa::Stringa(char c, int n)
{
    if(n>0)
    {
        dim = n;
        a = new char[dim];
        for(unsigned int i = 0; i<dim; i++)
            a[i] = c;
    }
}
Stringa::Stringa(std::string s)
{
    dim = s.size();
    a = new char[dim];
    for(unsigned int i = 0; i<dim; i++)
        a[i] = s[i];
}

Stringa& Stringa::operator =(const Stringa& s)
{
    if(this != & s)
    {
        delete[] a;
        a = s.copy();
        dim = s.dim;
    }
    return *this;
}
Stringa::~Stringa()
{
    delete[] a;
}

Stringa Stringa::operator +(const Stringa& s) const
{
   Stringa x;
   x.a = new char[dim + s.dim];
   x.dim = dim + s.dim;
   unsigned int i=0;
   for(; i<dim; ++i) x.a[i]=a[i];
   for( ; i<x.dim; ++i) x.a[i] = s.a[i-dim];
   return x;
}

void Stringa::append(const Stringa& s)
{
    *this = *this + s;
}

bool Stringa::operator ==(const Stringa& s) const
{
    if(dim != s.dim) return false;
    for(unsigned int i=0; i<dim; ++i)
      if(a[i] != s.a[i]) return false;
    return true;
}

char& Stringa::operator [](unsigned int i) const
{
    return a[i];
}

void Stringa::remove(unsigned int id, unsigned int q)
{
    dim-=q;
    char *c = new char[dim]();
    for(unsigned int i = 0; i<dim; i++)
    {
        if(i<id)
            c[i] = a[i];
        else
            c[i] = a[i+q];
    }
    delete[] a;
    a = c;
}
bool Stringa::check(char *a, char *b, int dim)
{
    bool ret = true;
    for(int i = 0; ret && i<dim; i++)
        if(a[i]!=b[i])
            ret = false;
    return ret;
}
int Stringa::search(const Stringa &s) const
{
    bool found = false;
    int ret = -1;
    for(unsigned int i = 0; !found && i<=dim-s.dim; i++)
    {
        if(a[i] == s.a[0] && check(&a[i], s.a, s.dim))
        {
            found = true;
            ret = i;
        }
    }
    return ret;
}

void Stringa::remove(const Stringa &s)
{
    int id = search(s);
    if(id != -1)
    {
        remove(id,s.dim);
    }
}
Stringa Stringa::subString(unsigned int start,unsigned int len) const
{
    return Stringa(&a[start], len);
}
std::vector<Stringa> Stringa::split(const Stringa &s) const
{
    std::vector<Stringa> ret;
    Stringa temp = Stringa(copy(),dim), al;
    int index = temp.search(s);
    while(index != -1)
    {
        al = temp.subString(0,index);
        ret.push_back(al);
        temp.remove(0,index+s.size());
        index = temp.search(s);
    }
    ret.push_back(temp);
    return ret;
}

unsigned int Stringa::hash() const
{
    unsigned int ret = A;
    for (unsigned int i = 0; i<dim; i++)
        ret = (ret * B) ^ (a[i] * C);
    return ret;
}

std::ostream& operator <<(std::ostream& os, const Stringa& s) {
  for(unsigned int i=0; i<s.size(); ++i)
      os << s[i];
  return os;
}
