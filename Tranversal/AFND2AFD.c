#include "AutomataFinito.h"
#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Metodo para analizar si un estado ya existe en algun conjunto de estados.
bool exist(char *states, char *src){
	int i = 0, j = 0, init1 = 0, init2 = 0;
	char state1[50], state2[50];
	bool flag = false, flag2;

	while (i<strlen(states) && !flag){				//Recorre los estados.
		if (states[i]==';') {							//separo por estados un conjunto de estados de 1 o mas elementos.
			memset(&state1, '\0', strlen(state1));		
			copyChais(&state1, states, init1, i);	
			if (strlen(state1)+1==strlen(src)) {		//Evita comparaciones con sub-estados.
				j = 0;
				init2=0;
				flag2 = true;							//Bandera para cortar la busqueda. Si no esta un estado unitario.
				while (j<strlen(src) && flag2) {		//Recorre el estado que se busca separando si contiene mas de un estado.
					if (src[j]==',' || src[j]==';'){	//Separacion de sub-estados.
						memset(&state2, '\0', strlen(state2));
						copyChais(&state2, src, init2, j);
						if (strstr(state1, state2)!=NULL){		//Busca un sub-estado en un estado.
							flag = true;
						}else{
							flag = false;
							flag2 = false;
						}//Fin if strstr
						init2 = j+1;
					}//Fin if separacion de sub-estados.
					j++;
				}//Fin while j.
			}else{
				flag = false;
			}
			init1 = i+1;
		}//Fin if separador de estados.
		i++;
	}//Fin while i.
	return flag;
}//Funciona.

/*bool exist2(char *states, char *src){*/
/*	int i = 0, init1 = 0;*/
/*	char state1[50];*/
/*	bool flag = false;*/
	
	
/*		while (i<strlen(states) && flag){*/
/*			if (states[i]==";") {*/
/*				memset(&state1, '\0', strlen(state1));*/
/*				copyChais(&state1, states, init1, i);						*/
/*					if (strcmp(state1, src)){*/
/*						flag = true;*/
/*					}else{*/
/*						flag = false;*/
/*					}					*/
/*			}*/
/*			init1 = i+1;*/
/*			i++;*/
/*		}*///Fin while i.
		
/*	return flag;*/
/*}*/



