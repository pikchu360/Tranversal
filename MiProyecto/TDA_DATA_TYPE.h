#ifndef TDA_DATA_TYPE_H
#define TDA_DATA_TYPE_H

//defino los codigos de los tipos de datos.
#define INT 1024
#define CHAR 1025
#define STRING 1032
#define LIST 1033
#define SET 1034

//Defino la estructura
struct dataType{
	int iNodeType;					//codigo del tipo de dato asociado.
	struct dataType * dtDatum_L;	//registro de algun tipo de dato.	
	struct dataType * dtNext_R;	//siguiente registro.
};

//Estructura de conjunto para armar los padres de cada conjunto de la 5-upla.
struct setType{
	int iNodeType;
	struct dataType * dtDatum;
	struct dataType * dtNext;
};

//Estructura de un entero
struct intType{
	int iNodeType;					//codigo del tipo de dato.
	int iValue;						//identificador del nodo.
	struct intType * itNext;		//Siguiente puntero. siempre será null
};

//Estructura para caracteres.
struct charType{
	int iNodeType;					//codigo del tipo de dato.
	char chValue;					//identificador del nodo.
	struct charType * ctNext;
};

//Estructura para una cadena
struct stringType{
	int iNodeType;
	char stValue[10];
	struct stringType * stNext;
};

//Metodos de lectura para cada estructura.
struct intType insertInt();
struct charType insertChar();
struct stringType insertString();

//Metodos de impresion para cada estructura.
void intShow();
void charShow();
void stringShow();

#endif
