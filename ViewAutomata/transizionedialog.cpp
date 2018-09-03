#include "transizionedialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
std::string TransizioneDialog::getPartenza() const
{
    return partenza;
}

std::string TransizioneDialog::getArrivo() const
{
    return arrivo;
}

std::list<std::string>* TransizioneDialog::getNewHead() const
{
    return newHead;
}

std::list<char>* TransizioneDialog::getInput() const
{
    return input;
}

std::list<char>* TransizioneDialog::getHead() const
{
    return head;
}

TransizioneDialog::TransizioneDialog(QWidget * parent, Qt::WindowFlags f, std::list<std::string> *stati, AutomaGraphicsView::AutomaType type, std::string da, std::string a, QString inputs, QString heads, QString newHeads):
    QDialog(parent, f), partenza(da), arrivo(a)//, input(input), head(head), newHead(newHead)
{
    editInput(inputs);
    editHead(heads);
    editNewHead(newHeads);

    this->setModal(true);
    this->setFixedSize(200,150);

    QHBoxLayout * layout, *opLayout;
    QVBoxLayout * inputLayout;

    layout = new QHBoxLayout();
    opLayout = new QHBoxLayout();
    inputLayout = new QVBoxLayout();

    QString temp;
    partEdit = new QTextEdit(this);
    arrEdit = new QTextEdit(this);
    partEdit->setStyleSheet("border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    arrEdit->setStyleSheet("border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    partEdit->setReadOnly(true);
    arrEdit->setReadOnly(true);
    partEdit->setToolTip("Qui puoi selezionare lo stato da cui deve partire questa transizione");
    arrEdit->setToolTip("Qui puoi selezionare lo stato al quale deve arrivare la transizione");
    for(std::list<std::string>::iterator i = stati->begin(); i!= stati->end(); i++)
        temp.append(QString::fromStdString(i->append("\n")));
    partEdit->append(temp);
    arrEdit->append(temp);
    connect(partEdit, SIGNAL(cursorPositionChanged()), this, SLOT(partSelection()));
    connect(arrEdit, SIGNAL(cursorPositionChanged()), this, SLOT(arrSelection()));
    if(da != "" || a != "")
    {
        int index = temp.indexOf(QString::fromStdString(da));
        partEdit->textCursor().setPosition(index);
        partEdit->textCursor().movePosition(QTextCursor::MoveOperation::EndOfLine,QTextCursor::MoveMode::KeepAnchor);
        partEdit->setEnabled(false);
        index = temp.indexOf(QString::fromStdString(a));
        arrEdit->textCursor().setPosition(index);
        arrEdit->textCursor().movePosition(QTextCursor::MoveOperation::EndOfLine,QTextCursor::MoveMode::KeepAnchor);
        arrEdit->setEnabled(false);
    }
    layout->addWidget(partEdit);
    layout->addLayout(inputLayout);
    layout->addWidget(arrEdit);

    QLineEdit* inputEdit = new QLineEdit(inputs,this);
    QLineEdit* headEdit = new QLineEdit(heads,this);
    QLineEdit* newHeadEdit = new QLineEdit(newHeads,this);
    inputEdit->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    headEdit->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    newHeadEdit->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");

    inputEdit->setToolTip("Qui puoi inserire il carattere che dovra' essere letto per eseguire questa transizione");

    if(type != AutomaGraphicsView::AutomaType::PDA)
    {
        headEdit->setEnabled(false);
        headEdit->setToolTip("Disponibile solo per PDA");
        newHeadEdit->setEnabled(false);
        newHeadEdit->setToolTip("Disponibile solo per PDA");
    }else
    {
        headEdit->setToolTip("Qui puoi inserire il carattere che dovra' essere in testa alla pila per eseguire questa transizione (Una volta eseguita sara' rimpiazzato)");
        newHeadEdit->setToolTip("Qui puoi inserire i caratteri che verranno posti in testa alla pila una volta eseguita questa transizione");
    }
    connect(inputEdit,SIGNAL(textEdited(QString)),this,SLOT(editInput(QString)));
    connect(headEdit,SIGNAL(textEdited(QString)),this,SLOT(editHead(QString)));
    connect(newHeadEdit,SIGNAL(textEdited(QString)),this,SLOT(editNewHead(QString)));
    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(headEdit);
    inputLayout->addWidget(newHeadEdit);
    inputLayout->addLayout(opLayout);

    QString ButtonStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; width:40px; height:35px } QToolTip{border:none; background-color:#f0f0f0}";
    QPushButton* ok, *cancel;
    ok = new QPushButton("Ok", this);
    cancel = new QPushButton("Cancel", this);
    ok->setStyleSheet(ButtonStyleSheet);
    cancel->setStyleSheet(ButtonStyleSheet);
    connect(ok,SIGNAL(pressed()),this,SLOT(accept()));
    connect(cancel,SIGNAL(pressed()),this,SLOT(reject()));
    opLayout->addStretch(1);
    opLayout->addWidget(ok);
    opLayout->addWidget(cancel);
    opLayout->addStretch(1);

    setLayout(layout);
}

void TransizioneDialog::editInput(QString val)
{
    input = new std::list<char>();
    if(val.size()>=1)
    {
        QStringList splitInputs = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitInputs.begin(); i != splitInputs.end(); i++)
        {
            input->push_back(i->at(0).toLatin1());
        }
    }
}

void TransizioneDialog::editHead(QString val)
{
    head = new std::list<char>();
    if(val.size()>=1)
    {
        QStringList splitHeads = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitHeads.begin(); i != splitHeads.end(); i++)
        {
            head->push_back(i->at(0).toLatin1());
        }
    }
}

void TransizioneDialog::editNewHead(QString val)
{
    newHead = new std::list<std::string>();
    if(val.size()>=1)
    {
        QStringList splitNewHeads = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitNewHeads.begin(); i != splitNewHeads.end(); i++)
        {
            newHead->push_back((*i).toStdString());
        }
    }
}

void TransizioneDialog::partSelection()
{
    QTextCursor cursor;
    cursor = partEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    partEdit->setTextCursor(cursor);
    partenza = cursor.selectedText().toStdString();
}

void TransizioneDialog::arrSelection()
{
    QTextCursor cursor;
    cursor = arrEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    arrEdit->setTextCursor(cursor);
    arrivo = cursor.selectedText().toStdString();
}
