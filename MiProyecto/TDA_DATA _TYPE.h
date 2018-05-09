#ifndef TDA_DATA _TYPE_H
#define TDA_DATA _TYPE_H

//defino los codigos de los tipos de datos.
#define INT 1024
#define CHAR 1025
#define STRING 1032
#define LIST 1033
#define SET 1034

//Defino la estructura
public struct dataType{
	int iNodeType;				//codigo del tipo de dato asociado
	struct dataType * dtDatum;	//registro de algun tipo de dato	
	struct dataType * dtNext;	//siguiente registro
};

//estructura de un entero
public struct intType{
	int iNodeType;
	int iValue;
};

//estructura para array de caracteres.
public struct charType{
	int iNodeType;
	char chValue[10];
};
	

//estructura de conjunto
public struct setType{
	int iNodeType;
	struct dataType * dtDatum;
	struct dataType * dtNext;
};

//Metodos publicos
public void load();

#endif
