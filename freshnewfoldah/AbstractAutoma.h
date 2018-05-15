#pragma once
#include "Nodo.h"
#include <list>
using namespace std;
class AbstractAutoma
{
private:
	list<Nodo> nodi;

public:
	virtual bool start(string) = 0;
	virtual void add(Nodo) = 0;
	virtual void remove(Nodo) = 0;

};

