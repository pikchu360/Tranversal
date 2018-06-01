#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//==============================================================================
//METODOS LECTURA DE LAS ESTRUCTURAS STRING Y CHAR.

//METODOS DE LECTURA.
//Ingresa un solo caracter.
struct charType insertChar(){
	struct charType ctChar;					//Variable auxiliar.
	while(getchar()!='\n');					//limpio el buffer.
	
	printf("\n\nIngrese un caracter: ");
	ctChar.iNodeType = CHAR;				//Asignacion de codigo.
	ctChar.cValue = getchar();				//Guarda un dato tipeado por teclado.
	
	return ctChar;
}//Funciona.

//Ingresa un cadena.
struct stringType insertString(){
	struct stringType chais;		//Variable auxiliar.
	fflush(stdin);					//Limpia el buffer.
	gets(chais.stChais);			//Asignacion de valores para la estructura.
	chais.iNodeType = STRING;		//Asignacion de codigo.
	
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


//==============================================================================
//METODOS DE LECTURA PARA EL ARBOL.

//Copia src en str desde la posicion init hasta la posicion end.
void copyChais(char *str, char src[], int init, int end){ 
	
	char sAux[20];						//Variable auxiliar para copiar la subcadena src.
	memset(&sAux, '\0', strlen(sAux));	//Limpio sAux.
	int first=0;						//Indice para concatenar desde la posicion 0 en sAux.
	
	for(int i = init; i < end; i++){	//Recorro src segun init y end pasados por parametros.
		sAux[first]=src[i];				//Copia caracter.
		first++;						//Incremento indice para sAux.
	}
	
	sAux[first] = '\0';					//Agrego fin de cadena en sAux.
	strcat(str,sAux);					//Retorno sAux.
}//Funciona.s

//Metodo que retorna, por parametro, un string de todos los estados del AF.
void getStates(char *ReturnStates, child root){
	struct stringType *str = malloc(sizeof(struct stringType));
	while(root!=NULL){								//Recorro el arbol de los estados hacia derecha.
		str = root->dtDatum;						//Asigno el registro del hijo izquierdo de SET a una variable.
		root = root->dtNext;						//Avanza a derecha el puntero.
		strcat(ReturnStates, str->stChais);			//Concatenacion.
		strcat(ReturnStates, ";");					//Concatenacion para poner un alerta.
	}
	strcat(ReturnStates, ".");						//Concatenacion de fin del arbol de estados.
}//Funciona.

//Metodo que retorna en un string con las transisiones del AF.
void getAlpha(char *ReturnAlpha, child root){
	struct stringType *str = malloc(sizeof(struct stringType));
	while(root!=NULL){								//Recorro el arbol de los estados hacia derecha.
		str = root->dtDatum;						//Asigno el registro del hijo izquierdo de SET a una variable.
		root = root->dtNext;						//Avanza a derecha el puntero.
		strcat(ReturnAlpha, str->stChais);			//Concatenacion.
		strcat(ReturnAlpha, ";");					//Concatenacion para poner un alerta.
	}
	strcat(ReturnAlpha, ".");						//Concatenacion de fin del arbol de estados.
}//Funciona.

//Metodo que retorna en un string con las transisiones del AF.
void getFinish(char *ReturnFinish, child root){
	struct stringType *str = malloc(sizeof(struct stringType));
	while(root!=NULL){								//Recorro el arbol de los estados hacia derecha.
		str = root->dtDatum;						//Asigno el registro del hijo izquierdo de SET a una variable.
		root = root->dtNext;						//Avanza a derecha el puntero.
		strcat(ReturnFinish, str->stChais);			//Concatenacion.
		strcat(ReturnFinish, ";");					//Concatenacion para poner un alerta.
	}
	strcat(ReturnFinish, ".");						//Concatenacion de fin del arbol de estados.
}//Funciona.

//Metodo que retorna en un string con las transisiones del AF.
void getTransation(char *ReturnTransitions, child root){
	struct stringType *str = malloc(sizeof(struct stringType));
	while(root!=NULL){								//Recorro el arbol de los estados hacia derecha.
		str = root->dtDatum;						//Asigno el registro del hijo izquierdo de SET a una variable.
		root = root->dtNext;						//Avanza a derecha el puntero.
		strcat(ReturnTransitions, str->stChais);			//Concatenacion.
		strcat(ReturnTransitions, ";");					//Concatenacion para poner un alerta.
	}
	strcat(ReturnTransitions, ".");						//Concatenacion de fin del arbol de estados.
}//Funciona.

//Metodo para cargar un nodo.
void insert( child *root, struct stringType* input ){
	child temp = (*root), newFather;		//Guardo la raiz para no perder la referencia.
	//newFather es el nuevo nodo a insertar.	
	if( *root==NULL ){						//Control de arbol vacio.
		*root=malloc(sizeof(child));		//Reserva memoria para la raiz.
		if (*root != NULL) { 				//Si hay memoria lo asigna.
			(*root)->iNodeType = LIST;		//Asignacion de codigo al padre del dato a guardar.
			(*root)->dtDatum = input;		//Al dato lo apunta el hijo izquierdo de la raiz.
			(*root)->dtNext = NULL;			
		} else {
			printf("\nNo se inserto %s. No hay memoria disponible.n", input->stChais);
		} 
	}else{
		while( (*root)->dtNext!=NULL ){			//Ubico el puntero para conectar con el nuevo dato.
			if( (*root)->dtDatum != NULL){		//Avanza el puntero mientras el hijo izquierdo este ocupado. 
				(*root) = (*root)->dtNext;		//Avanza puntero por la derecha.
			}
		}
		
		newFather = malloc(sizeof(struct setType));		//Reservo memoria.
		newFather->iNodeType = SET;						//Asignacion de codigo.
		newFather->dtDatum = input;						//El hijo izquierdo apunta a un registro.
		newFather->dtNext = NULL;
		
		(*root)->dtNext = newFather;		//Conecto al arbol el nuevo nodo creado.
		(*root) = temp;						//La raiz regresa a su inicio.
	}
}//Funciona.

//Evalua si la cadena cumple con los simbolos del alfabeto.
//bool valueChais(char *str, char *alpha){
//}

void inputStr(char* Aux){
	fflush(stdin);
	do{
		memset(Aux, '\0', strlen(Aux));
		gets(Aux);
		if(strlen(Aux)==0){
			printf(" Error. Ingrese caracter: ");
		}
	} while(strlen(Aux)==0);
	strcat(Aux,";");
}

void evalueChais(three root){ 		//Raiz del arbol.
	
	char chais[50];
	printf("\nIngrese una cadena: ");
	inputStr(chais);
	
}
//s( s(q,a),v) = { }
//s(q0,w)=p | p ->F 
