#include <stdio.h>
#include "AutomataFinito.h"
#include "Menu.h"
#include <stdlib.h>
#include <string.h>

int main(){
	char cadena[100], cOp[2]; 
	int op;
	bool flag = false;
	three raiz = NULL, raizAFD = NULL;
	
	printf("\t___________TEORIA DE LA COMPUTACION I___________\n\n\n");
	printf("\n\n\nIngrese un AF: ");
	
	loadAll(&raiz);
	showAll(raiz);
	
	menu();
	do{
		switch (op){
			case 1:
				evalueChais(raiz,true);
				menu();
				break;
			case 2: 
				showAll(raiz);
				menu();
				break;
			case 3:
				flag = true;
				afnd2afd(&raizAFD, raiz);
				menu();
				break;
			case 4:
				if(flag){
					showAll(raizAFD);
				}else{
					printf("\nError. Primero convierta su automata.");
				}
				menu();
				break;
			case 5:
				if (flag) {
					evalueChais(raizAFD,false);
				}else{
					printf("\nError. Primero convierta su automata.");
				}
				menu();
				break;
			case 6:
				op=6;
			default:
				break;
		}
		printf("\n\n\nOpciones: ");
		leeCad(cOp, 2);
		op = (int)cOp[0]-48;
		if( op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6){
			printf("Error. Ingrese un numero dentro del rango:");
		}
	}while( op!=6 );
	
	printf("\n\n\t___________TEORIA DE LA COMPUTACION I___________");
	return 0;
}


