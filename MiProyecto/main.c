#include <stdio.h>
#include "AutomataFinito.h"

int main(){
	//AutomataFinito A;
	//Inicializo el arbol.
	ptrRoot raiz = NULL;
	
	loadAll(&raiz);
	showAll(raiz);
	
	return 0;
}
