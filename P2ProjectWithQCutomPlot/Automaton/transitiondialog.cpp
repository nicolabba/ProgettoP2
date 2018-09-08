#include "transitiondialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include <QLabel>

QString TransitionDialog::getFrom() const
{
    return from;
}

QString TransitionDialog::getTo() const
{
    return to;
}

QList<QString>* TransitionDialog::getNewHead() const
{
    return newHead;
}

QList<QChar>* TransitionDialog::getInput() const
{
    return input;
}

QList<QChar>* TransitionDialog::getHead() const
{
    return head;
}

TransitionDialog::TransitionDialog(QWidget * parent, Qt::WindowFlags f, QList<QString> *states, AutomatonGraphicsView::AutomaType type,const QString& alphabet, const QString &from, const QString &to, const QString &inputs, const QString &heads, const QString &newHeads):
    QDialog(parent, f), type(type), from(from), to(to), alphabet(alphabet)
{
    editInput(inputs);
    editHead(heads);
    editNewHead(newHeads);

    this->setModal(true);
    this->setFixedSize(200,220);

    QHBoxLayout * mainLayout, *opLayout;
    QVBoxLayout * inputLayout, *fromLayout, *toLayout, *layout;

    layout = new QVBoxLayout();
    mainLayout = new QHBoxLayout();
    opLayout = new QHBoxLayout();
    inputLayout = new QVBoxLayout();
    fromLayout = new QVBoxLayout();
    toLayout = new QVBoxLayout();

    QLabel * fromLabel = new QLabel("Da:", this);
    QLabel * toLabel = new QLabel("A:", this);
    fromLayout->addWidget(fromLabel);
    toLayout->addWidget(toLabel);

    QString temp;
    fromEdit = new QTextEdit(this);
    toEdit = new QTextEdit(this);
    fromEdit->setStyleSheet("QTextEdit{border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    toEdit->setStyleSheet("QTextEdit{border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    fromEdit->setReadOnly(true);
    toEdit->setReadOnly(true);
    fromEdit->setToolTip("Qui puoi selezionare lo stato da cui deve partire questa transizione");
    toEdit->setToolTip("Qui puoi selezionare lo stato al quale deve arrivare la transizione");
    for(QList<QString>::iterator i = states->begin(); i!= states->end(); i++)
        temp.append(i->append("\n"));
    fromEdit->append(temp);
    toEdit->append(temp);
    connect(fromEdit, SIGNAL(cursorPositionChanged()), this, SLOT(fromSelection()));
    connect(toEdit, SIGNAL(cursorPositionChanged()), this, SLOT(toSelection()));
    if(from != "" || to != "")
    {
        int index = temp.indexOf(from);
        fromEdit->textCursor().setPosition(index);
        fromEdit->textCursor().movePosition(QTextCursor::MoveOperation::EndOfLine,QTextCursor::MoveMode::KeepAnchor);
        fromEdit->setEnabled(false);
        index = temp.indexOf(to);
        toEdit->textCursor().setPosition(index);
        toEdit->textCursor().movePosition(QTextCursor::MoveOperation::EndOfLine,QTextCursor::MoveMode::KeepAnchor);
        toEdit->setEnabled(false);
    }
    fromLayout->addWidget(fromEdit);
    toLayout->addWidget(toEdit);
    mainLayout->addLayout(fromLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(toLayout);

    QLineEdit* inputEdit = new QLineEdit(inputs,this);
    QLineEdit* headEdit = new QLineEdit(heads,this);
    QLineEdit* newHeadEdit = new QLineEdit(newHeads,this);
    inputEdit->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    headEdit->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    newHeadEdit->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");

    inputEdit->setToolTip("Qui puoi inserire il carattere che dovra' essere letto per eseguire questa transizione");

    if(type != AutomatonGraphicsView::AutomaType::PDA)
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

    QLabel * inputLabel = new QLabel("Input:", this);
    QLabel * headLabel = new QLabel("Testa:", this);
    QLabel * newHeadLabel = new QLabel("Rimpiazzo:", this);

    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(headLabel);
    inputLayout->addWidget(headEdit);
    inputLayout->addWidget(newHeadLabel);
    inputLayout->addWidget(newHeadEdit);

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

    layout->addLayout(mainLayout);
    layout->addLayout(opLayout);

    setLayout(layout);
}

void TransitionDialog::editInput(QString val)
{
    input = new QList<QChar>();
    if(val.size()>=1)
    {
        QStringList splitInputs = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitInputs.begin(); i != splitInputs.end(); i++)
        {
            input->push_back(i->at(0).toLatin1());
        }
    }
}

void TransitionDialog::editHead(QString val)
{
    head = new QList<QChar>();
    if(val.size()>=1)
    {
        QStringList splitHeads = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitHeads.begin(); i != splitHeads.end(); i++)
        {
            head->push_back(i->at(0).toLatin1());
        }
    }
}

void TransitionDialog::editNewHead(QString val)
{
    newHead = new QList<QString>();
    if(val.size()>=1)
    {
        QStringList splitNewHeads = val.split(QChar(','), QString::SkipEmptyParts);
        for(QStringList::iterator i = splitNewHeads.begin(); i != splitNewHeads.end(); i++)
        {
            newHead->push_back(*i);
        }
    }
}

void TransitionDialog::fromSelection()
{
    QTextCursor cursor;
    cursor = fromEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    fromEdit->setTextCursor(cursor);
    from = cursor.selectedText();
}

void TransitionDialog::toSelection()
{
    QTextCursor cursor;
    cursor = toEdit->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    toEdit->setTextCursor(cursor);
    to = cursor.selectedText();
}

void TransitionDialog::accept()
{
    QMessageBox * temp;
    QString message;
    bool error = false;
    if(!error && (from == "" || to == ""))
    {
        message = "Deve essere selezionato sia uno stato di partenza che uno di arrivo";
        error = true;
    }
    if(!error && (type == AutomatonGraphicsView::AutomaType::PDA))
    {
        if(head->size() == 0)
        {
            error = true;
            message = "Deve essere inserito almeno un elemento in: testa";
        }
        if(newHead->size() == 0)
        {
            error = true;
            message = "Deve essere inserito almeno un elemento in: rimpiazzo";
        }

        if(!error && !(input->size() == head->size() && input->size() == newHead->size()))
        {
            error = true;
            message = "Il numero di elementi in input, testa e rimpiazzo deve essere uguale";
        }
    }
    else if(!error && type == AutomatonGraphicsView::AutomaType::DFA)
    {
        QChar ch;
        for(QList<QChar>::iterator c = input->begin(); c != input->end(); c++)
        {
            ch = *c;
            if(!alphabet.contains(ch))
            {
                error = true;
                message = "Non puoi inserire in input elementi non presenti nell'alfabeto dell'automa (DFA)";
            }
        }
    }
    if(!error && (input->size() == 0))
    {
        error = true;
        message = "Deve essere inserito almeno un elemento in: input";
    }
    if(error)
    {
        temp = new QMessageBox("Errore", message,
                                             QMessageBox::Warning,
                                             QMessageBox::Ok,
                                             QMessageBox::NoButton,
                                             QMessageBox::NoButton,this);
        temp->show();
    }
    else
        QDialog::accept();
}

