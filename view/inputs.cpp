#include "inputs.h"
#include <QSpacerItem>
Inputs::Inputs(QWidget *parent) :QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(7);
    //QSpacerItem* item = new QSpacerItem(10,39);
    //layout->addSpacerItem(item);
    layout->addStretch(1);
    mapper = new QSignalMapper(this);
    QList<Stringa*> tempStringhe = QList<Stringa*>();
    tempStringhe.append(new Stringa());
    QList<bool> tempActive = QList<bool>();
    tempActive.append(true);
    inputs = QList<InputLine*>();
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(sendChanged(int)));
    setLayout(layout);
    refresh(tempStringhe,tempActive);
    //layout->addStretch(1);
}

void Inputs::refresh(QList<Stringa *> elements, QList<bool> active)
{
    int i = 0;
    QList<Stringa*>::iterator it;
    for(it = elements.begin(); it<elements.end()&&i<inputs.size();it++)
    {
        if(active.size() == elements.size())
            inputs[i]->changeActive(active[i]);
        inputs[i]->changeVal(QString((*it)->toString()));
        i++;
    }
    InputLine* temp;
    if(i<inputs.size())
    {
        for(int j = inputs.size()-1;j>=i;j--)
        {
            temp = inputs[j];
            layout->removeWidget(inputs[j]);
            inputs.removeAt(j);
            delete temp;
        }
    }
    else
    {
        while(i<elements.size())
        {
            temp = new InputLine();
            temp->changeVal(QString(elements[i]->toString()));
            if(active.size() == elements.size())
                temp->changeActive(active[i]);
            inputs.append(temp);
            connect(inputs[i],SIGNAL(valueChanged(QString)),mapper,SLOT(map()));
            connect(inputs[i],SIGNAL(activeChanged(bool)),mapper,SLOT(map()));
            mapper->setMapping(inputs[i],i);
            layout->addWidget(temp,0,Qt::AlignTop);
            i++;
        }
    }
}

void Inputs::sendChanged(int index)
{
    emit changed(index,inputs[index]->getValue(),inputs[index]->getActive());
}
bool Inputs::getActive(int index) const
{
    return inputs[index]->getActive();
}
QString Inputs::getValue(int index) const
{
    return inputs[index]->getValue();
}
int Inputs::getEleNumber() const
{
    return inputs.size();
}
void Inputs::setSelection(int input, int index, int length)
{
    inputs[input]->setSelection(index,length);
}
Inputs::~Inputs()
{
}
