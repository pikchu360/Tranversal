#ifndef TDA_INT_TYPE_H
#define TDA_INT_TYPE_H

//defino el codigos del tipos de datos asociado.
#define INT 1024

//Estructura de un entero
struct intType{
	int iNodeType;					//codigo del tipo de dato.
	int iValue;						//identificador del nodo.
};

//Inserta un dato de tipo intType.
struct intType insertInt();

//Muestra un dato de tipo intType.
void intShow();

#endif
