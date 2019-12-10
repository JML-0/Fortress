#include "rules.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Vérifie si une case est disponible
 * Retourne l'adresse de la case prise
 * Ou retourne NULL (case disponible)
 */
int * caseIsAvailable(Point P, int * T)
{
    int index = (P.y * LENGTH) + P.x;
    switch (T[index])
    {
        case -3 ... -1: 
            return &T[index];
        case 1 ... 3:
            return &T[index];
    }      
    return NULL;
}

/*
 * Retourne un tableau contenant les infos si une ou plusieurs tours se trouvent autour
 * Si une tour se trouve à coter, on stock un pointeur de celle-ci
 * 
 * -1 = hors tableau
 * *pointeur = tour a coter
 * 0 = pas de tour
 * 
 * x - 1 = Ouest
 * x + 1 = Est
 * y - 1 = Nord
 * y + 1 = Sud
 */
int * nextTowers(Point P, int * T)
{
    Point p; p.x = P.x; p.y = P.y;
    int * R, * ptr;
    R = (int *) malloc(sizeof(int) * 4);

    p.y -= 1;
    ptr = caseIsAvailable(p, T);

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.y < 0) R[N] = -1;
    else
    if (!ptr)
        R[N] = 0;
    else
        R[N] = *ptr;

    p.y += 1; p.x += 1;
    ptr = caseIsAvailable(p, T);

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.x > LENGTH - 1) R[E] = -1;
    else
    if (!ptr)
        R[E] = 0;
    else
        R[E] = *ptr;
    
    p.y += 1; p.x -= 1;
    ptr = caseIsAvailable(p, T);

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.y > WIDTH - 1) R[S] = -1;
    else
    if (!ptr)
        R[S] = 0;
    else
        R[S] = *ptr;
    
    p.y -= 1; p.x -= 1;
    ptr = caseIsAvailable(p, T);

    printf("x:%d   y:%d\n", p.x, p.y);

    if (p.x < 0) R[O] = -1;
    else
    if (!ptr)
        R[O] = 0;
    else
        R[O] = *ptr;
    
    return R;
}