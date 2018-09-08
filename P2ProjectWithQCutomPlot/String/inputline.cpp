#include "inputline.h"
#include <QHBoxLayout>
InputLine::InputLine(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("InputLine{background-color: white;}");
    input = new QLineEdit(this);
    input->setToolTip("Qui possono essere inserite le stringhe su cui operare");
    check = new myCheckBox(this);
    check->setToolTip("Qui puoi selezionare su quali stringhe operare, quelle scure sono attive");
    check->setChecked(true);

    input->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #c6ffac;}");
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
    if(act)
        input->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #c6ffac;}");
    else
        input->setStyleSheet("QLineEdit{height: 30px; border: none; selection-background-color:darkgray; background-color: #e6ffcc;}");

    emit activeChanged(act);
}
QString InputLine::getValue() const
{
    return input->text();
}
bool InputLine::getActive() const
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
