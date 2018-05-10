#include <stdio.h>
#include <stdbool.h>
#include "TDA_DATA_TYPE.h"

//Ingresa unicamente enteros.
struct intType insertInt(){
	bool flag=true;
	int iNumber;
	struct intType itNumber;
	
	while(flag){
		printf("\n\nIngrese un entero: ");
		if( scanf("%d",&iNumber) != 1 ){
			printf("\n\n\tError de carga.. Ingrese un numero entero.");
			//Limpio el buffer de entrada.
			while(getchar()!='\n');
		}else{
			flag = false;
		}
	}
	
	//Asignacion de informacion para la estructura intType.
	itNumber.iNodeType = INT;
	itNumber.iValue = iNumber;
	itNumber.itNext = NULL;
	
	return itNumber;
}//Funciona.

//Ingresa un solo caracter.
struct charType insertChar(){
	struct charType ctChar;
	
	//limpio el buffer.
	while(getchar()!='\n');
	
	printf("\n\nIngrese un caracter: ");
	
	//Asignacion del aracter a la estructura charType.
	ctChar.iNodeType = CHAR;
	ctChar.chValue = getchar();
	ctChar.ctNext = NULL;
	
	return ctChar;
}//Funciona.

//Ingresa un cadena.
struct stringType insertString(){
	struct stringType chais;

	//limpio el buffer.
	while(getchar()!='\n');
	
	printf("\n\nIngresa una cadena: ");
	
	//Asignacion de valores para la estructura.
	gets(chais.stValue);
	chais.iNodeType = STRING;
	chais.stNext = NULL;
	
	return chais;
}//Funciona.

//Imprime la estructura intType.
void intShow(struct intType itNumber){
	printf("\nNumero: %d", itNumber.iValue);
	printf("\nTipo INT: %d", itNumber.iNodeType);
}//Funciona.

//Imprime la estructura charType.
void charShow(struct charType ctChar){
	printf("\nCaracter: %c",ctChar.chValue);
	printf("\nTipo CHAR: %d", ctChar.iNodeType);
	
}//Funciona.

//Imprime la estructura stringType.
void stringShow(struct stringType stString){
	printf("\nCadena: %s", stString.stValue);
	printf("\nTipo STRING: %d", stString.iNodeType);
}//Funciona.
