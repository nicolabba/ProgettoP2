#ifndef INPUTLINE_H
#define INPUTLINE_H

#include <QWidget>
#include "stringa.h"
#include <QLineEdit>
#include <QCheckBox>

class InputLine : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* input;
    QCheckBox* check;
public:
    explicit InputLine(QWidget *parent = 0);
    ~InputLine();
    QString getValue();
    bool getActive();
signals:
    void valueChanged(QString s);
    void activeChanged(bool act);
    void changeVal(QString s);
    void changeActive(bool act);
private slots:
    void changeActivation(int i);
public slots:
    void setSelection(int start, int length);
};

#endif // INPUTLINE_H
