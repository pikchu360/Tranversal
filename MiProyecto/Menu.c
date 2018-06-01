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
	//printf("\nContinuar carga? S/n: ");
	do{
		fflush(stdin);
		gets(opt);
		if ( opt[0]=='s' || opt[0]=='S') {
			return true;
		}
		else if (opt[0] == 'n' || opt[0]=='N')
		{
			return false;
		}else {
			printf("\tError. Ingrese 's' o 'n': ");
			memset(&opt, '\0',strlen(opt));
		}
		fflush(stdin);
	}while(opt[0]!='s' && opt[0]!='S' && opt[0]!='n' && opt[0]!='N' );
}//Funciona.

void intro(char* Aux){
	fflush(stdin);
	gets(Aux);
	strcat(Aux,";");
}
void intoDelta(char* str, char *states){
	bool flag=true;
	do{
		memset(&str, '\0', strlen(str));
		gets(str);
		fflush(stdin);
		flag=true;
		if(strstr(states,str)==NULL){
			printf("Error. Ingrese estado valido: ");
		}else{
			flag = false;
		}
	} while (flag);
}

//Retorna una cadena modificada.
void MenuState(char* ReturnStates){	
	// Load States 
	int Salida=1;
	char States[100];
	do{				
		char Aux[5];
		int entrada = 0;
		printf ("\nCargue el estado inicial: ");
		intro(States);
		while (entrada == 0){
			printf("Carge nuevo estado:  ");
			intro(Aux);
			if (strstr(States,Aux) == NULL ){
				strcat(States,Aux);
				printf("\t\tContinuar carga? S/N:  ");
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

void MenuAlpha(char* Alpha){	
	int salida;
	char Symbol[100];
	memset(&Symbol,'\0', strlen(Symbol));	
	do{
		char Aux[5];
		int entrada = 0;
		while (entrada == 0){
			printf("Cargue simbolo de su AF: ");
			intro(Aux);
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
		}
		fflush(stdin);		
		printf("\t¿Este es su Alfabeto? Alphabet={ %s } -> S/N: ", Symbol);
	} while ( !option() );
	strcat(Symbol, ".");
	strcpy(Alpha,Symbol);
}//Funciona.

void MenuFinish(char* FStates, char* States){ //Load Final State
	char FinalState[100];
	int Salida=1;
	do{		
		char Aux[5];
		int entrada = 0;
		while (entrada == 0){
			printf("Nuevo estado final: ");
			intro(Aux);
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
		fflush(stdin);
		printf("\t¿Son sus Estados de Aceptacion? F={ %s } -> S/N: ", FinalState);
	}while ( !option() );
	strcat(FinalState,".");		
	strcpy(FStates,FinalState);	
}//Funciona.

void MenuDelta(char* DeltaFunction ,char* States, char* Alpha){//load function Delta
	char delta[1000], origin[50], destinations[50], state[20], in[10];
	bool entrada;
	int init = 0;
	memset(&delta ,'\0',strlen(delta));		
	
	do{
		for(int iSt = 0; iSt < strlen(States); iSt++){
			//Veo si completo un estado.
			if(States[iSt]==';'){
				copyChais(&state, States, init, iSt);		//obtengo 1 estado.
				
				//Analizo el estado con cada simbolo del alfabeto.
				for(int iAl = 0; iAl < strlen(Alpha); iAl++){
					//Veo si compleeto el alfabeto.
					if( Alpha[iAl]!=';' && Alpha[iAl]!='.'){
						memset(&origin ,'\0',strlen(origin));
						memset(&destinations ,'\0',strlen(destinations));
						//Armado de el punto de partida. Ej (q0:a).
						strcat(origin, state);
						strcat(origin, ":");
						strcat(origin, ""+Alpha[iAl]);		//Forma de casting para charToString
						strcat(origin, "->");
						
						//Ciclo de carga de destino de la transicion.
						entrada=true;
						while(entrada){
							memset(&in, '\0', strlen(in));
							printf("Cargue Transicion ('_'=vacio): (%s , %c)->", state, Alpha[iAl]);
							intoDelta(in,States);
							if( strstr(destinations, in)==NULL && strlen(state)==strlen(in)){
								strcat(destinations, in);
								strcat(destinations, ":");
							}else{
								printf("Error. Ya existe esa transicion! Cargue una nueva...\n");
							}
							printf("\t\tContinuar carga? S/N: ");
							if( !option() ){
								entrada = false	;
							}
						}
					}
				}//For del alfabeto.
			}
		}//For de los estados.
		printf("\t¿Son sus Transiciones? S={ %s } -> S/N: ", delta);
	}while( !option() );
	
	//strcpy(DeltaFunction,delta);
	/*char TransitionDelta[1000];
	int Salida=1;
	int Salida2=1;		
	char Flag = 'S';
	int i=0;
	while ( i<strlen(States)){
	int k = i;
	char AuxS[10];
	
	int IniAux=0;
	memset(AuxS,'\0',strlen(AuxS));
	while ( k<strlen(States)){
	if ((States[k] != ';') && (States[k] != '.') && (States[k] != '\n') && (States[k] != '_')){				
	fflush(stdin);
	AuxS[IniAux]=States[k];
	k++;
	IniAux++;
	}else {
	i=k;
	k=strlen(States)+1;
	}		
	}
	if (strlen(AuxS) != 0){
	
	for (int j=0; j<strlen(Alpha); j++){
	if ((Alpha[j] != ';') && (Alpha[j] != '.') && (Alpha[j] != '\n')){
	char AuxA[10];
	char AuxTransition[20];
	AuxA[j]=Alpha[j];
	do{						
	char Aux[10];
	fflush(stdout);
	printf ("\nCargue transicion ('_'=vacio): (%s , %c) -> ", AuxS,AuxA[j]);	
	fflush(stdin);
	
	do{
	memset(AuxTransition,'\0',strlen(AuxTransition));
	strcat(AuxTransition, AuxS);
	strcat(AuxTransition,",");						
	AuxTransition[strlen(AuxTransition)]=AuxA[j];
	strcat(AuxTransition,"->");							
	intro(Aux);
	
	if (strstr(States,Aux)!= NULL ){ // cargar transicion a Vacio _ usar guion bajo
	strcat(AuxTransition,Aux);
	if (strstr(TransitionDelta,AuxTransition)== NULL){
	strcat(TransitionDelta,AuxTransition);
	printf("\nNueva Transicion para (%s , %c) ?  (Si/No):  " , AuxS,AuxA[j]);
	fflush(stdin);
	Flag = getchar();
	if((Flag == 'n') || (Flag== 'N') ){
	Salida = 0;										
	}else {Salida = 1;}
	Salida2= 0;
	
	}else {
	fflush(stdout);
	printf ("\nError. La Transicion ya existe!!  ");
	Salida2 = 1;	
	}
	}else {
	fflush(stdout);
	printf ("\nCargue un estado valido:   ");
	Salida2 = 1;
	}
	}while(Salida2 != 0);
	
	}while (Salida != 0);			
	}
	}
	}
	
	i++;
	}
	strcat(TransitionDelta,".");
	strcpy(DeltaFunction,TransitionDelta);*/
}

