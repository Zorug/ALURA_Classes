#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void) {
	
	int i = 0, j = 0, k = 0, l = 0,///para teste
		B;///Variaveis de salvar temporária
	float A;///Variavel de salvar temporária
		
	int linhasPontoDat = 7550,///Input Lines; linhasPontoDat=0/1 é o título
		linhasExibidas = 1000;///Linhas exibidas na saída
	
	int nCaractStringEntrada = 150,///input size
		caracteresPorPontoMatricial = 50;///caracteres da matriz, 50
	
	int nColunasMatriz = 16;///colunas da matriz
	
	int contadorN = 0, contadorZ = 0, contadorY = 0;
	
	int SeqMod[linhasPontoDat];///esta é a matriz com a sequência numérica modificada
	
	char linhaGet[linhasPontoDat][nCaractStringEntrada];///input phrase; linhasPontoDat=0/1 é o título
	char matrizCaract[linhasPontoDat][nColunasMatriz][caracteresPorPontoMatricial];///Matriz de caracteres; linhasPontoDat=0/1 é o título
	
	float matrizFloat[linhasPontoDat][nColunasMatriz];///tabela convertida em float
	
	float BoostMin$ = 0.1, BoostMax$ = 1,///range de preços de Boosters
		  BoostMinPerc = 0,BoostMaxPerc = 75,///range de percentual dos Boosters
		  CardAvgMax = 1,///valor máximo da média (ajuda a liquidar as médias tirando cartas extrapoladas)
		  AvgQty = 80;///quantidade de trocas disponíveis
	
	FILE *dat;
	
	dat = fopen("dados.dat", "r");


	/*******************Aqui limpa as memórias do linhaGet***************/
	
	for(k = 0; k < nCaractStringEntrada; k++) {
		
		for(l = 0; l < linhasPontoDat; l++) {
			
			linhaGet[l][k] = 0;
		}
	}


	/***************importação das linhas do arquivo*******************/
	
	k = 0;
	while(!feof(dat)) {
		
		fgets(linhaGet[k], nCaractStringEntrada,dat);
		k++;
	}
	
	linhasPontoDat = k - 2;
	
	
	/*******************Aqui limpa as memória matrizCaract******************/
	
	//printf("      %s <+>    \t%s\t%s\t%s          %s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	//printf("%s", linhaGet[0]);
	//printf("%s", linhaGet[0]);
	
	for(j = 0; j < linhasPontoDat; j++) {
		
		for(k = 0; k < caracteresPorPontoMatricial; k++) {
			
			for(l = 0; l < nColunasMatriz; l++) {
				
				matrizCaract[j][l][k] = 0;
				//printf("%s", linhaGet[0]);
			}
			//printf("%s", linhaGet[0]);
		}
		//printf("%s", linhaGet[0]);
	}
	printf("%s", linhaGet[0]);
	printf("%s", linhaGet[1]);
	//printf("      %s <+>    \t%s\t%s\t%s          %s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	//printf("%s", linhaGet[0]);
		
	/******************Aqui separa em colunas em matrizCaract***************/
	
	for(j = 0; j < linhasPontoDat; j++) {
		
		while(linhaGet[j][contadorN] != '\n') {
			
			if(linhaGet[j][contadorN] == '\t') {
				
				contadorZ = 0;
				contadorY++;
			}
			else {
				
				matrizCaract[j][contadorY][contadorZ] = linhaGet[j][contadorN];
				contadorZ++;
				}
				
			contadorN++;
		}
		
		contadorN = 0;
		contadorZ = 0;
		contadorY = 0;
	}	
	
	//printf("      %s <+>    \t%s\t%s\t%s          %s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	//printf("%s\t%s\t%s\t%s%s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	
	/**********************************
	1. Coluna k=1a15: alterar ',' por '.'
	2. Coluna k=8: N/A vira 0.0
	3. Coluna k=14 datas
	***********************************/
	
	/************************1.Troca virgula e ponto*******************/
	
	for(j = 1; j < linhasPontoDat; j++) {
		
		for(k = 1; k < nColunasMatriz; k++) {
			
			for(l = 0; l < caracteresPorPontoMatricial; l++) {
				
				if(matrizCaract[j][k][l] == ',') {
					
					matrizCaract[j][k][l] = '.';
				}
			}
		}
	}
		
		
	/***********************2.Coluna 8 vira 0.0************************/
	
	for(j = 1; j < linhasPontoDat; j++) {
		
		for(l = 0; l < caracteresPorPontoMatricial; l++) {
			
			if((matrizCaract[j][8][l] == 'A') && (matrizCaract[j][8][l - 1] == '/') && (matrizCaract[j][8][l - 2] == 'N')) {
				
				matrizCaract[j][8][l] = '0';
				matrizCaract[j][8][l - 1] = '.';
				matrizCaract[j][8][l - 2] = '0';
			}
		}
	}
	
	
	/**********************3.Coluna de datas, 14***********************/
	
	for(j = 1; j < linhasPontoDat; j++){
		
		for(l = 0; l < caracteresPorPontoMatricial; l++) {
			
			if((matrizCaract[j][14][l] == '-') && (matrizCaract[j][14][l - 3] == '-')) {
				
				matrizCaract[j][14][l] = '#';
				matrizCaract[j][14][l - 3] = matrizCaract[j][14][l - 2];
				matrizCaract[j][14][l - 2] = matrizCaract[j][14][l - 1];
				matrizCaract[j][14][l - 1] = matrizCaract[j][14][l + 1];
				matrizCaract[j][14][l] = matrizCaract[j][14][l + 2];
				matrizCaract[j][14][l + 1] = '.';
				matrizCaract[j][14][l + 2] = '0';
			}
		}
	}	
	
	
	/*************Imprimir somente as colunas individualmente**********/
	
	/*k = 9;
	//printf("\n   **%s**\n\n", matrizCaract[0][k]);
	for(j = 0; j < linhasExibidas; j++) {
	* 
		printf("%i   **%s**%s**\n", j, matrizCaract[j][0], matrizCaract[j][15]);
	}*/
	
	
	/***************imprimir as colunas e linhas***********************/
	
	/*for(j = 0;j < linhasExibidas; j++) {
		
		printf("%i.", j + 1);
		for(k = 0; k < nColunasMatriz; k++) {
		
			printf("%s  ", matrizCaract[j][k]);
		}
		
		printf("\n\n");
	}*/
	
	
	/******************Transformar em float****************************/
	
	for(j = 0; j <= linhasPontoDat; j++) {
		
		for(l = 0;l < nColunasMatriz; l++){
			
			matrizFloat[j][l] = atof(matrizCaract[j][l]);
		}
	}
	
	
	/********Lista os primeiros da col9 e bota alterna no mínimo*******/
	
	l = 9;//coluna de interesse
	
	//linhasExibidas = 15;//Linhas exibidas na saída
	/*printf("\n\t%s\n\n", matrizCaract[0][l]);//título
	for(i = 1; i < linhasExibidas; i++) {
	
		printf("\t%.2f\n", matrizFloat[i][l]);
	}
	//arrumar sequência maior menor começa no + e vai pro negativo.
	printf("\n");*/
	
	
	/****************Organização do maior para o menor*****************/
	
	for(i = 0; i <= linhasPontoDat; i++) {//botar em sequência numérica da matriz que guardará a nova sequêcia
		
		SeqMod[i] = i;
		//printf("\tSeqMod<%i>=%i\t%.2f\n", i, SeqMod[i], matrizFloat[i][9]);
	}
	
	printf("\n");
	j = 1;//desconsiderando j=0 por ser titulo
	while(j != (2 * linhasPontoDat)) {//reorganiza as posições
		
		for(i = 2; i <= (linhasPontoDat - 1); i++) {
			
			if(matrizFloat[i][9] > matrizFloat[i - 1][9]) {
				
				A = matrizFloat[i][9];///acaba por alterar a sequência original de %booster
				B = SeqMod[i];///altera a sequência de acordo com essa organização, acompanhando a alteração dos matrizFloat
				matrizFloat[i][9] = matrizFloat[i - 1][9];
				SeqMod[i] = SeqMod[i - 1];
				matrizFloat[i - 1][9] = A;
				SeqMod[i - 1] = B;
			}
			else if(matrizFloat[i][9] > matrizFloat[i + 1][9]) {
				A = matrizFloat[i][9];
				B = SeqMod[i];
				matrizFloat[i][9] = matrizFloat[i + 1][9];
				SeqMod[i] = SeqMod[i + 1];
				matrizFloat[i + 1][9] = A;
				SeqMod[i + 1] = B;
			}
		}
		j++;
	}
	
	
	/**################################################################**/
	/**################## Filtro Booster Avg: entre ###################**/
	/**################################################################**/
	
	
	/*******Imprime em ordem de %, não esquecer que é SeqMod[i]********/
	
	//printf("%s\t%s\t%s\t%s%s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	//printf("      %s <+>    \t%s\t%s\t%s          %s\n\n", matrizCaract[0][9], matrizCaract[0][8], matrizCaract[0][7], matrizCaract[0][12], matrizCaract[0][0]);
	printf("      Booster %     \tBooster Avg\tCard Avg\tAvg Qty          Game\n\n");
	//BoostMin%=0,BoostMax%=100;							//Booster %			Booster Avg			Card Avg				Avg Qty				Game
	for(i = 1; i < linhasExibidas; i++) {
		
		if((matrizFloat[SeqMod[i]][8] > BoostMin$) && (matrizFloat[SeqMod[i]][8] < BoostMax$)) {///filtro de BoosterAvg|8
			
			if((matrizFloat[i][9] > BoostMinPerc) && (matrizFloat[i][9] <= BoostMaxPerc)) {///filtro de Booster%|9
				
				if(matrizFloat[SeqMod[i]][7] <= CardAvgMax) {///filtro do card avg
					
					if(matrizFloat[SeqMod[i]][12] >= AvgQty) {
						
						printf("\t%.2f\t\t   %.2f\t\t  %.2f\t\t  %.0f\t      %s\n",	
							matrizFloat[i][9], matrizFloat[SeqMod[i]][8], matrizFloat[SeqMod[i]][7],//em vez de i, colocar SeqMod[i] 
							matrizFloat[SeqMod[i]][12], matrizCaract[SeqMod[i]][0]);
					}
				}
			}
		}
	}
	
	fclose(dat);
	
	
	}
