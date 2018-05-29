#ifndef AutomataFinito_H
#define AutomataFinito_H

//defino el codigos del tipos de datos asociado.
#define INT 1024
#define CHAR 1025
#define STRING 1032
#define LIST 1033
#define SET 1034

//Declaracion de los punteros correspondientes.
typedef struct dataType* dataPtr;
typedef struct stringType* stringPtr;
typedef struct charType* charPtr;

//Estructura de conjunto para armar los padres de cada conjunto de la 5-upla.
//Representa el arbol.
struct dataType{
	int iNodeType;		//Codigo del tipo de dato.
	dataPtr dtDatum;	//Hijo izquierdo.
	dataPtr dtNext;		//Hijo derecho.
};


//Declaro los tipos de datos.

//Estructura de tipo char.
struct charType{
	int iNodeType;		//codigo del tipo de dato.
	char cValue;		//identificador del nodo.
};

//Estructura para una cadena
struct stringType{
	int iNodeType;
	char stChais[10];
};

//Metodos para los registros de tipo de datos.
//Inserta un dato de tipo intType.
struct charType insertChar();
struct stringType insertString();

//Muestra un dato de tipo intType.
void charShow();
void stringShow();

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

//Methos finish
void loadAll();
void showAll();

#endif
