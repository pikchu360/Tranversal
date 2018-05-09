#include <stdio.h>
#include "TDA_DATA_TYPE.h"

public void load(dataType *dt){
	char chain[10];			//cadena a ingresar y ser tratada.
	
	intType iElement;		//Registro de enteros.
	charType chElement;		//Registro de Array de caracteres.
	setType stElement;		//Registro de conjuntos.
	
	printf("\nInsert: ");
	gets(chain);			//Ingreso de cadena.
	
	dt->iNodeType = validate(&chain);
	
	//Segun el arbol del apunte de Tranversal
	if(dt->iNodeType == INT){
		dt->dtDatum = iElement;
		iElement.iNodeType = INT;
		iElement.iValue = chain;
	}else{
		dt->dtDatum = chElement;
		chElement.iNodeType = STRING;
		chElement.chValue = chain;
	}
	
}

//Valida el tipo de cadena que entro y retorna un codigo.
private int validate(char c[]){
	int i=0, code;
	while( c[i] != '\0' ){
		if(c[i]=='0' || c[i]=='1' || c[i]=='2' || c[i]=='3' || c[i]=='4' || c[i]=='5'
		|| c[i]=='6' || c[i]=='7' || c[i]=='8' || c[i]=='9'){
			code = INT;
		}else{
			code = STRING;
			break;
		}
		i++;
	}
	return code;
}
