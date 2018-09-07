#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "automatongraphicsview.h"
#include <QTextEdit>
#include <QLineEdit>

class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    AutomatonGraphicsView::AutomaType type;
    QString alphabet;
    QChar epsilon;
    QTextEdit* typeSel;
    QLineEdit* alphabetEdit, *epsilonEdit;

    public:
    SettingsDialog(QWidget* = nullptr,Qt::WindowFlags = Qt::WindowFlags(),AutomatonGraphicsView::AutomaType = AutomatonGraphicsView::AutomaType::NFA, const QString& = "", const QChar& = '&');
    AutomatonGraphicsView::AutomaType getType() const;
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
