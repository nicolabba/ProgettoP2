#include "stdafx.h"
#include "pdalink.h"

pdalink::pdalink(Nodo n, char i, char h, char* nh):link(n,i), head(h)
{
	newhead = new char[2]{ nh[0], nh[1] };
}

pdalink::~pdalink()
{
}
