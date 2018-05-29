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
	
	//limpio el buffer...
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

//Metodo para cargar un nodo.
void insert( ptrRoot *root, stringPtr input ){
	ptrRoot temp = (*root), newFather;
	if( (*root)==NULL ){
		*root=malloc(sizeof(dataPtr));
		//Si hay memoria lo asigna.
		if (*root != NULL) { 
			(*root)->iNodeType = SET;
			(*root)->dtDatum = input;
			(*root)->dtNext = NULL;
			
		} else {
			printf("\nNo se inserto %s. No hay memoria disponible.n", input->stChais);
		} 
	}else{
		while( (*root)->dtNext!=NULL ){
			if( (*root)->dtDatum != NULL){
				(*root) = (*root)->dtNext;
			}
		}
	
		newFather = malloc(sizeof(dataPtr));
		newFather->dtDatum = input;
		newFather->dtNext = NULL;

		(*root)->dtNext = newFather;
		(*root) = temp;
	}
}//Funciona.

//METODOS INDIVIDUALES DEL AUTOMATA.
void loadStates(ptrRoot *root){
	printf("\nEstado/os del automata: \n\nQ = { ");
	do{
		printf("\ninput: ");
		stringPtr in = (stringPtr) malloc(sizeof(stringPtr));
		
		fflush(stdin);
		gets(in->stChais); 
		in->iNodeType = STRING;
		
		insert(& (*root), in);		
	} while (option());
}

//METODOS PARA EL ARBOL.
void initializeTree(ptrRoot *root){
	root = NULL;
}

//Carga el arbol.
void loadAll(ptrRoot *root){
	loadStates( &(*root) );
}

//Metodos para imprimir arbol.
void inOrder(ptrRoot node){
	if( node!=NULL ){
		//inOrder(node->dtDatum);
		printThree(node);
		inOrder(node->dtNext);
	}
}

void printThree(ptrRoot node){
	
	printf(" %s ",node->dtDatum->stChais);

}

void showStates(ptrRoot root){
	inOrder(root);
}

//Muestra el arbol.
void showAll(ptrRoot root){
	showStates(root);
}
