#include "fortress.h"
#include <stdio.h>

/*
 * Vérifie si une case est disponible (1) ou pas (t[valeur])
 */
int caseIsAvailable(Point P, int * T)
{
    int index = (P.y * LENGTH) + P.x;
    switch (T[index])
    {
        case -3 ... -1: 
            return index;
        case 1 ... 3:
            return index;
    }      
    return 1;
}