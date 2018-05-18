#include <iostream>
#include "nfa.h"
using namespace std;

int main()
{
    NFA a = NFA();
    AbstractAutoma *automa = &a;
    automa->addStato("q0");
    automa->addStato("q1");
    automa->addStato("q2");
    automa->getStato("q0")->add(automa->getStato("q0"),'a');
    automa->getStato("q0")->add(automa->getStato("q1"),'\0');
    automa->getStato("q1")->add(automa->getStato("q1"),'b');
    automa->getStato("q1")->add(automa->getStato("q2"),'\0');
    automa->getStato("q2")->add(automa->getStato("q2"),'c');
    automa->getStato("q2")->setFinale(true);
    automa->setStartingState("q0");
    vector<string> prove = {"aaabbbccc","bbbccc","ccc","baca","cccaaa","cbb","","prova", "aacc"};
    for(unsigned int i = 0; i<prove.size(); i++)
    {
        cout << "\"" << prove[i] << "\" = " << (automa->start(prove[i])?"":"non ") << "accettata" << endl;
    }
    return 0;
}
