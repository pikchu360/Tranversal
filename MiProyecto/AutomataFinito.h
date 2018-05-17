#ifndef AUTOMATAFINITO_H
#define AUTOMATAFINITO_H

//defino el codigos del tipos de datos asociado.
#define INT 1024
#define CHAR 1025
#define STRING 1032

//Estructura de conjunto para armar los padres de cada conjunto de la 5-upla.
//Representa el arbol.
struct setType{
	int iNodeType;
	struct dataType * dtDatum;		//Hijo izquierdo.
	struct dataType * dtNext;		//Hijo derecho.
};

//Declaracion de los punteros correspondientes.
struct setType* stRoot;

//Defino la estructura
struct dataType{
	int iNodeType;					//codigo del tipo de dato asociado.
	struct dataType * dtDatum_L;	//registro de algun tipo de dato.	
	struct dataType * dtNext_R;	//siguiente registro.
};

//Declaro los tipos de datos.
//Estructura de un entero
struct intType{
	int iNodeType;					//codigo del tipo de dato.
	int iValue;						//identificador del nodo.
};

//Estructura de tipo char.
struct charType{
	int iNodeType;					//codigo del tipo de dato.
	char cValue;					//identificador del nodo.
};

//Estructura para una cadena
struct stringType{
	int iNodeType;
	char stValue[10];
};

//Metodos para los registros de tipo de datos.
//Inserta un dato de tipo intType.
struct intType insertInt();
struct charType insertChar();
struct stringType insertString();

//Muestra un dato de tipo intType.
void intShow();
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
