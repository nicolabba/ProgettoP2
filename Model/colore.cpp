#include "colore.h"

int Colore::getShade(Primari p) const
{
    switch (p) {
    case 1:
        return prim1;
        break;
    case 2:
        return prim2;
        break;
    case 3:
        return prim3;
        break;
    }
}

