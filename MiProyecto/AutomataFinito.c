#include "AutomataFinito.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//METODOS PARA LECTURA.
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
//Imprime la estructura intType.
void intShow(struct intType itNumber){
	printf("\nNumero: %d", itNumber.iValue);
	printf("\nTipo INT: %d", itNumber.iNodeType);
}//Funciona.

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
void loadStates(){
	struct dataType* temp = (struct setType*) malloc( sizeof(struct setType));
	struct dataType* father = (struct setType*) malloc(sizeof(struct setType));
		
	temp = father = NULL;

	printf("\nEstado/os del automata: ");
	do{
		
		fflush(stdin);
		printf("\nIngrese estado: ");
		struct stringType in = insertString();
		
		//printf("---------->pasa");
		father->dtDatum_L = in;
		father->dtNext_R = NULL;

		stringShow(in);
	} while (option());	
}

//METODOS PARA EL ARBOL.
void initializeTree(){
	stRoot = NULL;
}

bool isEmpty(){
	if ( stRoot == NULL){
		return true;
	}else{
		return false;
	}
}

//Carga el arbol.
void loadAll(){
	struct setType* rootBU = (struct setType*) malloc( sizeof(struct setType));
	rootBU = stRoot;
	loadStates();

	stRoot = rootBU;
}
//Muestra el arbol.
void showAll(){
	
}

/*



*/