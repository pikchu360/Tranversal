#include "AutomataFinito.h"
#include "Menu.h"
#include "Operaciones.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//______________________________________________
//METODOS PARA CARGAR CADA CONJUNTO DEL AUTOMATA.

void loadStates(child *root){
	char status[100];		//String donde se guardaran los estados ingresados.
	int init=0;				//indice para hacer una copia correcta.
	
	printf("\n________________________________________________________________________");
	printf("\nEstado/os del automata: \n\n");
	
	MenuState(&status);							//Guarda en status todos los estados ingresados, separado por un ';'.
	for(int i = 0; i < strlen(status); i++)	{	//Recorro status como si fuera array.
		if(status[i]==';'){						//Cuando encuentra un ';', lo anterior a eso es un estado.
			fflush(stdin);						//Limpio el buffer de entrada.
			if(i-init==1){						//Control para saber si es de tipo char o string. si es 1 es de tipo char.
				struct charType *in = (struct charType*) malloc(sizeof(struct charType));
				copyChais(&(*in).cValue, status, init, i);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
				(*in).iNodeType = CHAR;							//Asignacion de codigo del tipo de dato.
				insert(&(*root), in);							//Inserta en el arbol el dato de tipo charType.
			}else{
				struct stringType *in = (struct stringType*) malloc(sizeof(struct stringType));
				copyChais(&(*in).stChais, status, init, i);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
				(*in).iNodeType = STRING;						//Asignacion de codigo del tipo de dato.
				insert(&(*root), in);							//Inserta en el arbol el dato de tipo stringType.
			}	
			init = i+1;		//Incrementa el indice de indicando la posicion de donde comienza el siguiente estado.
		}
	}	
}//Funciona.

void loadAlphabet(child *root){
	char alph[100];			//Variable que guardara el alfabeto.
	int init=0;				//indice para hacer una copia correcta.
	
	printf("\n________________________________________________________________________");
	printf("\nAlfabeto del automata: \n\n\n");
	MenuAlpha(&alph);
	for(int i = 0; i < strlen(alph); i++)	{	//Recorro status como si fuera array.
		if(alph[i]==';'){						//Cuando encuentra un ';', lo anterior a eso es un estado.
			fflush(stdin);						//Limpio el buffer de entrada.
			struct charType *in = (struct charType*) malloc(sizeof(struct charType));
			copyChais(&(*in).cValue, alph, init, i);	//Carga el valor del caracter alpha en el registro de tipo charType.
			(*in).iNodeType = CHAR;						//Asignacion de codigo del tipo de dato.
			insert(&(*root), in);						//Inserta el registro en el arbol.
			init = i+1;				//Incremento del indice necesario para la copia de caracteres hacia el registro de tipo charType.
		}
	}
}//Funciona.

void loadInitialState(child *root, child set){
	struct stringType *initialState = malloc(sizeof(struct stringType));
	initialState = set->dtDatum;
	insert(&(*root), initialState);
}//Funciona.

void loadStateOfAcceptance(child *root, child set){
	char states[100], accepted[50];			//string para los estados y otro para los estados de aceptacion.
	int init=0;									//indice para hacer una copia correcta.
	
	memset(&states, '\0', strlen(states));		//Limpio variables. 
	memset(&accepted, '\0', strlen(accepted));	//Limpio variables. 
	
	printf("\n________________________________________________________________________");
	printf("\nEstado/os de Aceptacion: \n\n\n");	
	getStates(&states, set);			//Obtencion de los estados desde el arbol.
	MenuFinish(&accepted, states);				//Separa los que son de aceptacion segun el usuario.
	
	for(int i = 0; i < strlen(accepted); i++)	{	//Recorro status como si fuera array.
		if(accepted[i]==';'){						//Cuando encuentra un ';', lo anterior a eso es un estado.
			fflush(stdin);							//Limpio el buffer de entrada.
			if(i-init==1){							//Control para saber si es de tipo char o string. si es 1 es de tipo char.
				struct charType *in = (struct charType*) malloc(sizeof(struct charType));
				copyChais(&(*in).cValue, accepted, init, i);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
				(*in).iNodeType = CHAR;							//Asignacion de codigo del tipo de dato.
				insert(&(*root), in);							//Inserta en el arbol el dato de tipo charType.
			}else{
				struct stringType *in = (struct stringType*) malloc(sizeof(struct stringType));
				copyChais(&(*in).stChais, accepted, init, i);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
				(*in).iNodeType = STRING;						//Asignacion de codigo del tipo de dato.
				insert(&(*root), in);							//Inserta en el arbol el dato de tipo stringType.
			}	
			init = i+1;		//Incrementa el indice de indicando la posicion de donde comienza el siguiente estado.
		}
	}
}//Funciona.

