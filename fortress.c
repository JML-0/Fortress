/*
    - 6 lettres de longueur et 1 lettre de hauteur (3 si on compte le plafond + le bas)
    - Un tableau de 8 * 8 entrées en integer
    - 0 = tour morte ou case vide | 1, 2, 3 = tour joueur 1 | -1, -2, -3 = tour IA
*/

#include "rules.h"
#include "controls.h"
#include <stdlib.h>
#include <stdio.h>

int * creerTableau();
void afficherTableau(int* tableau);
void jouer(int* tableau);
void ia(int* tableau);
int someoneWin(int* tableau);

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
        }

        printf("\n     ");

        for(int ia = 0; ia < LENGTH * 5; ia++)
            printf("-");

        printf("\n");
    }
}

int someoneWin(int* tableau) {
    int scorePlayer = 0, scoreIA = 0;
    Point P;

    for(int i = 0; i < WIDTH; i++) {
        for(int ib = 0; ib < LENGTH; ib++) {
            P.x = ib; P.y = i;
            
            switch(tableau[getIndex(P)]) {
                case 100 ... 300:
                    scorePlayer += tableau[getIndex(P)];
                    break;

                case -300 ... -100:
                    scoreIA += (0 - tableau[getIndex(P)]) ;
                    break;

                default:
                    return 0;
                    break;
            }
        }
    }

    if(scorePlayer > scoreIA)
        return 1;

    if(scoreIA > scorePlayer)
        return 2;

    return 0;
}

void jouer(int* tableau) {
    Point P;
    int joue = 1;
    int _caseValue = 0;

    while(joue) {
        int ok = 1;
        afficherTableau(show(tableau));

        while(ok) {

            do {
                printf("\nCoordonnée X: ");
                scanf("%d", &P.x);
            } while(P.x >= LENGTH);
            
            do {
                printf("\nCoordonnée Y: ");
                scanf("%d", &P.y);
            } while(P.y >= WIDTH);
            
            _caseValue = caseValue(P, tableau);
            if(_caseValue) {
                tableau[getIndex(P)] = _caseValue;
                ok = 0;
            }

            if(ok == 1) {
                printf("\nVeuillez rejouer sur une autre case\n");
            }
        }
        
        show(tableau);
        ia(tableau);

        switch(someoneWin(show(tableau))) {
            case 1:
                printf("\nVous avez gagner, bravo !\n");
                afficherTableau(show(tableau));
                exit(0);
                break;

            case 2:
                printf("\nVous avez perdu :(\n");
                afficherTableau(show(tableau));
                exit(0);
                break;
        }

    }
}

