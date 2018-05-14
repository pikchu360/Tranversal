#ifndef TDA_AF_H
#define TDA_AF_H
#include "TDA_DATA_TYPE_H"

//Metodos para cargar el automata.
void loadStates();
void loadAlphabet();
void loadInitialState();
void loadStateOfAcceptance();
void loadTransitions();

//Metodos para imprimir el automata.
void showStates();
void showAlphabet();
void showInitialState();
void showStateOfAcceptance();
void showTransitions();


#endif
