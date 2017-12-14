#ifndef COLORE_H
#define COLORE_H


class Colore
{
private:
    int prim1, prim2, prim3;
protected:
    Colore();
    Colore(int _prim1,int _prim2,int _prim3);
    Colore(const Colore& c);
    int getShade(int i) const;
    void setShade(int i, int amount);
    virtual bool checkType(const Colore&c) const = 0;
public:
    static int const MIN = 0;
    static int const MAX = 255;
    virtual void add(const Colore& c);
    virtual void remove(const Colore& c);
    virtual void media(const Colore& c);
    virtual Colore operator+(const Colore& c) const;
    virtual Colore operator-(const Colore& c) const;
    virtual Colore operator/(const Colore& c) const;
    virtual bool operator==(const Colore& c) const;
};

class ColoreRGB : public Colore
{
private:
    bool checkType(const Colore &c) const;
public:
    enum Primari{Red, Green, Blue};
    ColoreRGB();
    ColoreRGB(int red,int green,int blue);
    ColoreRGB(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreRGB operator+(const Colore& c) const;
    ColoreRGB operator-(const Colore& c) const;
    ColoreRGB operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    int getShade(Primari p) const;
    void setShade(Primari p, int amount);
};

#endif // COLORE_H
