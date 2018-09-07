#ifndef INPUTS_H
#define INPUTS_H

#include <QWidget>
#include "mystring.h"
#include "inputline.h"
#include <QSignalMapper>
#include <QVBoxLayout>

class Inputs : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QList<InputLine*> inputs;
    QSignalMapper* mapper;
public:
    explicit Inputs(QWidget *parent = 0);
    void refresh(QList<MyString *> elements,QList<bool> active);
    bool getActive(int index) const;
    QString getValue(int index) const;
    int getEleNumber() const;
    ~Inputs();
private slots:
    void sendChanged(int index);
public slots:
    void setSelection(int input, int index, int length);
signals:
    void changed(int,QString,bool);
};

#endif // INPUTS_H