void ia(int* tableau) {
    //Positionner la tour dans une case proche aux maximums des cases positives
    Point poisitionParfaite, testPosition, P;
    int meilleurPositionNmbCotes = 0, test = 0;
    int* tableauPos = NULL;
    //int* tableauNew = show(tableau);

    //Pour les angles
    Point angle;
    int playerAngle = 0, caseNotFound = 1;

    angle.x = 0; angle.y = 0;
    if(tableau[getIndex(angle)] >= 100 && tableau[getIndex(angle)] <= 300 ) {
        angle.x = 1; angle.y = 1;

        if(caseIsAvailable(angle, tableau)) {
            poisitionParfaite = angle;
            playerAngle = 1;
            caseNotFound = 0;
        }
    }

    angle.x = 7; angle.y = 0;
    if(tableau[getIndex(angle)] >= 100 && tableau[getIndex(angle)] <= 300 ) {
        angle.x = 6; angle.y = 1;

        if(caseIsAvailable(angle, tableau)) {
            poisitionParfaite = angle;
            playerAngle = 1;
            caseNotFound = 0;
        }
    }

    angle.x = 0; angle.y = 7;
    if(tableau[getIndex(angle)] >= 100 && tableau[getIndex(angle)] <= 300 ) {
        angle.x = 1; angle.y = 6;

        if(caseIsAvailable(angle, tableau)) {
            poisitionParfaite = angle;
            playerAngle = 1;
            caseNotFound = 0;
        }
    }

    angle.x = 7; angle.y = 7;
    if(tableau[getIndex(angle)] >= 100 && tableau[getIndex(angle)] <= 300 ) {
        angle.x = 6; angle.y = 6;

        if(caseIsAvailable(angle, tableau)) {
            poisitionParfaite = angle;
            playerAngle = 1;
            caseNotFound = 0;
        }
    }

    if(!playerAngle) {
        for(int i = 0; i < WIDTH; i++) {
            for(int ib = 0; ib < LENGTH; ib++) {
                test = 0;
                testPosition.x = ib;
                testPosition.y = i;
                P.x = ib; P.y = i;
                tableauPos = nextTowers(testPosition, tableau);

                if(tableauPos[N] == 0)
                    if((tableau[getIndexDirection(P, N)] >= 100 && tableau[getIndexDirection(P, N)] <= 300) || tableau[getIndexDirection(P, N)] == 99)
                        test += tableau[getIndexDirection(P, N)];

                if(tableauPos[S] == 0)
                    if((tableau[getIndexDirection(P, S)] >= 100 && tableau[getIndexDirection(P, S)] <= 300) || tableau[getIndexDirection(P, S)] == 99)
                        test += tableau[getIndexDirection(P, S)];

                if(tableauPos[E] == 0)
                    if((tableau[getIndexDirection(P, E)] >= 100 && tableau[getIndexDirection(P, E)] <= 300) || tableau[getIndexDirection(P, E)] == 99)
                        test += tableau[getIndexDirection(P, E)];

                if(tableauPos[O] == 0)
                    if((tableau[getIndexDirection(P, O)] >= 100 && tableau[getIndexDirection(P, O)] <= 300) || tableau[getIndexDirection(P, O)] == 99)
                        test += tableau[getIndexDirection(P, O)];

                if( ( caseIsAvailable(testPosition, tableau) || (( tableau[getIndex(testPosition)] > -300 && tableau[getIndex(testPosition)] <= 100 ) || tableau[getIndex(testPosition)] == 99) ) && test > meilleurPositionNmbCotes) {
                    printf("\nTOTAL: %d\n", 0 - (tableau[getIndex(testPosition)] - 100));
                    if(0 - (tableau[getIndex(testPosition)] - 100) >= test) {
                        poisitionParfaite = testPosition;
                        meilleurPositionNmbCotes = test;
                        caseNotFound = 0;
                    }
                }
            }
        }
    }

    if(caseNotFound) {
        for(int i = 0; i < WIDTH; i++) {
            for(int ib = 0; ib < LENGTH; ib++) {
                test = 0;
                testPosition.x = ib;
                testPosition.y = i;
                P.x = ib; P.y = i;
                tableauPos = nextTowers(testPosition, tableau);

                if(tableauPos[N] == 0)
                    if((tableau[getIndexDirection(P, N)] >= 100 && tableau[getIndexDirection(P, N)] <= 300) || tableau[getIndexDirection(P, N)] == 99)
                        test += tableau[getIndexDirection(P, N)];

                if(tableauPos[S] == 0)
                    if((tableau[getIndexDirection(P, S)] >= 100 && tableau[getIndexDirection(P, S)] <= 300) || tableau[getIndexDirection(P, S)] == 99)
                        test += tableau[getIndexDirection(P, S)];

                if(tableauPos[E] == 0)
                    if((tableau[getIndexDirection(P, E)] >= 100 && tableau[getIndexDirection(P, E)] <= 300) || tableau[getIndexDirection(P, E)] == 99)
                        test += tableau[getIndexDirection(P, E)];

                if(tableauPos[O] == 0)
                    if((tableau[getIndexDirection(P, O)] >= 100 && tableau[getIndexDirection(P, O)] <= 300) || tableau[getIndexDirection(P, O)] == 99)
                        test += tableau[getIndexDirection(P, O)];

                if( ( caseIsAvailable(testPosition, tableau) || (( tableau[getIndex(testPosition)] > -300 && tableau[getIndex(testPosition)] <= 100 ) || tableau[getIndex(testPosition)] == 99) )) {
                    poisitionParfaite = testPosition;
                }
            }
        }
    }

    printf("IA X: %d, Y: %d\n", poisitionParfaite.x, poisitionParfaite.y);
    tableau[(poisitionParfaite.y * WIDTH) + poisitionParfaite.x] -= 100;
}