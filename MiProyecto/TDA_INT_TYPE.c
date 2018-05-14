#include <stdio.h>
#include <stdbool.h>
#include "TDA_INT_TYPE.h"

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
	
	return itNumber;
}//Funciona.

//Imprime la estructura intType.
void intShow(struct intType itNumber){
	printf("\nNumero: %d", itNumber.iValue);
	printf("\nTipo INT: %d", itNumber.iNodeType);
}//Funciona.

