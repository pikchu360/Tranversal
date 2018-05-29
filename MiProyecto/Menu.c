#include "Menu.h"
#include "AutomataFinito.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void intro(char* Aux){
	fflush(stdin);
	gets(Aux);
	strcat(Aux,";");
};

void MenuState(char* ReturnStates){	
	// Load States 
	int Salida=1;
	char States[100];
	char Flag = 'S';
	do{				
		char Aux[5];
		int entrada = 0;
		printf ("\nCargue su estado inicial:   ");
		intro(States);
		while (entrada == 0){
			printf("\nCarge otro Estados de Su Automata:  ");
			intro(Aux);
			if (strstr(States,Aux)== NULL ){
				strcat(States,Aux);
				printf("\nDesea cargar otro Estado  Si/No:  ");
				fflush(stdin);
				Flag = getchar();
				if((Flag == 'n') || (Flag== 'N') ){
					entrada = 1	;
					strcat(States,"_;.");}
			}
		}		
		printf("Estos son sus Estados S/N: %s", States);
		Flag = 'S';
		fflush(stdin);
		Flag = getchar();
		if((Flag == 's') || (Flag == 'S'))
			Salida = 0;
		
	}while (Salida != 0);	
	strcpy(ReturnStates,States);
}

void MenuAlpha(char* Alpha){	
	// Load Alpha
	char Flag = '0';
	char Symbol[100];
	memset(Symbol,'\0',strlen(Symbol));
	char Aux[5];
	char Aux2[5];
	int entrada = 0;
	
	
	printf ("\nCargue su primer simbolo del alfabeto:   ");
	do {
		fflush(stdin);	
		intro(Aux);
		
		if (strlen(Aux) > 2){
			printf("\nUsaremos el primer Simbolo de la cadena que ingreso: %c ", Aux[0] );
			
		}	
		Symbol[0]=Aux[0];
		strcat(Symbol,";");
		while (entrada == 0){
			printf("\nCarge otro Simbolo:  ");
			memset(Aux,'\0',strlen(Aux));
			fflush(stdin);
			intro(Aux);
			if (strlen(Aux) > 2) {
				memset(Aux2,'\0',strlen(Aux2));
				Aux2[0]=Aux[0];
			}
			if (strstr(Symbol,Aux2)== NULL ){
				strcat(Symbol,Aux2);
				strcat(Symbol,";");
				printf("\nDesea cargar otro Simbolo  Si/No:  ");
				fflush(stdin);
				Flag = getchar();
				if((Flag == 'n') || (Flag== 'N') ){
					entrada = 1	;
					strcat(Symbol,".");}
			}else {printf("el simbolo  '%s' ya esta en su alfabeto", Aux2);}
		}
	}while(entrada = 0);
	
	strcpy(Alpha,Symbol);
}

void MenuFinish(char* States,char* FStates){ //Load Final State
	char FinalState[100];
	int Salida=1;
	char Flag = 'S';
	do{		
		char Aux[5];
		int entrada = 0;
		while (entrada == 0){
			printf("\nCarge un Estado final:  ");
			intro(Aux);
			if (strstr(States,Aux)== NULL ){
				printf("\nEl estado %s No se encuentra declarado",Aux);
				
			}else{
				strcat(FinalState,Aux);
				printf("\nDesea cargar otro Estado de Aceptacion  (Si/No):    ");
				fflush(stdin);
				Flag = getchar();
				if((Flag == 'n') || (Flag== 'N') ){
					entrada = 1	;
					strcat(FinalState,".");
				}
			}
		}
		
		printf("Estos son sus Estados S/N: %s", FinalState);
		Flag = 'S';
		fflush(stdin);
		Flag = getchar();
		if((Flag == 's') || (Flag == 'S'))
			Salida = 0;
	}while (Salida != 0);		
	strcpy(FStates,FinalState);	
}

void  MenuDelta(char* States, char* Alpha, char* DeltaFunction ){//load function Delta
	
	char TransitionDelta[1000];
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
						printf ("\nCargue una transicion de Delta para (%s , %c) (el vacio es '_' ):   ", AuxS,AuxA[j]);	
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
									printf("\nDesea cargar otra Transicion para %s , %c  (Si/No):  " , AuxS,AuxA[j]);
									fflush(stdin);
									Flag = getchar();
									if((Flag == 'n') || (Flag== 'N') ){
										Salida = 0;										
									}else {Salida = 1;}
									Salida2= 0;
									
								}else {
										fflush(stdout);
										printf ("\nLa Transicion ya existe  ");
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
	strcpy(DeltaFunction,TransitionDelta);
}

