#include <iostream>
#include "stringa.h"
#include <string>
#include <vector>
using namespace std;
int main()
{
    Stringa d = Stringa("1:2:3:4:5:6:7:8:9:10");
    char array[10] = {'a','r','r','a','y','p','r','o','v','a'};
    Stringa s = Stringa("prova");
    cout << endl << "##INIZIO PROVA DEI COSTRUTTORI##"<<endl<<endl;
    cout << "default:" << Stringa() << "<end" << endl;
    cout << "da string, s = prova :" << Stringa("prova") << "<end" << endl;
    cout << "da array, c =  {'a','r','r','a','y','p','r','o','v','a'}, _dim = 10:" << Stringa(array, 10) << "<end" << endl;
    cout << "ripetizione carattere, c = 'a', n = 10: " << Stringa('a',10) << "<end" << endl;
    cout << "di copia, s = prova:" << Stringa(s) << "<end" << endl;
    cout << endl << "##FINE PROVA DEI COSTRUTTORI##";
    cout << endl << "##INIZIO PROVA DEGLI OPERATORI##"<<endl<<endl;
    cout << "=:" << endl;
    cout << "s =" << s << endl;
    Stringa a = Stringa("pippo");
    cout << "a =" << a << endl;
    cout << "a = s" << endl;
    a = s;
    cout << "a =" << a << endl;
    cout << "a = a" << endl;
    a = a;
    cout << "a =" << a << endl << endl;
    cout << "+:" << endl;
    cout << "s =" << s << endl;
    a = Stringa("pippo");
    cout << "a =" << a << endl;
    cout << "a + s =" << a + s << endl;
    cout << "a + a =" << a + a << endl;
    cout << "a + '' =" << a + Stringa() << endl << endl;
    cout << "==:" << endl;
    cout << "s =" << s << endl;
    cout << "a =" << a << endl;
    cout << "s == a =" << (s == a) << endl;
    cout << "s == s =" << (s == s) << endl;
    cout << "s == '' =" << (s == Stringa()) << endl << endl;
    cout << "[]:" << endl;
    cout << "a =" << a << endl;
    for(unsigned i = 0; i<a.size(); i++)
    {
        cout << "a[" << i << "] =" << a[i] << endl;
    }
    cout << "##FINE PROVA DEGLI OPERATORI##" << endl;
    cout << endl << "##INIZIO PROVA DELLE FUNZIONI##"<<endl<<endl;
    cout << "s =" << s << endl;
    cout << "a =" << a << endl;
    cout << "a.append(s)" << endl;
    a.append(s);
    cout << "a =" << a << endl << endl;
    cout << "a.search(s) = " << a.search(s) << endl << endl;
    cout << "a.remove(s)" << endl;
    a.remove(s);
    cout << "a =" << a << endl << endl;
    cout << "a.search(s) = " << a.search(s) << endl << endl;
    cout << "a.remove(s)" << endl;
    a.remove(s);
    cout << "a =" << a << endl << endl;
    cout << "a.remove(2,1)" << endl;
    a.remove(2,1);
    cout << "a =" << a << endl;
    cout << "a.hash() = " << a.hash() << endl;
    cout << "s =" << s << endl;
    cout << "s.hash() = " << s.hash() << endl << endl;
    cout << "s.substring(0,3) = " << s.subString(0,3) << endl  << endl;
    vector<Stringa> v = d.split(Stringa(":"));
    cout << "d =" << d << endl;
    cout << "v = d.split(Stringa(':'))" << endl;
    for(unsigned int i = 0; i < v.size(); i++)
    {
        cout << "v[" << i << "] =" << v[i] << endl;
    }
    cout << "##FINE PROVA DELLE FUNZIONI##" << endl;
}
