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

int main(void) {
    int * tableau = creerTableau();

    afficherTableau(tableau);

    Point p;
    p.x = 4;
    p.y = 1;
    printf("-----> %d\n", caseIsAvailable(p, tableau));
}

int * creerTableau()
{
    int size = (WIDTH * LENGTH) - 1;
    int * tab = malloc(sizeof(int) * size);

    //tab[5] = 1; //T1
    tab[12] = 1; //TT1
    //tab[22] = -3; //TTT2

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

    printf("\nRAPPEL: 0 = tour morte | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA\n");

}