#include "MENU.h"
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
	
void MenuState(){	
	// Load States 
	int Salida=1;
	char Flag = 'S';
	do{		
		char States[100];
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
					strcat(States,"\n");}
			}
		}		
		printf("Estos son sus Estados S/N: %s", States);
		Flag = 'S';
		fflush(stdin);
		Flag = getchar();
		if((Flag == 's') || (Flag == 'S'))
			Salida = 0;
		
	}while (Salida != 0);	
	}

void MenuAlpha(){	
	// Load Alpha
	
	char Flag = '0';
	char Symbol[100];
	char Aux[5];
	int entrada = 0;
	printf ("\nCargue su primer simbolo del alfabeto:   ");
	intro(Symbol);
	while (entrada == 0){
		printf("\nCarge otro Simbolo:  ");
		intro(Aux);
		if (strstr(Symbol,Aux)== NULL ){
			strcat(Symbol,Aux);
			printf("\nDesea cargar otro Simbolo  Si/No:  ");
			fflush(stdin);
			Flag = getchar();
			if((Flag == 'n') || (Flag== 'N') ){
				entrada = 1	;
				strcat(Symbol,"\n");}
		}
	}
}
void MenuFinish(char* States){ //Load Final State
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
					strcat(FinalState,"\n");
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
		
	}
	
void estado(char* entrada){
		
	
}
void MenuLambda(char* States, char* Alpha){
	char TransitionLambda[1000];
	char AuxStates[100];
	strcpy(AuxStates,States);
	char AuxAlpha[100];
	strcpy(AuxAlpha,Alpha);
	int Salida=1;
	int Sini = strlen(States);
	int Aini = strlen(Alpha);
	char Flag = 'S';
	int i=0;
	
	while ( i< Sini ){
		char AuxS[10];
		char AuxS2[10];
		int j=0;
		while (AuxStates[i] != ';'){
			strcpy(AuxS,AuxStates[i]);
			strcat(AuxS2,AuxS);
		}
		if (i==0){
		while(j<Aini){
			char AuxA[10];
			char AuxA2[10];
			while (AuxAlpha[i] != ';'){
				strcpy(AuxA,AuxAlpha[i]);
				strcat(AuxA2,AuxA);
			}
			do{		
				
				char Aux[5];
				int entrada = 0;
				printf ("\nCargue una transicion de %s , %s :   ", AuxS2,AuxA2);
				strcat(TransitionLambda, AuxS2);
				strcat(TransitionLambda, ';');
				strcat(TransitionLambda, AuxA2);
				strcat(TransitionLambda, ';');
				intro(Aux);
					if (strstr(States,Aux)!= NULL ){
						strcat(TransitionLambda,Aux);
						printf("\nDesea cargar otra Transicion para %s , %s  (Si/No):  " , AuxS2,AuxA2);
						fflush(stdin);
						Flag = getchar();
						if((Flag == 'n') || (Flag== 'N') ){
							Salida = 1;
							strcat(States,"\n");}
						else Salida = 0;
					}
				
					
				
			}while (Salida != 0);	
			
			
			j++;
		}
		}
		i++;
	}	
	
}

