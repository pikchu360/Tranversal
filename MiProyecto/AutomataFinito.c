#include "AutomataFinito.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//METODOS PARA LECTURA.

//Ingresa un solo caracter.
struct charType insertChar(){
	struct charType ctChar;
	
	//limpio el buffer.
	while(getchar()!='\n');
	
	printf("\n\nIngrese un caracter: ");
	
	//Asignacion del aracter a la estructura charType.
	ctChar.iNodeType = CHAR;
	ctChar.cValue = getchar();
	
	return ctChar;
}//Funciona.

//Ingresa un cadena.
struct stringType insertString(){
	struct stringType chais;
	
	//limpio el buffer.
	//while(getchar()!='\n');
	fflush(stdin);
	//printf("\n\nIngresa una cadena: ");
	
	//Asignacion de valores para la estructura.
	gets(chais.stChais);
	chais.iNodeType = STRING;
	
	return chais;
}//Funciona.

//METODOS DE IMPRESION.
//Imprime la estructura charType.
void charShow(struct charType ctChar){
	printf("\nCaracter: %c",ctChar.cValue);
	printf("\nTipo CHAR: %d", ctChar.iNodeType);
	
}//Funciona.

//Imprime la estructura stringType.
void stringShow(struct stringType stString){
	printf("\nCadena: %s", stString.stChais);
	printf("\nTipo STRING: %d", stString.iNodeType);
}//Funciona.

//Opcion para continuar o no el ingreso.
bool option(){
	char opt[2];
	printf("\nContinuar carga? S/n: ");
	do{
		fflush(stdin);
		gets(opt);
		if ( opt[0]=='s' || opt[0]=='S') {
			return true;
		}
		else if (opt[0] == 'n' || opt[0]=='N')
		{
			return false;
		}else {
			printf("\nError. Ingrese s/n: ");
		}
	}while(opt[0]!='s' && opt[0]!='S' && opt[0]!='n' || opt[0]!='N' );
}//Funciona.

//METODOS INDIVIDUALES DEL AUTOMATA.
void loadStates(dataPtr rootTemp){
	printf("\nEstado/os del automata: \n\nQ = { ");
	do{
		printf("\ninput: ");
		stringPtr in = (stringPtr) malloc(sizeof(stringPtr));
		
		fflush(stdin);
		gets(in->stChais); 
		printf("load: %s", in->stChais);
		
		
		
	} while (option());	
}

//METODOS PARA EL ARBOL.
void initializeTree(){
	
}

bool isEmpty(){
	/*if ( stRoot == NULL){
		return true;
	}else{
		return false;
	}*/
}

//Carga el arbol.
void loadAll(){
	dataPtr root = (dataPtr) malloc(sizeof(dataPtr));
	loadStates(root);
}
//Muestra el arbol.
void showAll(){
	
}

/*



*/
