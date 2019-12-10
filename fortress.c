/*
    - 6 lettres de longueur et 1 lettre de hauteur (3 si on compte le plafond + le bas)
    - Un tableau de 8 * 8 entrées en integer
    - 0 = tour morte ou case vide | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA
*/

#include "fortress.h"
#include "rules.h"
#include <stdlib.h>
#include <stdio.h>

int* creerTableau();
void afficherTableau(int* tableau);

#define HAUTEUR 8
#define LONGUEUR 8

int main(void) {
    int * tableau = creerTableau();

    afficherTableau(tableau);

    Point p;
    p.x = 5;
    p.y = 1;
    printf("-----> %d\n", caseIsAvailable(p, tableau));
}

int* creerTableau() {
    int taille = (HAUTEUR * LONGUEUR) - 1;
    int* tab = malloc(sizeof(int) * taille);

    //Le remplir de case vide
    for(int i = 0; i < (taille + 1); i++)
        tab[i] = 0;

    tab[5] = 1; //T1
    tab[12] = 2; //TT1
    tab[22] = -3; //TTT2

    return tab;
}

void afficherTableau(int* tableau) {
    printf("[Y/X]");
    for(int ia = 0; ia < LONGUEUR; ia++)
            printf("( %d )", ia);
    
    printf("\n");

    for(int i = 0; i < HAUTEUR; i++) {

        printf("(%d) |", i);
        for(int ib = 0; ib < LONGUEUR; ib++) {
            switch(tableau[(i * HAUTEUR) + ib]) {
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

        for(int ia = 0; ia < LONGUEUR * 5; ia++)
            printf("-");

        printf("\n");
    }

    printf("\nRAPPEL: 0 = tour morte | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA\n");

}