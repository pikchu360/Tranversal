#ifndef TDA_STRING_TYPE_H
#define TDA_STRING_TYPE_H

//defino el codigos del tipos de datos asociado.
#define STRING 1032

//Estructura para una cadena
struct stringType{
	int iNodeType;
	char stValue[10];
};

//inserta un dato de tipo stringType.
struct stringType insertString();

//Muestra un dato de tipo stringType.
void stringShow();

#endif
