#ifndef OPERACIONES_H
#define OPERACIONES_H
#include "AutomataFinito.h"

struct charType insertChar();
struct stringType insertString();
void charShow(struct charType ctChar);
void stringShow(struct stringType stString);
void copyChais(char *str, char src[], int init, int end);
void getStates(char *ReturnStates, child root);
void getAlpha(char *ReturnTransitions, child root);
void insert( child *root, struct stringType* input );
void evalueChais(three root, bool flag);

#endif
