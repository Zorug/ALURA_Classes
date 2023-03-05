/*Agora salvar a ordem*/
#include <stdio.h>
#include <stdlib.h>
#include "CFire.h"

//#define TAMANHO_STRING_CSV 180
//#define QNT_LINHAS_CSV 8000
//#define COLUNAS_MATRIZ 16
//#define STRING_MATRIZ 45

char strings_csv[QNT_LINHAS_CSV][TAMANHO_STRING_CSV];//caracteres do csv
char strings_matriz[QNT_LINHAS_CSV][COLUNAS_MATRIZ][STRING_MATRIZ];//matriz de caracteres organizada
float floats_matriz[QNT_LINHAS_CSV][COLUNAS_MATRIZ];//matriz de caracteres convertida

float coluna_de_armazenagem_hard[QNT_LINHAS_CSV];//aqui ficarão guardados valores em nova ordem
float coluna_de_armazenagem_floppy[QNT_LINHAS_CSV];//aqui ficarão guardados valores em nova ordem

int coluna_ordem_original[QNT_LINHAS_CSV]; //sequência inicial de ordem crescente i++
int coluna_nova_ordem[QNT_LINHAS_CSV];//mesmo esquema do armazenagem
int coluna_nova_ordem_floppy[QNT_LINHAS_CSV];

int linhas_csv = 0; //linha zero é o cabeçalho
int coluna_selecionada;

float filtro_de_impressao[COLUNAS_MATRIZ][3];//0 verifica se é ativado, 1 é minimo e 2 é máximo.

void importa_do_arquivo() {//também limpa filtro
  FILE* f;

  f = fopen("STC_set_data.csv", "r");
  if(f == 0) {
		printf("Desculpe, banco de dados não disponível\n\n");
		exit(1);
	}

  while(!feof(f)) {//verificar o número de linhas e as guarda
    fgets(strings_csv[linhas_csv], TAMANHO_STRING_CSV, f);
    linhas_csv++;
  }
  linhas_csv--;//ele acaba somando uma a mais no final

  //printf("%d\n\n", linhas_csv);

  fclose(f);

  for(int i = 0; i < COLUNAS_MATRIZ; i++) {//limpa a matriz filtro
    filtro_de_impressao[i][0] = 0;
    filtro_de_impressao[i][1] = 0;
    filtro_de_impressao[i][2] = 0;
  }
}

void organiza_matriz_string() {

  for(int j = 0; j <= linhas_csv; j++) {

    int virgulas = 1;//utilizado para separar as COLUNAS_MATRIZ

    int jump_coluna = 0;
    int jump_linha = 0;

    for(int i = 0; i <= TAMANHO_STRING_CSV; i++) {//filtra as strings do arquivo

      if((strings_csv[j][i] == ',') && (strings_csv[j][i-1] == '\"')) {//remove o problema com vírgulas perdidas
        virgulas++;

        strings_matriz[j][jump_coluna][jump_linha] = '\0';
        jump_coluna++;//pula para a próxima coluna
        jump_linha = 0;//reinicia o número da linha
        continue;

      } else if(strings_csv[j][i] == '\"') {
        continue;

      } else if((strings_csv[j][i] == -17) || (strings_csv[j][i] == -69) || (strings_csv[j][i] == -65)) {//erro de primeira linha
        continue;

      } else if((strings_csv[j][i] == '\n') || (strings_csv[j][i] == '\0')) {//erro de ultima linha, não tem /n
        strings_matriz[j][jump_coluna][jump_linha] = '\0';
        break;
      }

      strings_matriz[j][jump_coluna][jump_linha] = strings_csv[j][i];
      jump_linha++;
    }
  }
}

void interface() {

  printf("\nBem vindo ao STEAM TRADING CARD CLASSIFIER. ");
  printf("O programa tem o objetivo de organizar as cartas de forma a agregar valor no Steam.\n\n");
  /*printf("Temos as seguintes categorias:\n\n");
  for(int i = 0; i < COLUNAS_MATRIZ; i++) {
    printf("\t|%d.%s|", i, strings_matriz[0][i]);
    if(((i+1) % 8) == 0) printf("\n\n");
  }*/
  //printf("\n\n");

  printf("Podemos ordenar as seguintes categorias do maior para o menor: ");
  printf("\n\n\t|13.%s|   |12.%s|   |9.%s|   |8.%s|   |7.%s|   |6.%s|   |5.%s|\n\n",
        strings_matriz[0][13], strings_matriz[0][12],
        strings_matriz[0][9], strings_matriz[0][8],
        strings_matriz[0][7], strings_matriz[0][6], strings_matriz[0][5]);

  printf("\nQual categoria deseja ordenar? ");
  /******filtra a entrada nessa etapa. quem sabe resolver depois******/
  scanf("%d",&coluna_selecionada);
}

