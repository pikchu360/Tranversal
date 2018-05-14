#ifndef TDA_CHAR_TYPE._H
#define TDA_CHAR_TYPE._H

//defino el codigos del tipos de datos asociado.
#define CHAR 1025

//Estructura de tipo char.
struct charType{
	int iNodeType;					//codigo del tipo de dato.
	char cValue;					//identificador del nodo.
};

//Inserta un dato de tipo charType.
struct charType insertChar();

//Muestra un dato de tipo charType
void charShow();

#endif
