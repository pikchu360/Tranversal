#ifndef AUTOMATAFINITO_H
#define AUTOMATAFINITO_H

//defino el codigos del tipos de datos asociado.
#define INT 1024
#define CHAR 1025
#define STRING 1032
#define LIST 1033
#define SET 1034

//Armado de punteros para mejorar manejo de arbol.
typedef struct dataType setPtr;
typedef setPtr* three;

//Arbol.
struct dataType{
	int iNodeType;				//codigo del dato
	struct dataType *dtDatum;	//hijo izquierdo contenedor de un padre jr.
	struct dataType *dtNext;	//hijo derecho contenedor de una etiqueta
};

//Asignacion del puntero para los hijos de dataType.
typedef struct setType dataPtr;
typedef dataPtr* child;

//Hijo u hoja.
struct setType{
	int iNodeType;				//codigo del dato
	struct dataType *dtDatum;	//hijo izquierdo contenedor de un dato.
	struct dataType *dtNext;	//hijo derecho contenedor de un nuevo padre o null.
};

//==============================================================================
//Declaro los tipos de datos.

//Estructura de tipo char.
struct charType{
	int iNodeType;		//codigo del tipo de dato.
	char cValue;		//identificador del nodo.
};

//Estructura para una cadena
struct stringType{
	int iNodeType;
	char stChais[20];
};

//Metodos para los registros de tipo de datos.
//Inserta un dato de tipo intType.
struct charType insertChar();
struct stringType insertString();

//Muestra un dato de tipo intType.
void charShow();
void stringShow();

//Metodos para cargar el automata.
void loadStates(child *root); 						//Paso por referencia al padre jr.
void loadAlphabet(child *root);						//idem
void loadInitialState(child *root, child set);		//idem
void loadStateOfAcceptance(child *root, child set);	//idem
void loadTransitions(child *root, child set);		//idem

//Metodos para imprimir el automata.
void showStates(child root);				//Paso por valor al padre jr.
void showAlphabet(child root);				//Idem.
void showInitialState(child root);			//Idem.
void showStateOfAcceptance(child root);		//Idem.
void showTransitions(child root);			//Idem.

//Methos finish
void loadAll(three *root);			//Paso por referencia la raiz del arbol.
void showAll(three root);			//Paso por valor la raiz del arbol.

#endif
