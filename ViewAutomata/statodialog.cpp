#include "statodialog.h"
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QMessageBox>
#include <QCheckBox>

StatoDialog::StatoDialog(QWidget * parent, Qt::WindowFlags f, QString name, bool starting, bool final):QDialog(parent, f), text(name), iniziale(starting), finale(final)
{
    this->setModal(true);
    this->setFixedSize(200,150);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();

    QLineEdit* input = new QLineEdit(name ,this);
    input->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;");
    connect(input,SIGNAL(textChanged(QString)),this,SLOT(editInput(QString)));
    layout->addWidget(input);

    QCheckBox* cIniziale = new QCheckBox("Iniziale", this);
    QCheckBox* cFinale = new QCheckBox("Finale", this);
    cIniziale->setChecked(starting);
    cFinale->setChecked(final);
    if (starting)
        cIniziale->setEnabled(false);
    connect(cIniziale,SIGNAL(toggled(bool)),this,SLOT(changeIniziale(bool)));
    connect(cFinale,SIGNAL(toggled(bool)),this,SLOT(changeFinale(bool)));
    layout->addWidget(cIniziale);
    layout->addWidget(cFinale);

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

QString StatoDialog::getInput()
{
    return text;
}

bool StatoDialog::getIniziale()
{
    return iniziale;
}

bool StatoDialog::getFinale()
{
    return finale;
}

void StatoDialog::editInput(QString input)
{
    text = input;
}

void StatoDialog::changeIniziale(bool val)
{
    iniziale = val;
}

void StatoDialog::changeFinale(bool val)
{
    finale = val;
}

void StatoDialog::accept()
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
