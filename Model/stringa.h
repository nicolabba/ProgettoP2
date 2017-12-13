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
    unsigned int dim;
    char* copy() const;
    static bool check(char* a, char* b, int dim);
public:
    unsigned int size() const;
    Stringa();
    Stringa(std::string s);
    Stringa(char* c, unsigned int _dim);
    Stringa(char c, int n = 1);
    Stringa(const Stringa& s);
    Stringa& operator = (const Stringa& s);
    ~Stringa();
    Stringa operator + (const Stringa& s) const;
    bool operator == (const Stringa& s)const ;
    char& operator[] (unsigned int i) const;
    void append(const Stringa& s);
    void remove(const Stringa& s);
    void remove(unsigned int id,unsigned int q = 1);
    int search(const Stringa& s) const; // ritorna id della prima apparenza o -1 se non viene trovato niente
    unsigned int hash() const;
    std::vector<Stringa> split(const Stringa& s) const;
    Stringa subString(unsigned int start,unsigned int len) const;
};
std::ostream& operator <<(std::ostream& os, const Stringa& s);
#endif // STRINGA_H
