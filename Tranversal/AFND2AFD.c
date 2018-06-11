#include "AutomataFinito.h"
#include "Operaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void newAceptationsStates(char* NAS, char *AceptationStates,char* StatesB){
	// NAS nuevo esatdos ahi devuelve, AceptationStates los estados de aceptacion anteriores,StatesB los nuevos estados del AFDB
	char* state[20]={'\0'}, Finals[20]={'\0'};
	int initS=0, initF=0;
	memset(&NAS,'\0',strlen(NAS));
		
	for (int i=0; i<strlen(StatesB);i++){			// Recorre los StatesB
		if (StatesB[i]==';'){						// separa los estados de B
			memset(&state,'\0',strlen(state));		// Limpia el auxiliar
			copyChais(&state,StatesB,initS,i);		// copia el estado de B en el auxiliar
			strcat(state,";");
			initF=0;								// Setea la variable auxiliar de copia
			for(int j=0; j<strlen(AceptationStates);j++){ 	// recorre los estados de Aceptacion del AFND
				if (AceptationStates[j]==';'){ 				// separa los estados de aceptacion del AFND
					memset(&Finals,'\0',strlen(Finals));		// Limpia el auxiliar Finals
					copyChais(&Finals,AceptationStates,initF,j);	// Copia el estado de Aceptacion en el auxiliar
					if(strstr(state,Finals)!=NULL){				// compara si existe la interseccion en distinta de vacia
						//printf("\nif %s <- %s",NAS, state );
						if(!exist(NAS,state)){						//Si es de aceptacion pregunta si no esta ya en los nuevos estados de aceptacion NAS
							strcat(NAS,state); 						// Si el estado no estaba lo copia como un nuevo estado de aceptacion
						}//fin if exist
					}//fin if strstr
					initF=j+1;					//setea la variable de copia		
				}//fin if AceptationStates ;
			}//Fin for j
			initS=i+1;							//setea la variable de copia
		}//fin if StatesB ;
	}//FIN for i
}

