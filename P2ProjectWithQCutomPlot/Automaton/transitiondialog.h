#ifndef TRANSITIONDIALOG_H
#define TRANSITIONDIALOG_H

#include <QDialog>
#include "automatongraphicsview.h"
#include <QTextEdit>
#include <QString>
#include <QList>

class TransitionDialog : public QDialog
{
    Q_OBJECT
private:
    AutomatonGraphicsView::AutomaType type;
    QList<QString>* newHead;
    QList<QChar>* input, *head;
    QString from, to, alphabet;
    QTextEdit* fromEdit,* toEdit;
public:
    TransitionDialog(QWidget * = nullptr, Qt::WindowFlags = Qt::WindowFlags(), QList<QString>* = new QList<QString>(),
                     AutomatonGraphicsView::AutomaType = AutomatonGraphicsView::AutomaType::NFA, const QString & = "", const QString& = "",
                     const QString& = "", const QString& = "", const QString& = "", const QString& = "");
    QString getFrom() const;
    QString getTo() const;
    QList<QString>* getNewHead() const;
    QList<QChar>* getInput() const;
    QList<QChar>* getHead() const;

private slots:
    void editInput(QString);
    void editHead(QString);
    void editNewHead(QString);
    void fromSelection();
    void toSelection();
    void accept();
};

#endif // TRANSITIONDIALOG_H
