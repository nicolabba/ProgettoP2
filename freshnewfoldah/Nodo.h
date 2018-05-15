#pragma once
#include <list>
using namespace std;
class Nodo
{
private:
	string nome;
	bool finale;
	list<link> conn;
public:
	Nodo();
	~Nodo();
	void add(link);
	void remove(link);
	virtual link get(Nodo, char); //nodo dest
};
