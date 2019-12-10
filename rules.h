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
extern int * NextTowers(Point P, int * T);

#endif