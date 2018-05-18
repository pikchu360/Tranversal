#include <stdio.h>


int main(){
	char States[100] = "q0;q1;q2;\n";
	char Alpha[100]= "0;1;2;\n";
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
/*			strcpy(AuxS,AuxStates[i]);*/
			strcat(AuxS2,AuxS);
		
			if (i==0){
				while(j<Aini){
					char AuxA[10];
					char AuxA2[10];
					while (AuxAlpha[i] != ';'){
/*						strcpy(AuxA,AuxAlpha[i]);*/
						strcat(AuxA2,AuxA);
					
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
	}	
	/*char p1[]="hola mami";
	char p2[]="hola mamila";
	int i;
	printf("\nLos caracteres de la palabra %s son:\n\n",p1);
	for (i=0; i<strlen(p1); i++) {
		printf("%3d %c\n", (unsigned char)p1[i], p1[i]);
	}
	printf("\nLos caracteres de la palabra %s son:\n\n",p2);
	for (i=0; i<strlen(p2); i++) {
		printf("%3d %c\n", (unsigned char)p2[i], p2[i]);
	}
	printf("\n");
	*/
	return 0;
}
