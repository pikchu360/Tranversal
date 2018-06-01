#include <stdio.h>
#include "AutomataFinito.h"
#include "Menu.h"
#include <stdlib.h>
#include <string.h>

int main(){
	three raiz = NULL;
	printf("\t___________TEORIA DE LA COMPUTACION I___________\n\n\n");
	printf("\n\n\nIngrese un AF: ");
	
	loadAll(&raiz);
	showAll(raiz);
	/*
	system("clear");
	char cadena[100];
	int op;
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
			op=3;
		default:
			break;
		}
		printf("\n\n\nOpciones: ");
		fflush(stdin);
		scanf("%d", &op);
		if( op!=1 && op!=2 && op!=3){
			printf("Error. Ingrese un numero dentro del rango:");
		}
	}while( op!=3 );
	*/
	printf("\n\n\t___________TEORIA DE LA COMPUTACION I___________");
	return 0;
}
