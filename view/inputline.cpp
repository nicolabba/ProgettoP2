#include "inputline.h"
#include <QHBoxLayout>
InputLine::InputLine(QWidget *parent) :
    QWidget(parent)
{
    input = new QLineEdit(this);
    check = new QCheckBox(this);
    check->setChecked(true);

    input->setStyleSheet("height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc; margin-left:7px");
    check->setStyleSheet("QCheckBox::indicator{height:30px; width:30px; border:none;} QCheckBox::indicator::checked{background-color:#3D7848}QCheckBox::indicator::unchecked{background-color:lightgreen}");
    connect(input,SIGNAL(textEdited(QString)),this,SIGNAL(valueChanged(QString)));
    connect(check,SIGNAL(stateChanged(int)), this, SLOT(changeActivation(int)));
    connect(this,SIGNAL(changeActive(bool)),check,SLOT(setChecked(bool)));
    connect(this,SIGNAL(changeVal(QString)),input,SLOT(setText(QString)));
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(input);//,0,Qt::AlignCenter);
    layout->addWidget(check);//,0,Qt::AlignCenter);
    setLayout(layout);
}
void InputLine::changeActivation(int i)
{
    emit activeChanged(i>0);
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
