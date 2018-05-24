#include <iostream>
#include "nfa.h"
#include "dfa.h"
#include "npda.h"

using namespace std;

int main()
{
    NFA *automa = new NFA();
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


    DFA *automa2 = new DFA();
    automa2->setAlfabeto("abc");
    automa2->addStato("q0q1q2");
    automa2->addStato("q1q2");
    automa2->addStato("q2");
    automa2->addStato("0");
    automa2->getStato("q0q1q2")->add(automa2->getStato("q0q1q2"),'a');
    automa2->getStato("q0q1q2")->add(automa2->getStato("q1q2"),'b');
    automa2->getStato("q0q1q2")->add(automa2->getStato("q2"),'c');
    automa2->getStato("q1q2")->add(automa2->getStato("q1q2"),'b');
    automa2->getStato("q1q2")->add(automa2->getStato("q2"),'c');
    automa2->getStato("q1q2")->add(automa2->getStato("0"),'a');
    automa2->getStato("q2")->add(automa2->getStato("q2"),'c');
    automa2->getStato("q2")->add(automa2->getStato("0"),'a');
    automa2->getStato("q2")->add(automa2->getStato("0"),'b');
    automa2->getStato("0")->add(automa2->getStato("0"),'c');
    automa2->getStato("0")->add(automa2->getStato("0"),'a');
    automa2->getStato("0")->add(automa2->getStato("0"),'b');
    automa2->getStato("q0q1q2")->setFinale(true);
    automa2->getStato("q1q2")->setFinale(true);
    automa2->getStato("q2")->setFinale(true);
    automa2->setStartingState("q0q1q2");

    NPDA *automa3 = new NPDA();
    automa3->addStato("q0");
    automa3->addStato("q1");
    automa3->getStato("q0")->add(automa3->getStato("q0"),'a','\0',"a");
    automa3->getStato("q0")->add(automa3->getStato("q0"),'b','\0',"b");
    automa3->getStato("q0")->add(automa3->getStato("q1"),'\0','\0',"");
    automa3->getStato("q1")->add(automa3->getStato("q1"),'a','a',"");
    automa3->getStato("q1")->add(automa3->getStato("q1"),'b','b',"");
    automa3->getStato("q1")->setFinale(true);
    automa3->setStartingState("q0");

    cout << "Verifica NFA & DFA" << endl;
    vector<string> prove = {"aaabbbccc","bbbccc","ccc","baca","cccaaa","cbb","","prova", "aacc"};
    for(unsigned int i = 0; i<prove.size(); i++)
    {
        cout << "NFA: \"" << prove[i] << "\" = " << (automa->start(prove[i])?"":"non ") << "accettata" << endl;
        cout << "DFA: \"" << prove[i] << "\" = " << (automa2->start(prove[i])?"":"non ") << "accettata" << endl;
    }

    cout << "Verifica NPDA" << endl;
    prove = {"","aa","bb","aba","abbb","abba","abbabbabbabaababbabbabba"};

    for(unsigned int i = 0; i<prove.size(); i++)
    {
        cout << "NPDA: \"" << prove[i] << "\" = " << (automa3->start(prove[i])?"":"non ") << "accettata" << endl;
    }
    return 0;
}
