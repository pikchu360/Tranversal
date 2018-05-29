#include <stdio.h>
#include "AutomataFinito.h"

int main(){
	el primero es el inicial
	States=[q0;q1;q2;q3;q4;.]
		
	Alpha[a;b;c;d;e;.]
	
	FinalStates =[q2;q3;q4;.]
	
	DeltaTransition = States=[q0,a->q2;q0,a->q0;q1,a->q2;q0,a->q2;.]	
	//AutomataFinito A;
	//Inicializo el arbol. coso.
	ptrRoot raiz = NULL;

	loadAll(&raiz);
	showAll(raiz);
	
	return 0;
}
