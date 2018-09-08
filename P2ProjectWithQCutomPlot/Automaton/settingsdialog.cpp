#include "settingsdialog.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include <QLabel>

AutomatonGraphicsView::AutomaType SettingsDialog::getType() const
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

SettingsDialog::SettingsDialog(QWidget * parent, Qt::WindowFlags f, AutomatonGraphicsView::AutomaType type, const QString& alphabet, const QChar& epsilon):QDialog(parent,f),type(type),alphabet(alphabet),epsilon(epsilon)
{
    this->setModal(true);
    this->setFixedSize(200,265);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();

    QLabel * alphabetLabel = new QLabel("Alfabeto:",this);
    alphabetEdit = new QLineEdit(alphabet ,this);
    alphabetEdit->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    connect(alphabetEdit,SIGNAL(textChanged(QString)),this,SLOT(changeAlphabet(QString)));

    QLabel * epsilonLabel = new QLabel("Epsilon:",this);
    epsilonEdit = new QLineEdit(epsilon ,this);
    epsilonEdit->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    epsilonEdit->setMaxLength(1);
    connect(epsilonEdit,SIGNAL(textChanged(QString)),this,SLOT(changeEpsilon(QString)));


    QLabel * typeLabel = new QLabel("Tipo:",this);
    typeSel = new QTextEdit(this);
    typeSel->setStyleSheet("QTextEdit{border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");
    typeSel->setReadOnly(true);
    typeSel->setToolTip("Qui puoi selezionare il tipo di automa");
    typeSel->append("NFA\nDFA\nPDA");
    int index;
    switch(type)
    {
    case AutomatonGraphicsView::AutomaType::NFA:
        index = 0;
        alphabetEdit->setEnabled(false);
        break;
    case AutomatonGraphicsView::AutomaType::DFA:
        index = 4;
        epsilonEdit->setEnabled(false);
        break;
    case AutomatonGraphicsView::AutomaType::PDA:
        index = 8;
        alphabetEdit->setEnabled(false);
        break;
    }
    QTextCursor cursor;
    cursor = typeSel->textCursor();
    cursor.setPosition(index);
    //typeSelection();
    cursor.movePosition(QTextCursor::StartOfBlock,QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    typeSel->setTextCursor(cursor);
    connect(typeSel, SIGNAL(cursorPositionChanged()), this, SLOT(typeSelection()));

    layout->addWidget(typeLabel);
    layout->addWidget(typeSel);

    layout->addWidget(alphabetLabel);
    layout->addWidget(alphabetEdit);

    layout->addWidget(epsilonLabel);
    layout->addWidget(epsilonEdit);

    QString ButtonStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; height:35px }";
    QPushButton* ok, *cancel;
    ok = new QPushButton("Ok", this);
    cancel = new QPushButton("Cancel", this);
    ok->setStyleSheet(ButtonStyleSheet);
    cancel->setStyleSheet(ButtonStyleSheet);
    connect(ok,SIGNAL(pressed()),this,SLOT(accept()));
    connect(cancel,SIGNAL(pressed()),this,SLOT(reject()));
    //opLayout->addStretch(1);
    opLayout->addWidget(ok,1);
    opLayout->addWidget(cancel,1);
    //opLayout->addStretch(1);

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
        type = AutomatonGraphicsView::AutomaType::NFA;
        epsilonEdit->setEnabled(true);
        epsilonEdit->setToolTip("Qui va inserito il simbolo utilizzato per rappresentare epsilon");
        alphabetEdit->setEnabled(false);
        alphabetEdit->setToolTip("Disponibile solo per i DFA");
        alphabetEdit->setText("");
    }
    else if(cursor.selectedText() == "DFA")
    {
        type = AutomatonGraphicsView::AutomaType::DFA;
        epsilonEdit->setEnabled(false);
        epsilonEdit->setToolTip("Disponibile solo per i DFA e i PDA");
        alphabetEdit->setEnabled(true);
        alphabetEdit->setToolTip("Ogni carattere presente qui verra' considerato parte dell'alfabeto di questo DFA");
        epsilonEdit->setText("");
    }else
    {
        type = AutomatonGraphicsView::AutomaType::PDA;
        epsilonEdit->setEnabled(true);
        epsilonEdit->setToolTip("Qui va inserito il simbolo utilizzato per rappresentare epsilon");
        alphabetEdit->setEnabled(false);
        alphabetEdit->setToolTip("Disponibile solo per i DFA");
        alphabetEdit->setText("");
    }

}

void SettingsDialog::accept()
{
    QMessageBox * temp;
    bool error = false;
    QString message;
    if(type == AutomatonGraphicsView::AutomaType::NFA || type == AutomatonGraphicsView::AutomaType::PDA)
    {
        if(epsilon == '\0')
        {
            error = true;
            message = "Epsilon non puo' essere lasciato vuoto";
        }
    }
    else
        if(alphabet == "")
        {
            error = true;
            message = "Deve essere presente almeno un carattere nell'alfabeto";
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
