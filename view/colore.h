#ifndef COLORE_H
#define COLORE_H


class Colore
{
public:
    virtual void add(const Colore& c) = 0;
    virtual void remove(const Colore& c) = 0;
    virtual void media(const Colore& c) = 0;
    virtual Colore* operator+(const Colore& c) const = 0;
    virtual Colore* operator-(const Colore& c) const = 0;
    virtual Colore* operator/(const Colore& c) const = 0;
    virtual bool operator==(const Colore& c) const = 0;
    virtual Colore& operator=(const Colore& c) = 0;
};
class ColoreXYZ;
class ColoreCMY;
class ColoreCMYK;
class ColoreRGB : public Colore
{
private:
    unsigned int red,green,blue;
    bool checkType(const Colore &c) const;
public:
    ColoreXYZ toXYZ() const;
    ColoreCMY toCMY() const;
    ColoreCMYK toCMYK() const;
    ColoreRGB();
    ColoreRGB(unsigned int _red,unsigned int _green,unsigned int _blue);
    ColoreRGB(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreRGB* operator+(const Colore& c) const;
    ColoreRGB* operator-(const Colore& c) const;
    ColoreRGB* operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    ColoreRGB& operator=(const Colore& c);
    ColoreRGB& operator =(const ColoreRGB& c);
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
    ColoreRGB toRGB() const;
    ColoreCMY toCMY() const;
    ColoreCMYK toCMYK() const;
    ColoreXYZ();
    ColoreXYZ(double _x,double _y,double _z);
    ColoreXYZ(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreXYZ* operator+(const Colore& c) const;
    ColoreXYZ* operator-(const Colore& c) const;
    ColoreXYZ* operator/(const Colore& c) const;
    bool operator==(const Colore& c) const;
    ColoreXYZ& operator =(const Colore& c);
    ColoreXYZ& operator =(const ColoreXYZ& c);
    double getX() const;
    double getY() const;
    double getZ() const;
    void setX(double amount);
    void setY(double amount);
    void setZ(double amount);
};

class ColoreCMY : public Colore
{
private:
    unsigned int cyan, magenta, yellow;
    bool checkType(const Colore &c) const;
public:
    ColoreXYZ toXYZ() const;
    ColoreRGB toRGB() const;
    ColoreCMYK toCMYK() const;
    ColoreCMY();
    ColoreCMY(unsigned int c,unsigned int m,unsigned int y);
    ColoreCMY(const Colore& c);
    virtual void add(const Colore& c);
    virtual void remove(const Colore& c);
    virtual void media(const Colore& c);
    virtual ColoreCMY* operator+(const Colore& c) const;
    virtual ColoreCMY* operator-(const Colore& c) const;
    virtual ColoreCMY* operator/(const Colore& c) const;
    virtual bool operator==(const Colore& c) const;
    ColoreCMY& operator =(const Colore& c);
    ColoreCMY& operator =(const ColoreCMY& c);
    unsigned int getCyan() const;
    unsigned int getMagenta() const;
    unsigned int getYellow() const;
    void setCyan(unsigned int amount);
    void setMagenta(unsigned int amount);
    void setYellow(unsigned int amount);
};

class ColoreCMYK : public ColoreCMY
{
private:
    unsigned int black;
    bool checkType(const Colore &c) const;
public:
    ColoreXYZ toXYZ() const;
    ColoreRGB toRGB() const;
    ColoreCMY toCMY() const;
    ColoreCMYK();
    ColoreCMYK(unsigned int c, unsigned int m, unsigned int y, unsigned int k);
    ColoreCMYK(const Colore& c);
    void add(const Colore& c);
    void remove(const Colore& c);
    void media(const Colore& c);
    ColoreCMYK* operator+(const Colore& c) const;
    ColoreCMYK* operator-(const Colore& c) const;
    ColoreCMYK* operator/(const Colore& c) const;
    virtual bool operator==(const Colore& c) const;
    ColoreCMYK& operator =(const Colore& c);
    ColoreCMYK& operator =(const ColoreCMYK& c);
    unsigned int getBlack() const;
    void setBlack(unsigned int amount);
};
#endif // COLORE_H
