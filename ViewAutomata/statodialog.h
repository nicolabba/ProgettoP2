#ifndef NEWSTATODIALOG_H
#define NEWSTATODIALOG_H

#include <QDialog>

class StatoDialog : public QDialog
{
    Q_OBJECT
private:
    QString text;
    bool iniziale, finale;
public:
    StatoDialog(QWidget* = nullptr,Qt::WindowFlags = Qt::WindowFlags(), QString = "", bool = false, bool = false);
    QString getInput();
    bool getIniziale();
    bool getFinale();
private slots:
    void editInput(QString);
    void changeIniziale(bool);
    void changeFinale(bool);

public slots:
    void accept();
};

#endif // NEWSTATODIALOG_H
