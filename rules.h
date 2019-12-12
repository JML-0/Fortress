#include "fortress.h"
#ifndef _RULES_H
#define _RULES_H

#define LENGTH 8
#define WIDTH 8

typedef enum Direction
{
  N, E, S, O
} Direction;

typedef struct Point
{
  int x, y;  
} Point;

extern int caseIsAvailable(Point P, int * T);
extern int * nextTowers(Point P, int * T);
extern int * getAddressTowerDirection(Point P, int * T, Direction D);
extern int * show(int * T);
extern void deleteTowers(int * T);

#endif