void troca_letra_por_numero() {
  for(int i = 1; i <= linhas_csv; i++) {
    if(strings_matriz[i][8][0] == 'N') sprintf(strings_matriz[i][8], "-33.33");//troca N/a da coluna 8
  }
}

void transforma_string_em_float() {

  for(int i = 1; i <= linhas_csv; i++) {
    //floats_matriz[i][3] = atof(strings_matriz[i][3]);//# Cards

    floats_matriz[i][5] = atof(strings_matriz[i][5]);//Set Price
    floats_matriz[i][6] = atof(strings_matriz[i][6]);//Price diff
    floats_matriz[i][7] = atof(strings_matriz[i][7]);//Card Avg
    floats_matriz[i][8] = atof(strings_matriz[i][8]);//Booster Avg
    floats_matriz[i][9] = atof(strings_matriz[i][9]);//Booster %

    floats_matriz[i][12] = atof(strings_matriz[i][12]);//Avg Qty
    floats_matriz[i][13] = atof(strings_matriz[i][13]);//Discount

    coluna_de_armazenagem_hard[i] = -99999999;//aqui apenas limpa a matriz
    coluna_de_armazenagem_floppy[i] = -99999999;//aqui apenas limpa a matriz

    coluna_ordem_original[i] = i;//preenche com a sequência que será alterada depois
    coluna_nova_ordem[i] = -10;//mesmo esquema do armazenagem
    coluna_nova_ordem_floppy[i] = -10;
  }
}

void ordena_coluna() {

  //int coluna_selecionada = 9;
  int achou = 0;
  int max_lin = linhas_csv;
  //int max_lin = 35;

  for(int i = 1; i <= max_lin; i++) {
    for(int j = 1; j <= max_lin; j++){

      if(floats_matriz[i][coluna_selecionada] > coluna_de_armazenagem_hard[j]) {

        for(int k = j; k <= max_lin; k++) {

          coluna_de_armazenagem_floppy[k+1] = coluna_de_armazenagem_hard[k];//a partir da posição j todos os floppy[j+1] = todos hard[j]
          coluna_nova_ordem_floppy[k+1] = coluna_nova_ordem[k];//mesmo esquema, só que para guardar a sequência numérica
        }

        coluna_de_armazenagem_floppy[j] = floats_matriz[i][coluna_selecionada];//floppy[j] = floats_matriz[9][i]
        coluna_nova_ordem_floppy[j] = coluna_ordem_original[i];//mesma coisa, só que com números

        for(int k = j; k <= max_lin; k++) {

          coluna_de_armazenagem_hard[k] = coluna_de_armazenagem_floppy[k];//todos os hard[j] = todos os float[j]
          coluna_nova_ordem[k] = coluna_nova_ordem_floppy[k];//same here
        }
        break;
      }
    }
  }
}

