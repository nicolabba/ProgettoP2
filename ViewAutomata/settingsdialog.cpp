#include "settingsdialog.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>

AutomaGraphicsView::AutomaType SettingsDialog::getType() const
{
    return type;
}

QString SettingsDialog::getAlphabet() const
{
    return alphabet;
}

QChar SettingsDialog::getEpsilon() const
{
    return epsilon;
}

SettingsDialog::SettingsDialog(QWidget * parent, Qt::WindowFlags f, AutomaGraphicsView::AutomaType type, QString alphabet, QChar epsilon):QDialog(parent,f),type(type),alphabet(alphabet),epsilon(epsilon)
{
    this->setModal(true);
    this->setFixedSize(200,185);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();

    typeSel = new QTextEdit(this);
    typeSel->setStyleSheet("border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    typeSel->setReadOnly(true);
    typeSel->setToolTip("Qui puoi selezionare il tipo di automa");
    typeSel->append("NFA\nDFA\nPDA");
    connect(typeSel, SIGNAL(cursorPositionChanged()), this, SLOT(typeSelection()));
    int index;
    switch(type)
    {
    case AutomaGraphicsView::AutomaType::NFA:
        index = 0;
        break;
    case AutomaGraphicsView::AutomaType::DFA:
        index = 4;
        break;
    case AutomaGraphicsView::AutomaType::PDA:
        index = 8;
        break;
    }
    typeSel->textCursor().setPosition(index);
    typeSel->textCursor().movePosition(QTextCursor::MoveOperation::EndOfLine,QTextCursor::MoveMode::KeepAnchor);
    layout->addWidget(typeSel);

    alphabetEdit = new QLineEdit(alphabet ,this);
    alphabetEdit->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    connect(alphabetEdit,SIGNAL(textChanged(QString)),this,SLOT(changeAlphabet(QString)));
    layout->addWidget(alphabetEdit);

    epsilonEdit = new QLineEdit(epsilon ,this);
    epsilonEdit->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    epsilonEdit->setMaxLength(1);
    connect(epsilonEdit,SIGNAL(textChanged(QString)),this,SLOT(changeEpsilon(QString)));
    layout->addWidget(epsilonEdit);

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

    layout->addLayout(opLayout);
    setLayout(layout);
}

void SettingsDialog::changeAlphabet(QString val)
{
    alphabet = val;
}

void SettingsDialog::changeEpsilon(QString val)
{
    if(val.length() > 0)
        epsilon = val.at(0);
    else
        epsilon = '\0';
}

void SettingsDialog::typeSelection()
{
    QTextCursor cursor;
    cursor = typeSel->textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    typeSel->setTextCursor(cursor);
    if(cursor.selectedText() == "NFA")
    {
        type = AutomaGraphicsView::AutomaType::NFA;
        epsilonEdit->setEnabled(true);
        epsilonEdit->setToolTip("Qui va inserito il simbolo utilizzato per rappresentare epsilon");
        alphabetEdit->setEnabled(false);
        alphabetEdit->setToolTip("Disponibile solo per i DFA");
    }
    else if(cursor.selectedText() == "DFA")
    {
        type = AutomaGraphicsView::AutomaType::DFA;
        epsilonEdit->setEnabled(false);
        epsilonEdit->setToolTip("Disponibile solo per i DFA e i PDA");
        alphabetEdit->setEnabled(true);
        alphabetEdit->setToolTip("Ogni carattere presente qui verra' considerato parte dell'alfabeto di questo DFA");
    }else
    {
        type = AutomaGraphicsView::AutomaType::PDA;
        epsilonEdit->setEnabled(true);
        epsilonEdit->setToolTip("Qui va inserito il simbolo utilizzato per rappresentare epsilon");
        alphabetEdit->setEnabled(false);
        alphabetEdit->setToolTip("Disponibile solo per i DFA");
    }

}

void SettingsDialog::accept()
{
    QMessageBox * temp;
    bool error = false;
    if(type == AutomaGraphicsView::AutomaType::NFA || type == AutomaGraphicsView::AutomaType::PDA)
    {
        if(epsilon == '\0')
        {
            error = true;
            temp = new QMessageBox("Errore", "Epsilon non puo' essere lasciato vuoto",
                                   QMessageBox::Warning,
                                   QMessageBox::Ok,
                                   QMessageBox::NoButton,
                                   QMessageBox::NoButton,this);
            temp->show();
        }
    }
    else
        if(alphabet == "")
        {
            error = true;
            temp = new QMessageBox("Errore", "Deve essere presente almeno un carattere nell'alfabeto",
                                   QMessageBox::Warning,
                                   QMessageBox::Ok,
                                   QMessageBox::NoButton,
                                   QMessageBox::NoButton,this);
            temp->show();
        }
    if(!error)
        QDialog::accept();
}