void afnd2afd(three *root){
	three temp = *root, rootCheck, fatherT;
	struct stringType *auxChais = (struct stringType*) malloc(sizeof(struct stringType)); 
	struct stringType *son = malloc(sizeof(struct stringType));
	int i=0, j=0, init = 0, k=0;
	bool flag;
	char states[2000], alphabet[100], initialState[50], statesOfAcceptance[100], transitions[1000];
	char state[50], origin[100], destinations[100], deltaB[2000];
	
	memset(&states, '\0', strlen(states));
	memset(&alphabet, '\0', strlen(alphabet));
	memset(&initialState, '\0', strlen(initialState));
	memset(&statesOfAcceptance, '\0', strlen(statesOfAcceptance));
	memset(&transitions, '\0', strlen(transitions));

	memset(&origin, '\0', strlen(origin));
	//getStates(&states, temp->dtDatum);
	
	temp = temp->dtNext;
	getAlpha(&alphabet, temp->dtDatum);
	
	temp = temp->dtNext;
	//getInitialState(&initial,)
	auxChais = temp->dtDatum;
	strcpy(initialState, auxChais->stChais);
	
	temp = temp->dtNext;
	getFinish(&statesOfAcceptance, temp->dtDatum);
	
	temp = temp->dtNext;
	getTransition(&transitions, temp->dtDatum);
	
	fatherT = temp;		//Posicion del padre del arbol de transiciones.
	
	//Copia del estado en el que me voy a parar segun la transicion.	
	strcpy(states, initialState);
	strcat(states, ";");
	
	memset(&deltaB, '\0', strlen(deltaB));
	
	while (k<strlen(states)) {
		if (states[k]==";") {
			//Realizo la actualizacion del nuevo origen.
			memset(&origin, '\0', strlen(origin));
			copyChais(&origin,states,init,k);
			strcat(origin, ";");
			i=0;
			while(i<strlen(alphabet)){				//Analiza cada simbolo del alfabeto. 
				if (alphabet[i]!=";") {			//Separacion de los simbolos del alfabeto.';' es el que indica el fin de un estado.
					j = 0;
					init=0;//Setea indice de los estados.
					while(j<strlen(origin)){		//Analiza el estado de origen. EJ (q,a) o ({p,q},a) , seria 'q' y del segundo seria 'p,q'.
						if(origin[j]=="," && origin[j]!=";"){		//Recuperacion de 1 estado del conjunto de estados 'origin'.
							memset(&state, '\0', strlen(state));	//Limpio el auxiliar state.
							copyChais(&state, origin, init, j);	//Copio en state un estado de origin.
							
							//Recorre el arbol de transiciones.
							temp = fatherT;				//temp apunta al padre del arbol de transisiones.
							rootCheck = temp;			//puntero auxiliar para el analisis.
							//memset(&destinations, '\0', strlen(destinations));		//limpia la variable que guardara los estados de las transisiones.
							while(temp!=NULL){					//Recorrido del arbol de transiciones del AFND.
								son = rootCheck->dtDatum;		//Registro contenedor de la cadena representante de un estado o alfabeto.
								if(son->iNodeType==LIST && strcmp(son->stChais,state)==0){		//Verificador de cada transicion.
									rootCheck = rootCheck->dtNext;			//Avanza el puntero para analizar los estados destino de un transicion.
									son = rootCheck->dtDatum;				//Actualiza el registro al siguiente. ya que apuntaba al origen de una transicion.
									if(son->iNodeType == CHAR && son->stChais[0]==alphabet[i]){		//Analiza el simbolo del alfabeto de la funcion delta.
										rootCheck = rootCheck->dtNext;		//Actualiza el apuntador para trabajar con los destino de la transisiones.
										son = rootCheck->dtDatum;			//Actualiza el registro a un estado destino.
										flag=true;							//Bandera usada para detener los procesos.
										while(rootCheck!=NULL && flag){	//Recorro los estados destino.
											if (son->iNodeType != LIST && son->iNodeType != CHAR ) {	//Trabaja solamente en los estado de destino.
												
												if (strstr(destinations,son->stChais)==NULL || strlen(destinations)==0 ) {
													strcat(destinations, son->stChais);
													strcat(destinations, ",");
												}
											}else{
												flag = false;		//Corta el recorrido cuando entra una nueva transision.
											}
											rootCheck = rootCheck->dtNext;
											if(rootCheck!=NULL){ 
												son = rootCheck->dtDatum;
											}
										}//Fin Armado de estados destinos.
										
										//Armar nuevos origenes y nuevas transisiones.  
										//{q0,q3}:a > {q1,q8,q5} y se guarda, a su ves guardar como nuevo estado {q1,q8,q5}
										//Chequear que no existe el nuevo estado formado por la transicion {q1,q8,q5} (o variaciones)
										
									}
								}	
								temp = temp->dtNext;
								rootCheck = temp;
							}//Fin while temp.
							init = j+1;
						}
						//  {q0}:a > {q1,q0}
						//	deltaB=" {q0}:a>{q0,q1} ; {q0}:b>{q1} ... "
						//  {q0,q1}:a>{q0,q1}
						//	deltaB=" {q0}:a>{q0,q1} ; {q0}:b>{q1} ; {q0,q1}:a>{q0,q1} ... "
						//  {q0,q1}:a>{q0,q1}
						//Evalua si los destino obtenidos ya existen en el conjunto de transisione. Si no existen entonces los agrega, Caso contrario no hace nada y continua. 
						//if ( !exist(deltaB, destinations) ) {
							//Armo una transicion.
							strcat(deltaB, origin);
							strcat(deltaB, ":");
							strcat(deltaB, alphabet[i]);
							strcat(deltaB, ">");
							strcat(deltaB, destinations);
							strcat(deltaB, ";");
						//}
						
						if(!exist(states, destinations)){	//Formando el nuevo conjunto de estado del AFD equivalentes. (Qb)
							strcat(states, destinations);
							strcat(states, ";");
						}
						
						j++;
					}//Fin k, recorrido origen. 
					
				}//Fin if alphabet;
				i++;
			}//Fin i, recorrido Alfabeto.
		}//Fin If
		init = k+1;
		k++;
	}//Fin while k.
	printf("\nStatesB: %s",states);
	printf("\nDeltaB:  %s",deltaB);
}

/*
hacer un free(inOrder) del arbol completo 
*/

/*
temp = fatherT;				//temp apunta al padre del arbol de transisiones.
rootCheck = temp;			//puntero auxiliar para el analisis.
memset(&destinations, '\0', strlen(destinations));		//limpia la variable que guardara los estados de las transisiones.
while(temp!=NULL){					//Recorrido del arbol de transiciones del AFND.
son = rootCheck->dtDatum;		//Registro contenedor de la cadena representante de un estado o alfabeto.
if(son->iNodeType==LIST && strcmp(son->stChais,state)==0){		//Verificador de cada transicion.
//origin = son;
rootCheck = rootCheck->dtNext;			//Avanza el puntero para analizar los estados destino de un transicion.
son = rootCheck->dtDatum;				//Actualiza el registro al siguiente. ya que apuntaba al origen de una transicion.
if(son->iNodeType == CHAR && son->stChais[0]==str[i]){		//Analiza el simbolo del alfabeto de la funcion delta.
rootCheck = rootCheck->dtNext;		//Actualiza el apuntador para trabajar con los destino de la transisiones.
son = rootCheck->dtDatum;			//Actualiza el registro a un estado destino.
//origin = rootCheck; 				//
flag=true;							//Bandera usada para detener los procesos.
while(rootCheck!=NULL && flag){	//Recorro los estados destino.
if (son->iNodeType != LIST && son->iNodeType != CHAR ) {	//Trabaja solamente en los estado de destino.
strcat(destinations, son->stChais);s
strcat(destinations, ",");
}else{
flag = false;		//Corta el recorrido cuando entra una nueva transision.
}
rootCheck = rootCheck->dtNext;
if(rootCheck!=NULL){ 
son = rootCheck->dtDatum;
}
}//Fin Armado de estados destinos.

//Armar nuevos origenes y nuevas transisiones.  
//{q0,q3}:a > {q1,q8,q5} y se guarda, a su ves guardar como nuevo estado {q1,q8,q5}
//Chequear que no existe el nuevo estado formado por la transicion {q1,q8,q5} (o variaciones)

}
}	
temp = temp->dtNext;
rootCheck = temp;
}//Fin while root.
*/
