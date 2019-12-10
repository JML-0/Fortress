/*
    - 6 lettres de longueur et 1 lettre de hauteur (3 si on compte le plafond + le bas)
    - Un tableau de 8 * 8 entrées en integer
    - 0 = tour morte ou case vide | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA
*/

#include "rules.h"
#include <stdlib.h>
#include <stdio.h>

int * creerTableau();
void afficherTableau(int* tableau);
void jouer(int* tableau);

int main(void) {
    int * tableau = creerTableau();

    afficherTableau(tableau);

    Point p;
    p.x = 0;
    p.y = 7;
    printf("Adresse de la case du point (%d,%d) ---> %p\n", p.x, p.y, caseIsAvailable(p, tableau));

    int * test;
    test = nextTowers(p, tableau);
    printf("Tour au Nord -> %d\n", test[N]);
    printf("Tour a l'Est -> %d\n", test[E]);
    printf("Tour au Sud -> %d\n", test[S]);
    printf("Tour a l'Ouest -> %d\n", test[O]);
    
    jouer(tableau);
}

int * creerTableau()
{
    int size = (WIDTH * LENGTH) - 1;
    int * tab = malloc(sizeof(int) * size);

    //tab[5] = 1; //T1
    tab[56] = 1; //TT1
    tab[57] = -3; //TTT2

    return tab;
}

void afficherTableau(int* tableau) {
    printf("[Y/X]");
    for(int ia = 0; ia < LENGTH; ia++)
            printf("( %d )", ia);
    
    printf("\n");

    for(int i = 0; i < WIDTH; i++) {

        printf("(%d)  |", i);
        for(int ib = 0; ib < LENGTH; ib++) {
            switch(tableau[(i * WIDTH) + ib]) {
                case -1:
                    printf("T2  |");
                    break;

                case -2:
                    printf("TT2 |");
                    break;

                case -3:
                    printf("TTT2|");
                    break;

                case 1:
                    printf("T1  |");
                    break;

                case 2:
                    printf("TT1 |");
                    break;

                case 3:
                    printf("TTT1|");
                    break;

                default:
                    printf("    |");
                    break;
            }
            //printf(" %d |", tableau[(i * HAUTEUR) + ib]);
        }

        printf("\n     ");

        for(int ia = 0; ia < LENGTH * 5; ia++)
            printf("-");

        printf("\n");
    }

    //printf("\nRAPPEL: 0 = tour morte | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA\n");

}

void jouer(int* tableau) {
    int joue = 1;

    while(joue) {
        int ok = 1;
        afficherTableau(tableau);

        while(ok) {

            int x, y;
            do {
                printf("\nCoordonnée X: ");
                scanf("%d", &x);
            } while(x >= LENGTH);
            
            do {
                printf("\nCoordonnée Y: ");
                scanf("%d", &y);
            } while(y >= WIDTH);
            
            int valeur = tableau[(y * WIDTH) + x];
            if(valeur >= 0 && valeur < 3) {
                tableau[(y * WIDTH) + x]++;
                ok = 0;
            }

            if(ok == 1) {
                printf("\nVeuillez rejouer sur une autre case\n");
            }
        }
        
        //Faire jouer l'IA ici
    }
}