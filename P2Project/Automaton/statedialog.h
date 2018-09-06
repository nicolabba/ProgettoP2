#ifndef STATEDIALOG_H
#define STATEDIALOG_H

#include <QDialog>

class StateDialog : public QDialog
{
    Q_OBJECT
private:
    QString text;
    bool starting, final;
public:
    StateDialog(QWidget* = nullptr,Qt::WindowFlags = Qt::WindowFlags(), QString = "", bool = false, bool = false);
    QString getInput();
    bool getStarting();
    bool getFinal();
private slots:
    void setInput(QString);
    void setStarting(bool);
    void setFinal(bool);

public slots:
    void accept();
};

#endif // STATEDIALOG_H
