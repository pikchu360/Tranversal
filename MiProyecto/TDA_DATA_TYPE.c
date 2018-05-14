#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TDA_DATA_TYPE.h"

//Inicializa el arbol.
void initTree(){
	stRoot = NULL;
	stLeft = NULL;
	stRight = NULL;
}

//Para saber si existe o no el arbol.
bool isEmpty(){
	if(stRoot==NULL){
		return true;
	}else{
		return false;
	}
}

//Carga el arbol.
void load(){
	initTree();
}

//Muestra el arbol.
void show(){
	
}