void loadTransitions(child *root, child set){
	char transitions[1000], states[100], alpha[50], str[20];
	int init = 0, iniStr=0;
	int cod;
	bool flag;
	
	memset(&transitions, '\0', strlen(transitions));
	memset(&states, '\0', strlen(states));
	memset(&alpha, '\0', strlen(alpha));
	
	getStates(&states, set->dtDatum);
	set = set->dtNext;
	getAlpha(&alpha, set->dtDatum);
	
	MenuDelta(&transitions, states, alpha);
	
	for(int i = 0; i < strlen(transitions); i++)	{	//Recorro status como si fuera array.
		if(transitions[i]==';'){						//Cuando encuentra un ';', Nueva Transision.
			//Nueva asignacion de code LIST.
			cod = LIST;
			flag=true;
			for(int k=init; k<=i; k++){
				if( transitions[k]==':' || transitions[k]=='>' || transitions[k]==';'){
					fflush(stdin);				//Limpio el buffer de entrada.
					
					if(!flag){
						if(k-iniStr==1){
							cod = CHAR;
						}else{
							cod = STRING;
						}
					}
					
					if(k-iniStr==1){			//Control para saber si es de tipo char o string. si es 1 es de tipo char.
						struct charType *in = (struct charType*) malloc(sizeof(struct charType));
						copyChais(&(*in).cValue, transitions, iniStr, k);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
						(*in).iNodeType = cod;							//Asignacion de codigo del tipo de dato.
						insert(&(*root), in);							//Inserta en el arbol el dato de tipo charType.
					}else{
						struct stringType *in = (struct stringType*) malloc(sizeof(struct stringType));
						copyChais(&(*in).stChais, transitions, iniStr, k);		//Copia desde 'init' hasta 'i' la subcadena status al valor del registro.
						(*in).iNodeType = cod;						//Asignacion de codigo del tipo de dato.
						insert(&(*root), in);							//Inserta en el arbol el dato de tipo stringType.
					}
					flag=false;
					iniStr=k+1;
				}
			}//Fin extracion de cadena o caracter.	
			init = i+1;		//Incrementa el indice de indicando la posicion de donde comienza el siguiente estado.
		}
	}
}//Funciona.

//==============================================================================
//METODOS DE IMPRESION.

//Metodos para imprimir arbol.
void inOrder(three node){
	//printf("\ncode: %d = SET\n", node->iNodeType);
	if( node!=NULL ){
		//inOrder(node->dtDatum);
		printThree(node->dtDatum);
		inOrder(node->dtNext);
	}
}

void inOrderTr(three node){
	if( node!=NULL ){
		printThreeTrans(node->dtDatum);
		inOrderTr(node->dtNext);
	}
}

//Metodo para imprimir un registro de tipo stringType.
void printThree(child node){
	
	struct stringType *chais =  malloc(sizeof(struct stringType));
	struct charType *character =  malloc(sizeof(struct charType));
	
	if(node->iNodeType == STRING){ chais = node; }
	else{ character = node; }
	switch (node->iNodeType){
	case STRING:
		if(node->iNodeType!=SET && node->iNodeType!=LIST){
			//printf(" %s \tcode: %d = STRING", chais->stChais, chais->iNodeType);
			printf(" %s ", chais->stChais);
		}	
		break;
	case CHAR:
		
		if(node->iNodeType!=SET && node->iNodeType!=LIST){
			//printf(" %c \tcode: %d = CHAR", character->cValue, character->iNodeType);
			printf(" %c ", character->cValue);
		}	
		break;
	default:
		break;
	}
}

void printThreeTrans(child node){
	
	struct stringType *chais =  malloc(sizeof(struct stringType));
	struct charType *character =  malloc(sizeof(struct charType));
	
	int sizeAux;
	
	if(node->iNodeType == STRING){ chais = node; }
	if(node->iNodeType == CHAR){ character = node; }
	if(node->iNodeType == LIST){ chais = node; }
	
	switch (node->iNodeType){
	case STRING:
		if(node->iNodeType!=SET ){
			//printf(" %s \tcode: %d = STRING", chais->stChais, chais->iNodeType);
			printf(" %s ", chais->stChais);
		}	
		break;
	case CHAR:
		
		if(node->iNodeType!=SET ){
			//printf(" %c \tcode: %d = CHAR", character->cValue, character->iNodeType);
			printf(" %c ", character->cValue);
		}
	case LIST:
		printf(" %s ", chais->stChais);
		break;
	default:
		break;
	}
}

//________________________________________________
//METODOS PARA IMPRIMIR CADA CONJUNTO DEL AUTOMATA.

void showStates(child root){
	printf("\n..................Satus = {");
	inOrder(root);
	printf("}");
}

void showAlphabet(child root){
	printf("\n...............Alphabet = {");
	inOrder(root);
	printf("}");
}

void showInitialState(child root){
	printf("\n.......Initial State(s) = {");
	inOrder(root);
	printf("}");
}

void showStateOfAcceptance(child root){
	printf("\nStates of Acceptance(s) = {");
	inOrder(root);
	printf("}");
}

void showTransitions(child root){
	printf("\n.........Transitions(s) = {");
	inOrderTr(root);
	printf("}");
}

//==============================================================================
//METODOS PRINCIPALES.

//Carga el arbol.
void loadAll(three *root){
	
	three temp, aux;
	int index=1;
	
	*root = malloc(sizeof(three));		//Reservo memoria para el arbol.
	(*root)->iNodeType = SET;			//Es de tipo set ya que es la raiz del arbol.
	temp = (*root);						//Copia temporal de la raiz del arbol.
	
	while(index<=5){
		switch (index){
		case 1:
			loadStates(&(*root)->dtDatum);
			break;
		case 2:
			
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadAlphabet(&(*root)->dtDatum);
			
			break;
		case 3:				
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadInitialState(&(*root)->dtDatum, temp->dtDatum);
			
			break;
		case 4:
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadStateOfAcceptance(&(*root)->dtDatum, temp->dtDatum);
			break;
		case 5:
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadTransitions(&(*root)->dtDatum, temp);
			break;
			
		default:
			break;
		}
		index++;
	}
	
	(*root) = temp;
}

//Muestra el arbol.
void showAll(three root){
	printf("\n\n\n________________________________________________________________________");
	showStates(root->dtDatum);			//Paso el padre del arbol de los estados.
	
	root = root->dtNext;
	showAlphabet(root->dtDatum);
	
	root = root->dtNext;
	showInitialState(root->dtDatum);
	
	root = root->dtNext;
	showStateOfAcceptance(root->dtDatum);
	
	root = root->dtNext;
	showTransitions(root->dtDatum);
	
	printf("\n\n________________________________________________________________________\n\n\n");
}
