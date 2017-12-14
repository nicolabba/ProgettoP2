#ifndef COLORE_H
#define COLORE_H


class Colore
{
private:
    int Prim1, Prim2, Prim3;
public:
    enum Primari{};
    virtual void add(const Colore& c);
    virtual void remove(const Colore& c);
    virtual void media(const Colore& c);
    virtual Colore& operator+(const Colore& c) const;
    virtual Colore& operator-(const Colore& c) const;
    virtual bool operator==(const Colore& c) const;
    int getShade(Primari p) const;
    void setShade(Primari p, int amount);
};

class ColoreRGB : public Colore
{
public:
    enum Primari{Red, Green, Blue};
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreRGB& operator+(const Colore& c) const;
    ColoreRGB& operator-(const Colore& c) const;
    bool operator==(const Colore& c) const;
};

#endif // COLORE_H
