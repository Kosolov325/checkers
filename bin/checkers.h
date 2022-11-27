#ifndef __CHECKERS_H
#define __CHECKERS_H

// ************Header files Included************
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "constants.h"
#include <string.h>

// ************Functions declarations************

char *remove_spaces(char *str);
int if_capture_possible(checkersGrid CheckerBoard[][SIZE], char turn);
int winner(checkersGrid Board[][SIZE], char turn);
bool ifdouble(checkersGrid Board[][SIZE], coordinates a, char turn);
void initBoard(checkersGrid Board[][SIZE]);
void printBoard(checkersGrid Board[][SIZE]);
int isvalid(checkersGrid Board[][SIZE], char P, char M, int b, char N, int d);
int movements(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2); //c1-Initial & c2-final coordinates
int captures(checkersGrid Board[][SIZE], char turn, coordinates c1, coordinates c2);
int is_capture(checkersGrid Board[][SIZE], char turn, coordinates c);
int if_capture(checkersGrid Board[][SIZE], char turn);
coordinates *double_captures(checkersGrid Board[][SIZE], char turn, coordinates c);
int introduction();
char switchTurn(char turn);
void sound(); // Adds sound when a valid move(either diagonal or capture) is made

#endif