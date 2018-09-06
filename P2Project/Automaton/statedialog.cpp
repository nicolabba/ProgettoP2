#include "statedialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>

StateDialog::StateDialog(QWidget * parent, Qt::WindowFlags f, QString name, bool starting, bool final):QDialog(parent, f), text(name), starting(starting), final(final)
{
    this->setModal(true);
    this->setFixedSize(200,150);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();

    QLabel * nameLabel = new QLabel("Nome:",this);
    layout->addWidget(nameLabel);

    QLineEdit* input = new QLineEdit(name ,this);
    input->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    connect(input,SIGNAL(textChanged(QString)),this,SLOT(setInput(QString)));
    layout->addWidget(input);

    QCheckBox* cStarting = new QCheckBox("Iniziale", this);
    QCheckBox* cFinal = new QCheckBox("Finale", this);
    cStarting->setChecked(starting);
    cFinal->setChecked(final);
    if (starting)
        cStarting->setEnabled(false);
    connect(cStarting,SIGNAL(toggled(bool)),this,SLOT(setStarting(bool)));
    connect(cFinal,SIGNAL(toggled(bool)),this,SLOT(setFinal(bool)));
    layout->addWidget(cStarting);
    layout->addWidget(cFinal);

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

    layout->addLayout(opLayout,0);
    this->setLayout(layout);
}

QString StateDialog::getInput()
{
    return text;
}

bool StateDialog::getStarting()
{
    return starting;
}

bool StateDialog::getFinal()
{
    return final;
}

void StateDialog::setInput(QString input)
{
    text = input;
}

void StateDialog::setStarting(bool val)
{
    starting = val;
}

void StateDialog::setFinal(bool val)
{
    final = val;
}

void StateDialog::accept()
{
    if(text == "")
    {
        QMessageBox * temp = new QMessageBox("Errore", "Il nome dello stato non puo' essere lasciato vuoto",
                                             QMessageBox::Warning,
                                             QMessageBox::Ok,
                                             QMessageBox::NoButton,
                                             QMessageBox::NoButton,this);
        temp->show();
    }
    else
        QDialog::accept();
}
