#ifndef TRANSIZIONEDIALOG_H
#define TRANSIZIONEDIALOG_H

#include <QDialog>
#include <automagraphicsview.h>
#include <QTextEdit>
#include <QString>

class TransizioneDialog : public QDialog
{
    Q_OBJECT
private:
    AutomaGraphicsView::AutomaType type;
    std::list<char>* input, *head;
    std::list<std::string>* newHead;
    std::string partenza, arrivo;
    QTextEdit* partEdit,* arrEdit;
public:
    TransizioneDialog(QWidget * = nullptr, Qt::WindowFlags = Qt::WindowFlags(), std::list<std::string>* = new std::list<std::string>(), AutomaGraphicsView::AutomaType = AutomaGraphicsView::AutomaType::NFA, std::string = "", std::string = "", QString = "a", QString = "", QString = "");
    std::string getPartenza() const;
    std::string getArrivo() const;
    std::list<std::string>* getNewHead() const;
    std::list<char>* getInput() const;
    std::list<char>* getHead() const;

private slots:
    void editInput(QString);
    void editHead(QString);
    void editNewHead(QString);
    void partSelection();
    void arrSelection();
};

#endif // TRANSIZIONEDIALOG_H
