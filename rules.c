#include "rules.h"
#include <stdio.h>

/*
 * Vérifie si une case est disponible (-1) ou pas (t[index])
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
    return -1;
}

/*
 * x - 1 = Ouest
 * x + 1 = Est
 * y - 1 = Nord
 * y + 1 = Sud
 */
int NextTowers(Point P, int * T)
{
    Point p; Direction d;

    if (!P.x && !P.y) //(0,0)
    {
        p.x = P.x + 1; p.y = P.y;
        if (caseIsAvailable(p, T) != -1)
            return d = E;
    }

    if (P.x && !P.y) //(x,0)
    {
        
    }

    p.x -= 1; p.y = P.y;
    if (caseIsAvailable(p, T) != -1)
        return d = O;
    
    p.x += 2;
    if (caseIsAvailable(p, T) != -1)
        return d = E;
    
    p.x = P.x; p.y -= 1;
    if (caseIsAvailable(p, T) != -1)
        return d = N;
    
    p.y += 2;
    if (caseIsAvailable(p, T) != -1)
        return d = S;
}