#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//==============================================================================
//METODOS LECTURA DE LAS ESTRUCTURAS STRING Y CHAR.

//METODOS DE LECTURA.
int leeCad(char *cadena, int tam){
	int j, ret;
	char c;
	j=0;
	fflush(stdin);	
	c=getchar();
	ret=0;
	while (c!=EOF && c!='\n' && j<tam-1){
		cadena[j]=c;
		j++;
		c=getchar();
		ret=1;
	}
	cadena[j]='\0';
	while(c!=EOF && c!='\n')
		c=getchar();
	return ret;
}

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
void getTransition(char *ReturnTransitions, child root){
	struct stringType *str = malloc(sizeof(struct stringType));
	bool flag = false;
	while(root!=NULL){								//Recorro el arbol de los estados hacia derecha.
		str = root->dtDatum;						//Asigno el registro del hijo izquierdo de SET a una variable.
		
		if(str->iNodeType==LIST){ //Solo cuando es padre osea LIST
			flag = true;
			if (strlen(ReturnTransitions)!= NULL){
				strcat(ReturnTransitions, ";");
			}
			strcat(ReturnTransitions, str->stChais);
		}else{
			if (flag){
				strcat(ReturnTransitions, ":");
				strcat(ReturnTransitions, str->stChais);
				strcat(ReturnTransitions, ">");
				flag = false;
			}else{
				strcat(ReturnTransitions, str->stChais);
			}
			if(root->dtNext!=NULL){
				if( root->dtNext->dtDatum->iNodeType!=LIST ){
					if(ReturnTransitions[strlen(ReturnTransitions)-1]!='>'){
						strcat(ReturnTransitions, ":"); 
					}
				}
			}
		}
		root = root->dtNext;			//Avanza a derecha el puntero.
	}
	strcat(ReturnTransitions, ";.");	//Concatenacion de fin del arbol de estados.
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

//________________________________________________________
//Evalua si la cadena cumple con los simbolos del alfabeto.

bool validateChais(char *str, char *alpha){
	int i=0;    
	bool flag = true;
	
	while(i<strlen(str)){
		flag= false;
		for(int j = 0; j<strlen(alpha);j++){
			if( str[i]==alpha[j] ){
				flag=true;
			}   	 
		}
		if (flag){
			i++;
		}else{
			i=strlen(str);
		}
	}
	return flag;
}//Funciona.

//METODO ANTEFINAL.
bool evalTransitions(char *str, child root){
	//str: ababababa
	//root = father de las transisiones.
	struct stringType *son = malloc(sizeof(struct stringType));
	child temp = root;
	
	int i = 0;
	bool flag=true;
	
	while( i<strlen(str) ){
		root=temp;
		while(root!=NULL){
			if(flag){
				
			}
			root = root->dtNext;
		}
		i++;
	}
	
	return true;
}

//METODO FINAL.
void evalueChais(three root){ 		//Raiz del arbol.
	
	child fatherAlpha = root->dtNext, fatherTransitions;
	char alpha[20], chais[50], trans[100];
	
	memset(&alpha, '\0', strlen(alpha));
	memset(&trans, '\0', strlen(trans));
	
	getAlpha(&alpha, fatherAlpha->dtDatum);
	
	fatherTransitions = fatherAlpha->dtNext->dtNext->dtNext;
	//getTransition(trans, fatherTransitions->dtDatum);
	
	//printf("\n transiciones: %s", trans);

	printf("\nIngrese una cadena: ");
	leeCad(chais, 50);
	
	if(validateChais(chais, alpha)){
		printf("\nCadena Aceptada (por el alfabeto)");
		//Code evalTrans.
/*		if(evalTransitions(chais, fatherTransitions->dtDatum)){*/
/*			printf("\nFunca. ");*/
/*		}else{*/
/*			printf("\nNo FUNCA.");*/
/*		}*/
	}else{
		printf("\nCadena No aceptada Aceptada (Por cdel alfabeto)");
	}
}
