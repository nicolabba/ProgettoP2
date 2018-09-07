#ifndef STRINGA_H
#define STRINGA_H
#include <string>
#include <vector>
class MyString
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
    MyString();
    MyString(const std::string& s);
    MyString(char* c,  int _dim);
    MyString(char c, int n = 1);
    MyString(const MyString& s);
    MyString& operator = (const MyString& s);
    ~MyString();
    MyString operator + (const MyString& s) const;
    bool operator == (const MyString& s)const ;
    char& operator[] ( int i) const;
    void append(const MyString& s);
    void remove(const MyString& s);
    void remove( int id, int q = 1);
    int search(const MyString& s) const; // ritorna id della prima apparenza o -1 se non viene trovato niente
    int hash() const;
    std::vector<MyString> split(const MyString& s) const;
    MyString subString( int start, int len) const;
    char* toString() const;
};
std::ostream& operator <<(std::ostream& os, const MyString& s);
#endif // STRINGA_H
