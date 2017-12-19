#ifndef COLORE_H
#define COLORE_H


class Colore
{
    virtual Colore();
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
    unsigned int red,green,blue;
    bool checkType(const Colore &c) const;
public:
    ColoreRGB();
    ColoreRGB(int _red,int _green,int _blue);
    ColoreRGB(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreRGB operator+(const Colore& c) const;
    ColoreRGB operator-(const Colore& c) const;
    ColoreRGB operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
    void setRed(int amount);
    void setGreen(int amount);
    void setBlue(int amount);
};

class ColoreXYZ : public Colore
{
private:
    double x,y,z;
    bool checkType(const Colore &c) const;
public:
    ColoreXYZ();
    ColoreXYZ(double _x,double _y,double _z);
    ColoreXYZ(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreXYZ operator+(const Colore& c) const;
    ColoreXYZ operator-(const Colore& c) const;
    ColoreXYZ operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double amount);
    void setY(double amount);
    void setZ(double amount);
}
#endif // COLORE_H
