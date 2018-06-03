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
bool evalTransitions(char *str, child root, char *statesAccept){
	struct stringType *son = malloc(sizeof(struct stringType));
	struct stringType *origin = malloc(sizeof(struct stringType));
	struct stringType *dest = malloc(sizeof(struct stringType));
	child temp, rootCheck;
	
	char destinations[100], origins[100], state[50];
	int i = 0, j = 0, init=0;
	bool flag = false;
	
	temp = root;
	dest = root->dtDatum;
	
	memset(&origins, '\0', strlen(origins));
	strcpy(origins,dest->stChais);
	strcat(origins,";");

	while( i<strlen(str) ){
		init = 0;
		j = 0;
		memset(&destinations, '\0', strlen(destinations));
		while(j<strlen(origins)){
			if(origins[j]==';'){
				memset(&state, '\0', strlen(state));
				copyChais(&state ,origins, init, j);
				root=temp;
				rootCheck = root;
				memset(&destinations, '\0', strlen(destinations));
				while(root!=NULL){
					son = rootCheck->dtDatum;
					if(son->iNodeType==LIST && strcmp(son->stChais,state)==0){
						origin = son;
						rootCheck = rootCheck->dtNext;
						son = rootCheck->dtDatum;
						if(son->iNodeType == CHAR && son->stChais[0]==str[i]){
							rootCheck = rootCheck->dtNext;
							son = rootCheck->dtDatum;
							origin = rootCheck; 
							flag=true;
							while(rootCheck!=NULL && flag){
								if (son->iNodeType != LIST && son->iNodeType != CHAR ) {
									strcat(destinations, son->stChais);
									strcat(destinations, ";");
								}else{
									flag = false;
								}
								rootCheck = rootCheck->dtNext;
								if(rootCheck!=NULL){ 
									son = rootCheck->dtDatum;
								}
							}
						}
					}	
					dest = origin;
					root = root->dtNext;
					rootCheck = root;
				}//Fin while root.
				init=j+1;
			}//Fin if origins.
			j++;
		}//Fin while j.
		memset(&origins, '\0', strlen(origins));
		strcpy(origins,destinations);
		i++;
	}//Fin de while i.
		
	flag = false;
	i = 0; init = 0;
	while(i<strlen(origins)){
		if(origins[i]==';'){
			memset(&state, '\0', strlen(state));
			copyChais(&state, origins, init, i);
			if( strstr(statesAccept,state)!= NULL ){
				flag = true; 
			}else{
				flag = false;
			}
			init = i+1;
		}
		i++;
	}
	return flag;
}//Probando.

//METODO FINAL.
void evalueChais(three root){ 		//Raiz del arbol.
	
	child fatherAlpha, fatherTransitions, fatherAcceptance;
	char alpha[20], chais[50], trans[100], accept[100];
	
	memset(&alpha, '\0', strlen(alpha));
	memset(&trans, '\0', strlen(trans));
	memset(&accept, '\0', strlen(accept));
		
	fatherAlpha = root->dtNext;
	getAlpha(&alpha, fatherAlpha->dtDatum);
	
	fatherAcceptance = fatherAlpha->dtNext->dtNext; 
	getFinish(&accept, fatherAcceptance->dtDatum);
	
	fatherTransitions = fatherAlpha->dtNext->dtNext->dtNext;

	printf("\nIngrese una cadena: ");
	leeCad(chais, 50);
	
	if(validateChais(chais, alpha)){
		//Code evalTrans.
		if(evalTransitions(chais, fatherTransitions->dtDatum,  accept)){
			printf("\nCadena Aceptada por el AF. ");
		}else{
			printf("\nCadena NO ACEPTADA por el AF.");
		}
	}else{
		printf("\nCadena No aceptada  (Por el alfabeto)");
	}
}

