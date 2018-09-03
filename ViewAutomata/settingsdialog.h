#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "automagraphicsview.h"
#include <QTextEdit>
#include <QLineEdit>

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    AutomaGraphicsView::AutomaType type;
    QString alphabet;
    QChar epsilon;
    QTextEdit* typeSel;
    QLineEdit* alphabetEdit, *epsilonEdit;

    public:
    SettingsDialog(QWidget* = nullptr,Qt::WindowFlags = Qt::WindowFlags(),AutomaGraphicsView::AutomaType = AutomaGraphicsView::AutomaType::NFA, QString = "", QChar = '&');
    AutomaGraphicsView::AutomaType getType() const;
    QString getAlphabet() const;
    QChar getEpsilon() const;

private slots:
    void changeAlphabet(QString);
    void changeEpsilon(QString);
    void typeSelection();

public slots:
    void accept();
};

#endif // SETTINGSDIALOG_H