//Metodo para la conversion de AFND a AFD. 
void afnd2afd(three *newRoot, three root){				//Viene el arbol completo. 
	three temp, rootCheck, fatherT;		//Auxiliares para no modificar la raiz del arbol.
	struct stringType *auxChais = (struct stringType*) malloc(sizeof(struct stringType));	//Variable para trabajar el tipo de dato guardado. 
	struct stringType *son = malloc(sizeof(struct stringType));								//Idem.
	int i=0, j=0, k=0, init=0;			//Indices para ciclos y alguna funcion.
	bool flag , flagDestination;		//Banderas de control de fin de ciclos.
	//Declaracion de todos las cadenas necesarias para el manejo de la creacion del nuevo automata equivalente.
	char states[2000]={'\0'}, alphabet[100]={'\0'}, initialState[50]={'\0'}, statesOfAcceptance[100]={'\0'}, chAux[10]={'\0'};
	char state[50]={'\0'}, origin[100]={'\0'}, destinations[100]={'\0'}, deltaB[2000]={'\0'}, AcceptancesB[1000]={'\0'}, auxDelta[50] = {'\0'};
	
	//Harcord the three.
	temp = root;				//Asignacion de puntero auxiliar, hacia la raiz del arbol.
	temp = root->dtNext;	//Avanza el puntero a derecha del arbol.
	getAlpha(&alphabet, temp->dtDatum);	//Obtencion del alfabeto del AF.
	
	temp = temp->dtNext;					//Avanza a derecha el puntero.
	auxChais = temp->dtDatum->dtDatum;		//Copia la estructura stringType o charType en auxChais.
	strcpy(initialState, auxChais->stChais);//Extraccion del estado inicial del del AF.
	
	temp = temp->dtNext;							//Avanza el puntero a derecha.
	getFinish(&statesOfAcceptance, temp->dtDatum);	//Obtencion de los estados de aceptacion del AF.
	
	temp = temp->dtNext;		//Avanza el puntero a derecha.
	fatherT = temp->dtDatum;	//Posicion del padre del arbol de transiciones.
	
	strcpy(states, initialState);	//Copia del estado en el que me voy a parar segun la transicion.
	strcat(states, ";");			//Concatenacion necesaria para separar cada estado nuevo.
	
	while(k<strlen(states)){		//Recorre los estados del AFD equivalente.
		if (states[k]==';') {		//separacion de estados.
			//Realizo la actualizacion del nuevo origen.
			memset(&origin, '\0', strlen(origin));
			copyChais(&origin,states,init,k);
			strcat(origin, ";");
			i=0;
			while(i<strlen(alphabet)){				//Recorrido del alfabeto del AF. 
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
												if(flagDestination){		//La bandera controla la primera transicion evaluada.
													memset(&destinations,'\0',strlen(destinations));	//Limpieza.
													strcat(destinations, son->stChais);				//concatena el estado de llegada.
													flagDestination=false;
												}else if (strstr(destinations,son->stChais)==NULL) {	//Control de existencia de un nuevo estado de llegada.
													strcat(destinations, ",");							//Separacion de sub-estados.
													strcat(destinations, son->stChais);				//concatena el nuevo estado de llegada.
												}
											}else{
												if (son->iNodeType != LIST && son->iNodeType == CHAR ) {	//Trabaja solamente en los estado de destino.
													if(flagDestination){									//La bandera controla la primera transicion evaluada.
														memset(&destinations,'\0',strlen(destinations));	//Limpieza.
														strcat(destinations, son->stChais);				//concatena el estado de llegada.
														flagDestination=false;
													}else if (strstr(destinations,son->stChais)==NULL) {	//Control de existencia de un nuevo estado de llegada.
														strcat(destinations, ",");							//Separacion de sub-estados.
														strcat(destinations, son->stChais);				//concatena el nuevo estado de llegada.
													}
												}else{
													flag = false;
												}//Fin else del if Armado de destinos de CHAR
											}//Fin else del if Armado de destinos de STRING
											rootCheck = rootCheck->dtNext;	//Avanza el puntero a su derecha.
											if(rootCheck!=NULL){ 			//Control para hijo izquierdo.
												son = rootCheck->dtDatum;	//Asignacion de datos.
											}
										}//Fin while Armado de estados destinos.
									}//Fin if son->iNodeType == CHAR && son->stChais[0]==alphabet[i]
								}//Fin if son->iNodeType==LIST && strcmp(son->stChais,state)==0
								temp = temp->dtNext;
								rootCheck = temp;
							}//Fin while temp.
							init = j+1;
						}//Fin If , y ;
						j++;
					}//Fin j, recorrido origen.
					strcat(destinations, ";");					
					
					if (destinations[0]!=';') {	//Control para concatenar correctamente las nuevas transiciones.
						strcat(auxDelta, origin);
						auxDelta[strlen(auxDelta)-1]= ':';
						auxDelta[strlen(auxDelta)] = '\0';
						auxDelta[strlen(auxDelta)] = alphabet[i];
						auxDelta[strlen(auxDelta)] = '\0';
						strcat(auxDelta, ">");
						strcat(auxDelta, destinations);
						
						strcat(deltaB, auxDelta);
						memset(&auxDelta, '\0', strlen(auxDelta));
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
	generateAFD(&(*newRoot), states, alphabet, AcceptancesB, deltaB);
}

void generateAFD(three *root, char *states, char *alphabet, char *statesFinish, char *transitions){
	three temp, fatherStates;
	int index=1;
	
	*root = malloc(sizeof(three));		//Reservo memoria para el arbol.
	(*root)->iNodeType = SET;			//Es de tipo set ya que es la raiz del arbol.
	temp = (*root);						//Copia temporal de la raiz del arbol.
	
	while(index<=5){
		switch (index){
		case 1:
			loadStates(&(*root)->dtDatum, false, states);
			break;
		case 2:
			
			fatherStates = (*root);
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadAlphabet(&(*root)->dtDatum, fatherStates, false, alphabet);
			
			break;
		case 3:				
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadInitialState(&(*root)->dtDatum, fatherStates->dtDatum);
			
			break;
		case 4:
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadStateOfAcceptance(&(*root)->dtDatum, temp->dtDatum, false, statesFinish);
			break;
		case 5:
			(*root)->dtNext = malloc(sizeof(three));
			(*root) = (*root)->dtNext;
			(*root)->iNodeType = SET;
			loadTransitions(&(*root)->dtDatum, temp, false, transitions);
			break;
			
		default:
			break;
		}
		index++;
	}
	
	(*root) = temp;
}
