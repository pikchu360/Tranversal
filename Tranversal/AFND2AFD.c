#include "AutomataFinito.h"
#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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


int sizeStates(child root){
	char states[100];
	int sum = 0;
	getStates(&states, root);
	
	for(int i=0; i<strlen(states); i++){
		if(states[i]==';'){
			sum++;
		}
	}
	return (int)pow(2, sum-1);
}

void newAceptationsStates(char* NAS, char *AceptationStates,char* StatesB){
	// NAS nuevo esatdos ahi devuelve, AceptationStates los estados de aceptacion anteriores,StatesB los nuevos estados del AFDB
	char* state[20], Finals[20];
	int initS=0, initF=0;
	bool flag = false; 
	memset(&NAS,'\0',strlen(NAS));
		
	for (int i=0; i<strlen(StatesB);i++){// Recorre los StatesB
		if (StatesB[i]==';'){// separa los estados de B
			memset(&state,'\0',strlen(state));// Limpia el auxiliar
			copyChais(&state,StatesB,initS,i);// copia el estado de B en el auxiliar
			initF=0;// Setea la variable auxiliar de copia
			for(int j=0; j<strlen(AceptationStates);j++){ // recorre los estados de Aceptacion del AFND
				if (AceptationStates[j]==';'){ // separa los estados de aceptacion del AFND
					memset(&Finals,'\0',strlen(Finals));// Limpia el auxiliar Finals
					copyChais(&Finals,AceptationStates,initF,j);// Copia el estado de Aceptacion en el auxiliar
					if(strstr(state,Finals)){// compara si existe la interseccion en distinta de vacia
						if(!exist(NAS,state)){//Si es de aceptacion pregunta si no esta ya en los nuevos estados de aceptacion NAS
							strcat(NAS,state); // Si el estado no estaba lo copia como un nuevo estado de aceptacion
							strcat(NAS,';');
						}//fin if exist
					}//fin if strstr
					initF=j+1;			//setea la variable de copia		
				}//fin if AceptationStates ;
				
			}//Fin for j
			initS=i+1;//setea la variable de copia
		}//fin if StatesB ;
	}//FIN for i
}

void afnd2afd(three *root){
	three temp, rootCheck, fatherT;
	struct stringType *auxChais = (struct stringType*) malloc(sizeof(struct stringType)); 
	struct stringType *son = malloc(sizeof(struct stringType));
	int i=0, j=0, k=0, init=0;
	bool flag , flagDestination;
	char states[2000], alphabet[100], initialState[50], statesOfAcceptance[100], transitions[1000];
	char state[50], origin[100], destinations[100], deltaB[2000], AcceptancesB[1000];
	char cAuxAlp;
	memset(&AcceptancesB, '\0', strlen(AcceptancesB));
	memset(&states, '\0', strlen(states));
	memset(&alphabet, '\0', strlen(alphabet));
	memset(&initialState, '\0', strlen(initialState));
	memset(&statesOfAcceptance, '\0', strlen(statesOfAcceptance));
	memset(&transitions, '\0', strlen(transitions));
	memset(&destinations,'\0',strlen(destinations));
	memset(&origin, '\0', strlen(origin));
	memset(&deltaB, '\0', strlen(deltaB));
	
	temp = (*root);
		
	temp = (*root)->dtNext;
	getAlpha(&alphabet, temp->dtDatum);
	
	temp = temp->dtNext;
	
	auxChais = temp->dtDatum->dtDatum;
	strcpy(initialState, auxChais->stChais);
	
	temp = temp->dtNext;
	getFinish(&statesOfAcceptance, temp->dtDatum);
	
	temp = temp->dtNext;
	fatherT = temp->dtDatum;		//Posicion del padre del arbol de transiciones.
	
	//Copia del estado en el que me voy a parar segun la transicion.	
	strcpy(states, initialState);	
	strcat(states, ";");
	
	while(k<strlen(states)){		//El corte de ciclo esta dado por el concepto indice<2^|P(Q)|
		if (states[k]==';') {
			//Realizo la actualizacion del nuevo origen.
			memset(&origin, '\0', strlen(origin));
			copyChais(&origin,states,init,k);
			strcat(origin, ";");
			i=0;
			while(i<strlen(alphabet)){				//Analiza cada simbolo del alfabeto. 
				flagDestination = true;
				if (alphabet[i]!=';'&& alphabet[i]!='.') {	//Separacion de los simbolos del alfabeto.';' es el que indica el fin de un estado.
					j = 0;
					init=0;							//Setea indice de los estados.
					while(j<strlen(origin)){		//Analiza el estado de origen. EJ (q,a) o ({p,q},a) , seria 'q' y del segundo seria 'p,q'.
						if(origin[j]==',' || origin[j]==';'){		//Recuperacion de 1 estado del conjunto de estados 'origin'.
							memset(&state, '\0', strlen(state));	//Limpio el auxiliar state.
							copyChais(&state, origin, init, j);	//Copio en state un estado de origin.
							//Recorre el arbol de transiciones.
							temp = fatherT;				//temp apunta al padre del arbol de transisiones.
							rootCheck = temp;			//puntero auxiliar para el analisis.
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
												if(flagDestination){
													memset(&destinations,'\0',strlen(destinations));
													strcat(destinations, son->stChais);
													flagDestination=false;
												}else if (strstr(destinations,son->stChais)==NULL) {
													strcat(destinations, ",");
													strcat(destinations, son->stChais);
												}
											}else{
												flag = false;		//Corta el recorrido cuando entra una nueva transision.
											}
											rootCheck = rootCheck->dtNext;
											if(rootCheck!=NULL){ 
												son = rootCheck->dtDatum;
											}
										}//Fin Armado de estados destinos.
									}
								}	
								temp = temp->dtNext;
								rootCheck = temp;
							}//Fin while temp.
							init = j+1;
						}//Fin If , y ;
						j++;
					}//Fin j, recorrido origen. 
					strcat(destinations, ";");
					if (destinations[0]!=';') {
						strcat(deltaB, origin);
						deltaB[strlen(deltaB)-1]= ':';
						cAuxAlp =(char)alphabet[i]; // falla concatena cosas demas
						deltaB[strlen(deltaB)]= cAuxAlp;
						strcat(deltaB, ">");
						strcat(deltaB, destinations);
					}
								
					if(!exist(states, destinations) && destinations!=";"){	//Formando el nuevo conjunto de estado del AFD equivalentes. (Qb)
						strcat(states, destinations);
					}
					memset(&destinations,'\0',strlen(destinations)); //limpia la variable que guardara los estados de las transisiones.
				}//Fin if alphabet;
				i++;
			}//Fin i, recorrido Alfabeto.
			init = k+1;
		}//Fin If
		
		k++;
	}//Fin Recorrido Partes de Q.
	
	newAceptationsStates(AcceptancesB,statesOfAcceptance,states);
	
	printf("\n\n\nStatesB: %s",states);
	printf("\nDeltaB:  %s",deltaB);
	printf("\n\n\nAceptacion : %s",AcceptancesB);
	
}
