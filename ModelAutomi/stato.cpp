#include "stato.h"

Stato::Stato(const std::string & n, const bool & f):nome(n),finale(f)
{

}

std::string Stato::getNome()
{
    return nome;
}

bool Stato::isFinale()
{
    return finale;
}

void Stato::setFinale(bool f)
{
    finale = f;
}


