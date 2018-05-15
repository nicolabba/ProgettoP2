#pragma once
#include "link.h"
class pdalink :
	public link
{
	char head;
	char* newhead;
public:
	pdalink(Nodo, char, char, char[2]);
	~pdalink();
	
};

