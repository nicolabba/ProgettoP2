#include "inputline.h"
#include <QHBoxLayout>
InputLine::InputLine(QWidget *parent) :
    QWidget(parent)
{
    input = new QLineEdit(this);
    check = new myCheckBox(this);
    check->setChecked(true);

    input->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc; ");
    connect(input,SIGNAL(textEdited(QString)),this,SIGNAL(valueChanged(QString)));
    connect(check,SIGNAL(stateChanged(bool)), this, SLOT(changeActivation(bool)));
    connect(this,SIGNAL(changeActive(bool)),check,SLOT(setChecked(bool)));
    connect(this,SIGNAL(changeVal(QString)),input,SLOT(setText(QString)));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(input);
    layout->addWidget(check);
    setLayout(layout);
}
void InputLine::changeActivation(bool act)
{
    emit activeChanged(act);
}
QString InputLine::getValue()
{
    return input->text();
}
bool InputLine::getActive()
{
    return check->isChecked();
}
void InputLine::setSelection(int start, int length)
{
    input->setSelection(start,length);
}
InputLine::~InputLine()
{
}
