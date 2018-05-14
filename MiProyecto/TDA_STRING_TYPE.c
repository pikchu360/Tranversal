#include <stdio.h>
#include <stdbool.h>
#include "TDA_STRING_TYPE.h"

//Ingresa un cadena.
struct stringType insertString(){
	struct stringType chais;
	
	//limpio el buffer.
	while(getchar()!='\n');
	
	printf("\n\nIngresa una cadena: ");
	
	//Asignacion de valores para la estructura.
	gets(chais.stValue);
	chais.iNodeType = STRING;
	
	return chais;
}//Funciona.


//Imprime la estructura stringType.
void stringShow(struct stringType stString){
	printf("\nCadena: %s", stString.stValue);
	printf("\nTipo STRING: %d", stString.iNodeType);
}//Funciona.
