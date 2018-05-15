#pragma once
#include "Nodo.h"
#include <list>
using namespace std;
class link
{
private:
	Nodo dest;
	char input;
public:	
	link(Nodo, char = 0);
	~link();
};

