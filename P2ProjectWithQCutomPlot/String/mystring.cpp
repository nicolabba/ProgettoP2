#include "mystring.h"
#include <string>
#include <iostream>
#include <vector>

char* MyString::copy() const
{
    if(dim==0)
        return 0;
    char* ret = new char[dim];
    for( int i=0; i<dim; ++i)
        ret[i]=a[i];
    return ret;
}
 int MyString::size() const
{
    return dim;
}

MyString::MyString() : a(0), dim(0){}
MyString::MyString(const MyString& s): a(s.copy()), dim(s.dim) {}
MyString::MyString(char *c,  int _dim)
{
    //if(_dim>0)
    //{
    dim = _dim;
    a = new char[dim];
    for( int i = 0; i<dim; i++)
        a[i] = c[i];
    //}
}
MyString::MyString(char c, int n)
{
    if(n>0)
    {
        dim = n;
        a = new char[dim];
        for( int i = 0; i<dim; i++)
            a[i] = c;
    }
}
MyString::MyString(const std::string& s)
{
    dim = s.size();
    a = new char[dim];
    for( int i = 0; i<dim; i++)
        a[i] = s[i];
}

MyString& MyString::operator =(const MyString& s)
{
    if(this != & s)
    {
        delete[] a;
        a = s.copy();
        dim = s.dim;
    }
    return *this;
}
MyString::~MyString()
{
    delete[] a;
}

MyString MyString::operator +(const MyString& s) const
{
   MyString x;
   x.a = new char[dim + s.dim];
   x.dim = dim + s.dim;
    int i=0;
   for(; i<dim; ++i) x.a[i]=a[i];
   for( ; i<x.dim; ++i) x.a[i] = s.a[i-dim];
   return x;
}

void MyString::append(const MyString& s)
{
    *this = *this + s;
}

bool MyString::operator ==(const MyString& s) const
{
    if(dim != s.dim) return false;
    for( int i=0; i<dim; ++i)
      if(a[i] != s.a[i]) return false;
    return true;
}

char& MyString::operator []( int i) const
{
    return a[i];
}

void MyString::remove( int id,  int q)
{
    dim-=q;
    char *c = new char[dim]();
    for( int i = 0; i<dim; i++)
    {
        if(i<id)
            c[i] = a[i];
        else
            c[i] = a[i+q];
    }
    delete[] a;
    a = c;
}
bool MyString::check(char *a, char *b, int dim)
{
    bool ret = true;
    for(int i = 0; ret && i<dim; i++)
        if(a[i]!=b[i])
            ret = false;
    return ret;
}
int MyString::search(const MyString &s) const
{
    bool found = false;
    int ret = -1;
    if(s.dim>0)
        for(int i = 0; !found && i<=dim - s.dim; i++)
        {
            if(a[i] == s.a[0] && check(&a[i], s.a, s.dim))
            {
                found = true;
                ret = i;
            }
        }
    return ret;
}

void MyString::remove(const MyString &s)
{
    int id = search(s);
    if(id != -1)
    {
        remove(id,s.dim);
    }
}
MyString MyString::subString( int start, int len) const
{
    return MyString(&a[start], len);
}
std::vector<MyString> MyString::split(const MyString &s) const
{
    std::vector<MyString> ret;
    MyString temp = MyString(copy(),dim), al;
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

 int MyString::hash() const
{
     int ret = A;
    for ( int i = 0; i<dim; i++)
        ret = (ret * B) ^ (a[i] * C);
    return ret;
}

std::ostream& operator <<(std::ostream& os, const MyString& s) {
  for( int i=0; i<s.size(); ++i)
      os << s[i];
  return os;
}

char* MyString::toString() const
{
    char* res = new char[size()+1]();
    for( int i = 0; i<size();i++)
    {
        res[i] = a[i];
    }
    res[size()+1] = '\0';
    return res;
}
