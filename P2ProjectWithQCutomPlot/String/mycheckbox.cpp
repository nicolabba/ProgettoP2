#include "mycheckbox.h"
#include <QVBoxLayout>
myCheckBox::myCheckBox(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    active = true;
    button = new QPushButton(this);
    connect(button,SIGNAL(pressed()),this,SLOT(pressed()));
    layout->addWidget(button,1);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void myCheckBox::pressed()
{
    active = !active;
    setChecked(active);
    emit stateChanged(active);
}

void myCheckBox::setChecked(bool act)
{
    active = act;
    if(active)
    {
        button->setStyleSheet("QPushButton{height:30px; width:30px; background-color:#3D7848; border: none;}");
    }else
    {
        button->setStyleSheet("QPushButton{height:30px; width:30px; background-color:lightgreen; border: none;}");
    }
}

bool myCheckBox::isChecked() const
{
    return active;
}
