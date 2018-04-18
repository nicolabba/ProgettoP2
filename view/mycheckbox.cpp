#include "mycheckbox.h"
#include <QVBoxLayout>
myCheckBox::myCheckBox(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    attivo = true;
    bottone = new QPushButton(this);
    connect(bottone,SIGNAL(pressed()),this,SLOT(pressed()));
    layout->addWidget(bottone,1);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void myCheckBox::pressed()
{
    attivo = !attivo;
    setChecked(attivo);
    emit stateChanged(attivo);
}

void myCheckBox::setChecked(bool act)
{
    attivo = act;
    if(attivo)
    {
        bottone->setStyleSheet("height:30px; width:30px; background-color:#3D7848");
    }else
    {
        bottone->setStyleSheet("height:30px; width:30px; background-color:lightgreen");
    }
}

bool myCheckBox::isChecked()
{
    return attivo;
}
