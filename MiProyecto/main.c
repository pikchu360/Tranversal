#include <stdio.h>
#include "TDA_DATA_TYPE.h"

int main(){
	
	//Test intType
	struct intType numero;
	
	numero = insertInt();
	intShow(numero);
	
	//Test charType
	struct charType caracter;
	
	caracter = insertChar();
	charShow(caracter);
	
	//Test stringType.
	struct stringType cadena;
	
	cadena = insertString();
	stringShow(cadena);
	
	return 0;
}