void imprime_coluna() {

  int linhas_impressas = 35;

  /*printf("\tMATRIZ\t\tARMAZENAGEM\tORDEM\n\n");
  for(int i = 1; i <= linhas_impressas; i++) {
    printf("%d.\t%f\t%f\t%d\n", i, floats_matriz[i][9], coluna_de_armazenagem_hard[i],coluna_nova_ordem[i]);
  }*/

  //printf("%s   %s   %s    %s\n", strings_matriz[0][A], strings_matriz[0][B], strings_matriz[0][C], strings_matriz[0][D]);//título
  printf("\n\n|  13.%s\t|   12.%s\t|  9.%s\t| 8.%s\t|  7.%s\t| 6.%s\t|  5.%s\t|\t\t0.%s\n\n",
      strings_matriz[0][13], strings_matriz[0][12],
      strings_matriz[0][9], strings_matriz[0][8],
      strings_matriz[0][7], strings_matriz[0][6], strings_matriz[0][5],
      strings_matriz[0][0]);

  for(int i = 1; i <= linhas_impressas; i++) {
    //printf("%d.    %s\t      %s\t\t%s\t%s\n", i, strings_matriz[i][A], strings_matriz[i][B], strings_matriz[i][C], strings_matriz[i][D]);

    if(filtro_de_impressao[13][0] != 0){// 13.Disconto
      if((floats_matriz[coluna_nova_ordem[i]][13] < filtro_de_impressao[13][1]) || (floats_matriz[coluna_nova_ordem[i]][13] > filtro_de_impressao[13][2])) {
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[12][0] != 0){// 12.Avg Qty
      if((floats_matriz[coluna_nova_ordem[i]][12] < filtro_de_impressao[12][1]) || (floats_matriz[coluna_nova_ordem[i]][12] > filtro_de_impressao[12][2])) {
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[9][0] != 0){// 9.Booster Perc
      if((floats_matriz[coluna_nova_ordem[i]][9] < filtro_de_impressao[9][1]) || (floats_matriz[coluna_nova_ordem[i]][9] > filtro_de_impressao[9][2])) {
        //acontece se for menor que 1 ou maior que 5
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[8][0] != 0){// 8.Booster Avg
      if((floats_matriz[coluna_nova_ordem[i]][8] < filtro_de_impressao[8][1]) || (floats_matriz[coluna_nova_ordem[i]][8] > filtro_de_impressao[8][2])) {
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[7][0] != 0){// 7.Card Avg
      if((floats_matriz[coluna_nova_ordem[i]][7] < filtro_de_impressao[7][1]) || (floats_matriz[coluna_nova_ordem[i]][7] > filtro_de_impressao[7][2])) {
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[6][0] != 0){// 6.Price diff
      if((floats_matriz[coluna_nova_ordem[i]][6] < filtro_de_impressao[6][1]) || (floats_matriz[coluna_nova_ordem[i]][6] > filtro_de_impressao[6][2])) {
        linhas_impressas++;
        continue;
      }
    }
    if(filtro_de_impressao[5][0] != 0){// 5.Set Price
      if((floats_matriz[coluna_nova_ordem[i]][5] < filtro_de_impressao[5][1]) || (floats_matriz[coluna_nova_ordem[i]][5] > filtro_de_impressao[5][2])) {
        linhas_impressas++;
        continue;
      }
    }
    /*if(filtro_de_impressao[3][0] != 0){// 3.# Cards
      if((floats_matriz[coluna_nova_ordem[i]][3] < filtro_de_impressao[3][1]) || (floats_matriz[coluna_nova_ordem[i]][3] > filtro_de_impressao[3][2])) {
        linhas_impressas++;
        continue;
      }
    }*/

    printf("|\t%.2f\t|\t%.0f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%.2f\t|\t%d.\t%.45s\n",
        floats_matriz[coluna_nova_ordem[i]][13], floats_matriz[coluna_nova_ordem[i]][12],
        floats_matriz[coluna_nova_ordem[i]][9], floats_matriz[coluna_nova_ordem[i]][8],
        floats_matriz[coluna_nova_ordem[i]][7], floats_matriz[coluna_nova_ordem[i]][6], floats_matriz[coluna_nova_ordem[i]][5],
        coluna_nova_ordem[i], strings_matriz[coluna_nova_ordem[i]][0]);
  }
  printf("\n");

  /*int filtrar = 0;
  printf("Deseja aplicar um filtro? 1.Sim\n");
  scanf("%d", &filtrar);
  if(filtrar == 1)*/ filtra_coluna();

}

void filtra_coluna() { // aqui filtramos alguns dos dados de acordo com o usuário.

  int numero;

  printf("Escolha uma coluna para filtrar: \n");
  scanf("%d", &numero);
  filtro_de_impressao[numero][0] = numero;
  printf("defina uma valor mínimo para o filtro: ");
  scanf("%f",&filtro_de_impressao[numero][1]);
  printf("\nagora defina um valor máximo para o filtro: ");
  scanf("%f",&filtro_de_impressao[numero][2]);

  imprime_coluna();
    //printf("(1. Apagar os valores médios de Booster nulos)");


}

int main() {

  importa_do_arquivo();

  organiza_matriz_string();

  interface();

  troca_letra_por_numero();

  transforma_string_em_float();

  ordena_coluna();

  imprime_coluna();

  //filtra_coluna();
}
