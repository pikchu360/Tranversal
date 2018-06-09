#include <stdio.h>
#include "AutomataFinito.h"
#include "Menu.h"
#include <stdlib.h>
#include <string.h>

int main(){
	char cadena[100], cOp[2]; 
		int op;
	three raiz = NULL;
	
	printf("\t___________TEORIA DE LA COMPUTACION I___________\n\n\n");
	printf("\n\n\nIngrese un AF: ");
	
	loadAll(&raiz);
	showAll(raiz);
	
	menu();
	do{		
		switch (op){
		case 1:
			evalueChais(raiz);
			break;
			
		case 2: 
			showAll(raiz);
			break;
		case 3:
			afnd2afd(&raiz);
			break;
		case 4:
			op=4;
		default:
			break;
		}
		printf("\n\n\nOpciones: ");
		leeCad(cOp, 2);
		op = (int)cOp[0]-48;
		if( op!=1 && op!=2 && op!=3 && op!=4){
			printf("Error. Ingrese un numero dentro del rango:");
		}
	}while( op!=4 );
	
	printf("\n\n\t___________TEORIA DE LA COMPUTACION I___________");
	return 0;
}


