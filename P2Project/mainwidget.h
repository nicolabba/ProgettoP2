#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "String/stringmain.h"
#include "Graph/graphmain.h"
#include "Automaton/automatonmain.h"

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    QList<StringMain*>* sm;
    QList<GraphMain*>* gm;
    QList<AutomatonMain*>* am;
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void openStringEditor();
    void openGraphEditor();
    void openAutomatonEditor();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
