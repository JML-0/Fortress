#include "rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Vérifie si une case est disponible (1) ou pas (0)
 */
int caseIsAvailable(Point P, int * T)
{
    int index = (P.y * LENGTH) + P.x;
    switch (T[index])
    {
        case -300 ... -100:
            return 0;
        case 100 ... 300:
            return 0;
    }      

    return 1;
}

/*
 * Retourne un tableau contenant les infos si une ou plusieurs tours se trouvent autour
 * 
 * -1 = hors tableau
 * 0 = tour a coter
 * 1 = pas de tour
 * 
 * x - 1 = Ouest
 * x + 1 = Est
 * y - 1 = Nord
 * y + 1 = Sud
 */
int * nextTowers(Point P, int * T)
{
    Point p; p.x = P.x; p.y = P.y;
    int * R;
    R = malloc(sizeof(int) * 4); assert(R);

    p.y -= 1;
    if (p.y < 0) R[N] = -1;
    else
    R[N] = caseIsAvailable(p, T);

    p.y += 1; p.x += 1;
    if (p.x > LENGTH - 1) R[E] = -1;
    else
    R[E] = caseIsAvailable(p, T);
    
    p.y += 1; p.x -= 1;
    if (p.y > WIDTH - 1) R[S] = -1;
    else
    R[S] = caseIsAvailable(p, T);
    
    p.y -= 1; p.x -= 1;
    if (p.x < 0) R[O] = -1;
    else
    R[O] = caseIsAvailable(p, T);
    
    return R;
}

/*
 * Retoune l'index du point donné
 */
int getIndex(Point P) { return (P.y * WIDTH) + P.x; } 

/*
 * Retourne l'index du point donné en fonction d'une direction
 */
int getIndexDirection(Point P, Direction D)
{
    switch (D)
    {
    case N:
        return ((P.y - 1 ) * LENGTH) + P.x;
    case E:
        return (P.y * LENGTH) + P.x + 1;
    case S:
        return ((P.y + 1) * LENGTH) + P.x;
    case O:
        return (P.y * LENGTH) + P.x - 1;
    }
}

void setValue(Point P, Direction D, int * T, int * R, int S)
{
    if (S)
    {
        if (R[getIndexDirection(P, D)] == 99) //différence entre case vide et 0
            R[getIndexDirection(P, D)] = 0;

        R[getIndexDirection(P, D)] += T[getIndex(P)] / 100; 

        if (R[getIndexDirection(P, D)] == 0)
            R[getIndexDirection(P, D)] = 99;
    }
    else
    {
        if (R[getIndexDirection(P, D)] == 99) 
            R[getIndexDirection(P, D)] = 0;

        R[getIndexDirection(P, D)] -= -T[getIndex(P)] / 100;

        if (R[getIndexDirection(P, D)] == 0)
            R[getIndexDirection(P, D)] = 99;
    }
}

int * show(int * T)
{
    Point p;
    int * R, * _nextTowers;

    R           = malloc(sizeof(int) * (LENGTH * WIDTH));       assert(R);
    _nextTowers = malloc(sizeof(int) * 4);                      assert(_nextTowers);

    deleteTowers(T); //tour a supprimer

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            p.x = j; p.y = i;

            if (!caseIsAvailable(p , T)) // une tour
            {
                _nextTowers = nextTowers(p, T);
                
                switch (T[getIndex(p)])
                {
                    case -300 ... -100: //tour -
                        if (_nextTowers[E] == 1) setValue(p, E, T, R, 0); // pas de tour à l'Est
                        
                        if (_nextTowers[S] == 1) setValue(p, S, T, R, 0);

                        if (_nextTowers[O] == 1) setValue(p, O, T, R, 0);
                        
                        if (_nextTowers[N] == 1) setValue(p, N, T, R, 0);

                        R[getIndex(p)] = T[getIndex(p)]; //Tour

                        break;
                    case 100 ... 300: //tour +
                        if (_nextTowers[E] == 1) setValue(p, E, T, R, 1);
                        
                        if (_nextTowers[S] == 1) setValue(p, S, T, R, 1);

                        if (_nextTowers[O] == 1) setValue(p, O, T, R, 1);
                        
                        if (_nextTowers[N] == 1) setValue(p, N, T, R, 1);

                        R[getIndex(p)] = T[getIndex(p)];

                        break;
                    default:
                        break;
                }
            }
        }
    }
    free(_nextTowers);

    return R;
}

/*
 * Supprime les tours lorsqu'elles ne dominent pas l'adversaire
 */
void deleteTowers(int * T)
{
    Point P;
    int Tower, TN, TE, TS, TO, Total;
    int * _nextTowers;

    _nextTowers = malloc(sizeof(int) * 4);  assert(_nextTowers);

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            P.x = j; P.y = i;
            Tower = T[getIndex(P)]; //Tour actuelle;
            TN = TE = TS = TO = 0;          //Tour Nord Est Sud Ouest
            _nextTowers = nextTowers(P, T);

            if (_nextTowers[N] == 0) TN = T[getIndexDirection(P, N)];  //
            if (_nextTowers[E] == 0) TE = T[getIndexDirection(P, E)];  //  Valeur des tours si présentes
            if (_nextTowers[S] == 0) TS = T[getIndexDirection(P, S)];  //
            if (_nextTowers[O] == 0) TO = T[getIndexDirection(P, O)];  //

            Total = TN + TE + TS + TO; //Somme des valeurs des tours adjacentes

            if ((Tower > 0) && (Tower + Total < 0)) //Tour +
                T[getIndex(P)] = Total / 100;

            if ((Tower < 0) && (Tower + Total > 0)) // Tour -
                T[getIndex(P)] = Total / 100;
        }        
    }
    free(_nextTowers);
}