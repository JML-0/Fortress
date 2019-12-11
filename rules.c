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
        case -30 ... -10: 
            return 0;
        case 10 ... 30:
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

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.y < 0) R[N] = -1;
    else
    R[N] = caseIsAvailable(p, T);

    p.y += 1; p.x += 1;

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.x > LENGTH - 1) R[E] = -1;
    else
    R[E] = caseIsAvailable(p, T);
    
    p.y += 1; p.x -= 1;

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.y > WIDTH - 1) R[S] = -1;
    else
    R[S] = caseIsAvailable(p, T);
    
    p.y -= 1; p.x -= 1;

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.x < 0) R[O] = -1;
    else
    R[O] = caseIsAvailable(p, T);
    
    return R;
}

/*
 * Retourne l'adresse d'une tour voisine en fonction d'une direction donnée
 */
int * getAddressTowerDirection(Point P, int * T, Direction D)
{
    switch (D)
    {
    case N:
        return &T[(P.y - 1 * LENGTH) + P.x];
    case E:
        return &T[(P.y * LENGTH) + P.x + 1];
    case S:
        return &T[(P.y + 1 * LENGTH) + P.x];
    case O:
        return &T[(P.y * LENGTH) + P.x - 1];
    }

    return NULL;
}

int * show(int * T)
{
    int * R;
    R = malloc(sizeof(int) * (LENGTH * WIDTH)); assert(R);

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            Point p;
            p.x = j; p.y = i;
            int isTower = caseIsAvailable(p , T);

            if (!isTower) // une tour
            {
                int * _NextTowers = malloc(sizeof(int) * 4);
                _NextTowers = nextTowers(p, T);
                
                switch (T[(i * WIDTH) + j])
                {
                    case 10:
                        if (_NextTowers[E] == 1) //pas de tour a l'Est
                        {
                            R[(i * WIDTH) + (j + 1)] += 1;
                            printf("E -> %d\n", _NextTowers[E]);
                        }
                        
                        if (_NextTowers[S] == 1) //pas de tour au Sud
                        {
                            R[((i + 1) * WIDTH) + j] += 1;
                            printf("S -> %d\n", _NextTowers[S]);
                        }

                        if (_NextTowers[O] == 1) //pas de tour a l'Ouest
                        {
                            R[(i * WIDTH) + (j - 1)] += 1;
                            printf("O -> %d\n", _NextTowers[O]);
                        }
                        
                        if (_NextTowers[N] == 1) //pas de tour au Nord
                        {
                            R[((i - 1) * WIDTH) + j] += 1;
                            printf("N -> %d\n", _NextTowers[N]);
                        }

                        R[(i * WIDTH) + j] = 10; //Tour

                        break;
                    case 20:
                        if (_NextTowers[E] == 1) //pas de tour a l'Est
                        {
                            R[(i * WIDTH) + (j + 1)] += 2;
                            printf("E -> %d\n", _NextTowers[E]);
                        }
                        
                        if (_NextTowers[S] == 1) //pas de tour au Sud
                        {
                            R[((i + 1) * WIDTH) + j] += 2;
                            printf("S -> %d\n", _NextTowers[S]);
                        }

                        if (_NextTowers[O] == 1) //pas de tour a l'Ouest
                        {
                            R[(i * WIDTH) + (j - 1)] += 2;
                            printf("O -> %d\n", _NextTowers[O]);
                        }
                        
                        if (_NextTowers[N] == 1) //pas de tour au Nord
                        {
                            R[((i - 1) * WIDTH) + j] += 2;
                            printf("N -> %d\n", _NextTowers[N]);
                        }

                        R[(i * WIDTH) + j] = 20; //Tour

                        break;
                    case 30:
                        if (_NextTowers[E] == 1) //pas de tour a l'Est
                        {
                            R[(i * WIDTH) + (j + 1)] += 3;
                            printf("E -> %d\n", _NextTowers[E]);
                        }
                        
                        if (_NextTowers[S] == 1) //pas de tour au Sud
                        {
                            R[((i + 1) * WIDTH) + j] += 3;
                            printf("S -> %d\n", _NextTowers[S]);
                        }

                        if (_NextTowers[O] == 1) //pas de tour a l'Ouest
                        {
                            R[(i * WIDTH) + (j - 1)] += 3;
                            printf("O -> %d\n", _NextTowers[O]);
                        }
                        
                        if (_NextTowers[N] == 1) //pas de tour au Nord
                        {
                            R[((i - 1) * WIDTH) + j] += 3;
                            printf("N -> %d\n", _NextTowers[N]);
                        }

                        R[(i * WIDTH) + j] = 30; //Tour

                        break;
                
                    case -10:
                        if (_NextTowers[E] == 1) //pas de tour a l'Est
                        {
                            R[(i * WIDTH) + (j + 1)] -= 1;
                            printf("E -> %d\n", _NextTowers[E]);
                        }
                        
                        if (_NextTowers[S] == 1) //pas de tour au Sud
                        {
                            R[((i + 1) * WIDTH) + j] -= 1;
                            printf("S -> %d\n", _NextTowers[S]);
                        }

                        if (_NextTowers[O] == 1) //pas de tour a l'Ouest
                        {
                            R[(i * WIDTH) + (j - 1)] -= 1;
                            printf("O -> %d\n", _NextTowers[O]);
                        }
                        
                        if (_NextTowers[N] == 1) //pas de tour au Nord
                        {
                            R[((i - 1) * WIDTH) + j] -= 1;
                            printf("N -> %d\n", _NextTowers[N]);
                        }

                        R[(i * WIDTH) + j] = -10; //Tour

                        break;
                    default:
                        break;
                }
            }
        }
    }

    return R;
}