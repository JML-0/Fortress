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

    afficherTableau(show(tableau));

    Point p;
    p.x = 0;
    p.y = 7;
    printf("Case disponible au point (%d,%d) ? ---> %d\n", p.x, p.y, caseIsAvailable(p, tableau));


    int * test;
    test = nextTowers(p, tableau);
    printf("Tour au Nord -> %d\n", test[N]);
    printf("Tour a l'Est -> %d\n", test[E]);
    printf("Tour au Sud -> %d\n", test[S]);
    printf("Tour a l'Ouest -> %d\n", test[O]);

    printf("%d\n", tableau[55]);
    printf("%p\n", getAddressTowerDirection(p, tableau, S));

    jouer(tableau);

    free(test); free(tableau);
}

int * creerTableau()
{
    int size = (WIDTH * LENGTH) - 1;
    int * tab = malloc(sizeof(int) * size);
    

    /*tab[42] = 10; //TTT2
    tab[49] = 10; //T1
    tab[51] = 10; //T1
    tab[56] = 10; //TT1
    tab[58] = 10; //TTT2

    tab[60] = 20;
    tab[0] = 20;

    tab[14] = -10;
    tab[21] = -10;
    tab[28] = 10;*/

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
                case 1:
                    printf("+1  |");
                    break;
                case 2:
                    printf("+2  |");
                    break;
                case 3:
                    printf("+3  |");
                    break;
                case 4:
                    printf("+4  |");
                    break;

                case -1:
                    printf("-1  |");
                    break;
                case -2:
                    printf("-2  |");
                    break;
                case -3:
                    printf("-3  |");
                    break;
                case -4:
                    printf("-4  |");
                    break;

                case -10:
                    printf("T2  |");
                    break;
                case -20:
                    printf("TT2 |");
                    break;

                case -30:
                    printf("TTT2|");
                    break;

                case 10:
                    printf("T1  |");
                    break;

                case 20:
                    printf("TT1 |");
                    break;

                case 30:
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

void jouer(int* tableau) {
    int joue = 1;

    while(joue) {
        int ok = 1;
        afficherTableau(show(tableau));

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
            if(valeur >= 0 && valeur < 30) {
                printf("KKKKKKKKK -> %d\n", valeur);
                tableau[(y * WIDTH) + x] += 10;
                ok = 0;
            }

            if(ok == 1) {
                printf("\nVeuillez rejouer sur une autre case\n");
            }
        }
        
        //Faire jouer l'IA ici
    }
}