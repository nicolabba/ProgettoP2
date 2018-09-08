#ifndef STRINGMAIN_H
#define STRINGMAIN_H

#include <QWidget>
#include "mystring.h"
#include <QList>
#include "inputline.h"
#include <QVBoxLayout>
#include <QSignalMapper>
#include "inputs.h"
#include <QScrollArea>

class StringMain : public QWidget
{
    Q_OBJECT
public:
    explicit StringMain(QWidget *parent = nullptr);

private:
    QList<MyString*> myStrings;
    QList<bool> activeInp;
    Inputs* inp;
    MyString opInput;
    QScrollArea* inpCont;
    void refreshSize();
private slots:
    void updateStoredData(int index, const QString& value, bool active);
    void addInput();
    void removeInput();
    void append();
    void remove();
    void search();
    void split();
    void hash();
    void duplicate();
    void editOpInput(const QString& s);
};

#endif // STRINGMAIN_H
