#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stringa.h"
#include <QList>
#include "inputline.h"
#include <QVBoxLayout>
#include <QSignalMapper>
#include "inputs.h"
#include <QScrollArea>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QList<Stringa*> stringhe;
    QList<bool> activeInp;
    Inputs* inp;
    Stringa opInput;
    QScrollArea* inpCont;
    void refreshSize();
private slots:
    void updateStoredData(int index, QString value, bool active);
    void addInput();
    void removeInput();
    void append();
    void remove();
    void search();
    void split();
    void hash();
    void duplicate();
    void editOpInput(QString s);
};

#endif // MAINWINDOW_H
