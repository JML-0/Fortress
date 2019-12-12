#include <stdio.h>
#include "controls.h"

/*
 * Retourne la valeur à mettre pour une tour selon la case sélectionnée
 */
int caseValue(Point P, int * T)
{
    int V = T[getIndex(P)];
    if(V >= 0 && V < 100)   return 100;
    if(V >= 100 && V < 300) return V + 100;
    if(V == -1)             return V + 101;
    return 0;
}

int playerStillHaveTowers(int * T) 
{
    for(int i = 0; i < WIDTH; i++)
        for(int ib = 0; ib < LENGTH; ib++)
            if(T[(i * WIDTH) + ib] >= 0 && T[(i * WIDTH) + ib] <= 300)
                return 1;

    return 0;
}