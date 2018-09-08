#ifndef AUTOMATONMAIN_H
#define AUTOMATONMAIN_H

#include <QWidget>
#include "abstractautomaton.h"
#include"automatongraphicsview.h"
#include <QTextEdit>

class AutomatonMain : public QWidget
{
    Q_OBJECT
public:
    explicit AutomatonMain(QWidget *parent = nullptr);

private:
    AutomatonGraphicsView* view;
    QTextEdit* check;

private slots:
    void start();
    void addState();
    void addTransition();
    void resetResults();
};

#endif // AUTOMATONMAIN_H
