#ifndef TDA_DATA_TYPE_H
#define TDA_DATA_TYPE_H

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

#endif
