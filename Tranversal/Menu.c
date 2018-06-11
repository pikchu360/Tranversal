#include "Menu.h"
#include "Operaciones.h"
#include "AutomataFinito.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//METODO AUXILIAR.
//Opcion para continuar o no el ingreso.
bool option(){
	char opt[2];
	do{
		leeCad(opt,2);
		if ( opt[0]=='s' || opt[0]=='S') {
			return true;
		}
		else if (opt[0] == 'n' || opt[0]=='N')
		{
			return false;
		}else {
			printf("\tError. Ingrese 'S' o 'N': ");
			printf(" %s ", opt);
		}
	}while(opt[0]!='s' && opt[0]!='S' && opt[0]!='n' && opt[0]!='N' );
}//Funciona.

//Retorna una cadena modificada.
void MenuState(char* ReturnStates){	
	// Load States 
	char States[100], Aux[10];
	int entrada;
	do{				
		entrada = 0;
		printf ("\nCargue el estado inicial: ");
		leeCad(States,100);
		strcat(States, ";");
		while (entrada == 0){
			printf("Carge nuevo estado: ");
			leeCad(Aux,10);
			strcat(Aux, ";");
			if (strstr(States,Aux) == NULL ){
				strcat(States,Aux);
				printf("\t\tContinuar carga? S/N: ");
				if( !option() ){
					entrada = 1	;
				}
			}else{ 
				printf("\nError. Ya existe el estado ingresado!!!\n"); 
			}
		}
		printf("\t¿Estos son sus Estados? Q={ %s } -> S/N: ", States);
	}while( !option() );
	strcat(States,"_;.");
	strcpy(ReturnStates,States);
}//Funciona.

void MenuAlpha(char* Alpha, char *States){	
	int entrada;
	char Symbol[100], Aux[3];
	do{
		entrada = 0;
		memset(&Symbol,'\0', strlen(Symbol));	
		while (entrada == 0){
			printf("Cargue un simbolo de su AF: ");
			leeCad(Aux, 3);
			strcat(Aux, ";");
			if (!exist(States, Aux)) {
				if ( strstr(Symbol,Aux)==NULL && strlen(Aux)==2 ){
					strcat(Symbol,Aux);
					printf("\t\tContinuar carga? S/N: ");
					if( !option() ){
						entrada = 1	;
					}
				}else{
					if(strlen(Aux)>2){
						printf("\nError. Ingrese 1 solo caracter!!!\n");
					}else{
						printf("\nError. %s Ya fue ingrsado!!!\n", Aux);
					}
				}
			}else{
				printf("\nError. Existe un Estado en Q con ese Simbolo . Podria usar minuscula o mayuscula. (A<>a)\n");
			}
		}
		printf("\t¿Este es su Alfabeto? Alphabet={ %s } -> S/N: ", Symbol);
	} while ( !option() );
	strcat(Symbol, ".");
	strcpy(Alpha,Symbol);
}//Funciona.

void MenuFinish(char* FStates, char* States){ //Load Final State
	char FinalState[100], Aux[10];
	int entrada;
	do{		
		entrada = 0;
		memset(&FinalState,'\0', strlen(FinalState));
		while (entrada == 0){
			printf("Nuevo estado final: ");
			leeCad(Aux, 10);
			strcat(Aux, ";");
			if (strstr(States,Aux)== NULL ){
				printf("\nError. '%s' No existe en el AF:\n ",Aux);
			}else{
				if( strstr(FinalState,Aux)==NULL ){
					strcat(FinalState,Aux);
				}else{
					printf("\tError. Ya cargo '%s'!!! \n", Aux);
				}
				printf("\t\tContinuar carga? S/N: ");
				if( !option() ){
					entrada = 1	;
				}
			}
		}
		printf("\t¿Son sus Estados de Aceptacion? F={ %s } -> S/N: ", FinalState);
	}while ( !option() );
	strcat(FinalState,".");		
	strcpy(FStates,FinalState);	
}//Funciona.

void MenuDelta(char* DeltaFunction ,char* States, char* Alpha){//load function Delta
	char delta[1000], origin[50], destinations[50], state[20], in[10];
	bool entrada, ex;
	int init;
	
	do{
		init = 0;
		memset(&delta ,'\0',strlen(delta));
		for(int iSt = 0; iSt < strlen(States); iSt++){
			//Veo si completo un estado.
			if(States[iSt]==';'){
				memset(&state, '\0', strlen(state));
				copyChais(&state, States, init, iSt);		//obtengo 1 estado.
				if(strstr(state, "_")==NULL){
					//Analizo el estado con cada simbolo del alfabeto.
					for(int iAl = 0; iAl < strlen(Alpha); iAl++){
						//Veo si compleeto el alfabeto.
						if( Alpha[iAl]!=';' && Alpha[iAl]!='.'){
							memset(&origin ,'\0',strlen(origin));
							memset(&destinations ,'\0',strlen(destinations));
							//Armado de el punto de partida. Ej (q0:a).
							strcat(origin, state);
							strcat(origin, ":");
							origin[strlen(origin)] = Alpha[iAl];
							strcat(origin, ">");
							
							//Ciclo de carga de destino de la transicion.
							entrada=true;
							while(entrada){
								printf("Cargue Transicion ('_'=vacio): (%s , %c)->", state, Alpha[iAl]);
								intoDelta(in,States);
								if( strstr(destinations, in)==NULL ){
									strcat(in, ":");
									strcat(destinations, in);	
								}else{
									printf("Error. Ya existe esa transicion! Cargue una nueva...\n");
								}
								printf("\t\tContinuar carga? S/N: ");
								if( !option() ){
									destinations[strlen(destinations+1)] = ';';
									entrada = false	;
								}
							}
							strcat(delta, origin);
							strcat(delta, destinations);
						}
					}//For del alfabeto.
				}
				init = iSt+1;
			}
		}//For de los estados.
		printf("\n¿Son sus Transiciones? S={ %s } -> S/N: ", delta);
	}while( !option() );
	strcpy(DeltaFunction, delta);
}//Funciona.

//Realizar.
void menu(){
	
	printf("\nFUNCIONES:");
	printf("\n\n\t 1-Ingresar cadena para evaluar AF");
	printf("\n\t 2-Mostrar el Automata Finito");
	printf("\n\t 3-Convertir AFND a AFD");
	printf("\n\t 4-Mostrar el Automata Finito Determinista Convertido");
	printf("\n\t 5-Ingresar cadena para evaluar AFD equivalente");
	printf("\n\t 6-Salir");
	
}
