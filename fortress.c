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
void ia(int* tableau);
int playerStillHaveTowers(int* tableau);

int main(void) {
    int * tableau = creerTableau();

    jouer(tableau);

    free(tableau);
}

int * creerTableau()
{
    int size = (WIDTH * LENGTH) - 1;
    int * tab = malloc(sizeof(int) * size);

    //tab[27] = -100;

    return tab;
}

void afficherTableau(int* tableau) {
    Point P;
    printf("[Y/X]");
    for(int ia = 0; ia < LENGTH; ia++)
            printf("( %d )", ia);
    
    printf("\n");

    for(int i = 0; i < WIDTH; i++) {

        printf("(%d)  |", i);
        for(int ib = 0; ib < LENGTH; ib++) {
            P.x = ib; P.y = i;
            switch(tableau[getIndex(P)]) {
                case 99:
                    printf(" 0  |");
                    break;
                case 1 ... 9:
                    printf("+%d  |", tableau[getIndex(P)]);
                    break;
                case 10 ... 12:
                    printf("+%d |", tableau[getIndex(P)]);
                    break;

                case -9 ... -1:
                    printf("%d  |", tableau[getIndex(P)]);
                    break;
                case -12 ... -10:
                    printf("%d |", tableau[getIndex(P)]);
                    break;

                case -100:
                    printf("T2  |");
                    break;
                case -200:
                    printf("TT2 |");
                    break;

                case -300:
                    printf("TTT2|");
                    break;

                case 100:
                    printf("T1  |");
                    break;

                case 200:
                    printf("TT1 |");
                    break;

                case 300:
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

int playerStillHaveTowers(int* tableau) {
    for(int i = 0; i < WIDTH; i++)
        for(int ib = 0; ib < LENGTH; ib++) {
            if(tableau[(i * WIDTH) + ib] >= 0 && tableau[(i * WIDTH) + ib] <= 300) {
                return 1;
            }
        }

    return 0;
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
            if((valeur >= 0) && (valeur < 100)) {
                tableau[(y * WIDTH) + x] += 100 - valeur;
                ok = 0;
            }
            if(valeur >= 100) {
                tableau[(y * WIDTH) + x] += 100;
                ok = 0;
            }
            if(valeur == -1){
                tableau[(y * WIDTH) + x] += 101;
                ok = 0;
            }

            if(ok == 1) {
                printf("\nVeuillez rejouer sur une autre case\n");
            }
        }
        
        ia(tableau);

        if(!playerStillHaveTowers(tableau)) {
            printf("\n Perdu !");
            exit(0);
        }
    }
}

void ia(int* tableau) {
    //Positionner la tour dans une case proche aux maximums des cases positives
    Point poisitionParfaite, testPosition, P;
    int meilleurPositionNmbCotes = 0, test = 0;
    int* tableauPos = NULL;
    //int* tableauNew = show(tableau);

    for(int i = 0; i < WIDTH; i++) {
        for(int ib = 0; ib < LENGTH; ib++) {
            test = 0;
            testPosition.x = ib;
            testPosition.y = i;
            P.x = ib; P.y = i;
            tableauPos = nextTowers(testPosition, tableau);

            if(tableauPos[N] == 0)
                if((tableau[getIndexDirection(P, N)] >= 100 && tableau[getIndexDirection(P, N)] <= 300) || tableau[getIndexDirection(P, N)] == 99)
                    test++;

            if(tableauPos[S] == 0)
                if((tableau[getIndexDirection(P, S)] >= 100 && tableau[getIndexDirection(P, S)] <= 300) || tableau[getIndexDirection(P, S)] == 99)
                    test++;

            if(tableauPos[E] == 0)
                if((tableau[getIndexDirection(P, E)] >= 100 && tableau[getIndexDirection(P, E)] <= 300) || tableau[getIndexDirection(P, E)] == 99)
                    test++;

            if(tableauPos[O] == 0)
                if((tableau[getIndexDirection(P, O)] >= 100 && tableau[getIndexDirection(P, O)] <= 300) || tableau[getIndexDirection(P, O)] == 99)
                    test++;

            if(caseIsAvailable(testPosition, tableau) && test > meilleurPositionNmbCotes) {
                poisitionParfaite = testPosition;
                meilleurPositionNmbCotes = test;
            }
        }
    }

    //printf("X: %d, Y: %d", poisitionParfaite.x, poisitionParfaite.y);
    tableau[(poisitionParfaite.y * WIDTH) + poisitionParfaite.x] -= 100;
}