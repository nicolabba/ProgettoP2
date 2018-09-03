#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "abstractautoma.h"
#include"automagraphicsview.h"
#include <QTextEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    AbstractAutoma* automa;
    AutomaGraphicsView* view;
    QTextEdit* check;

private slots:
    void start();
    void addStato();
    void addTransizione();
};

#endif // MAINWINDOW_H
