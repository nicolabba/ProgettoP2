#ifndef STRINGA_H
#define STRINGA_H
#include <string>
#include <vector>
class Stringa
{
private:
    static const int A = 27983;/* Numero primo per la generazione di hash */
    static const int B = 47701;/* Numero primo per la generazione di hash */
    static const int C = 68111;/* Numero primo per la generazione di hash */
    char* a;
     int dim;
    char* copy() const;
    static bool check(char* a, char* b, int dim);
public:
     int size() const;
    Stringa();
    Stringa(std::string s);
    Stringa(char* c,  int _dim);
    Stringa(char c, int n = 1);
    Stringa(const Stringa& s);
    Stringa& operator = (const Stringa& s);
    ~Stringa();
    Stringa operator + (const Stringa& s) const;
    bool operator == (const Stringa& s)const ;
    char& operator[] ( int i) const;
    void append(const Stringa& s);
    void remove(const Stringa& s);
    void remove( int id, int q = 1);
    int search(const Stringa& s) const; // ritorna id della prima apparenza o -1 se non viene trovato niente
     int hash() const;
    std::vector<Stringa> split(const Stringa& s) const;
    Stringa subString( int start, int len) const;
    char* toString() const;
};
std::ostream& operator <<(std::ostream& os, const Stringa& s);
#endif // STRINGA_H
