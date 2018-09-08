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
    StateDialog(QWidget* = nullptr,Qt::WindowFlags = Qt::WindowFlags(), const QString& = "", bool = false, bool = false);
    QString getInput() const;
    bool getStarting() const;
    bool getFinal() const;
private slots:
    void setInput(QString);
    void setStarting(bool);
    void setFinal(bool);

public slots:
    void accept();
};

#endif // STATEDIALOG_H
