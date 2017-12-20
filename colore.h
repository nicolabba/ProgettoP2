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
    ColoreXYZ toXYZ() const;
    ColoreCMY toCMY() const;
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
    unsigned double x,y,z;
    bool checkType(const Colore &c) const;
    ColoreRGB toRGB() const;
    ColoreCMY toCMY() const;
public:
    ColoreXYZ();
    ColoreXYZ(unsigned double _x,unsigned double _y,unsigned double _z);
    ColoreXYZ(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreXYZ operator+(const Colore& c) const;
    ColoreXYZ operator-(const Colore& c) const;
    ColoreXYZ operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    unsigned double getX() const;
    unsigned double getY() const;
    unsigned double getZ() const;
    void setX(unsigned double amount);
    void setY(unsigned double amount);
    void setZ(unsigned double amount);
};

class ColoreCMY : public Colore
{
private:
    unsigned int cyan, magenta, yellow;
    bool checkType(const Colore &c) const;
    ColoreRGB toRGB() const;
public:
    ColoreCMY();
    ColoreCMY(unsigned int c,unsigned int m,unsigned int y);
    ColoreCMY(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreCMY operator+(const Colore& c) const;
    ColoreCMY operator-(const Colore& c) const;
    ColoreCMY operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    unsigned int getCyan() const;
    unsigned int getMagenta() const;
    unsigned int getYellow() const;
    void setCyan(unsigned int amount);
    void setMagenta(unsigned int amount);
    void setYellow(unsigned int amount);
};
#endif // COLORE_H
