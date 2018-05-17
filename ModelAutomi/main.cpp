#include <iostream>
#include "nfa.h"
using namespace std;

int main()
{
    NFA automa = NFA();
    automa.addStato("q0");
    automa.addStato("q1");
    automa.addStato("q2");
    automa["q0"]->add(automa["q0"],'a');
    automa["q0"]->add(automa["q1"],'\0');
    automa["q1"]->add(automa["q1"],'b');
    automa["q1"]->add(automa["q2"],'\0');
    automa["q2"]->add(automa["q2"],'c');
    automa["q2"]->setFinale(true);
    automa.setStartingState("q0");
    vector<string> prove = {"aaabbbccc","bbbccc","ccc","baca","cccaaa","cbb","","prova", "aacc"};
    for(unsigned int i = 0; i<prove.size(); i++)
    {
        cout << "\"" << prove[i] << "\" = " << (automa.start(prove[i])?"":"non ") << "accettata" << endl;
    }
    return 0;
}
