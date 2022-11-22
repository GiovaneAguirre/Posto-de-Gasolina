#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#define C_RED       "\033[31m"
#define C_GREEN     "\033[32m"
#define C_YELLOW    "\033[33m"
#define C_BLUE      "\033[34m"
#define NONE        "\033[0m"

struct Tcarro {
  char modelo[20];
  char cor[10];
  int ano;
};

void infoCarro(struct Tcarro umCarro) {
  printf("\nModelo do carro: %s\n", umCarro.modelo);
  printf("\nCor do carro: %s\n", umCarro.cor);
  printf("\nAno de lançamento: %d\n", umCarro.ano);
}


void flush_in(){
  int ch;
  while((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}

void mensagemDeAlerta();
void msgDeAlerta();
void msgFila();
void msgTanqueVazio();
void menuprincipal();
void menurelatorios();
void msgInicial();

int main(void) {

  float tamfila;
  float vcombustivel; // vl = valor do combustível. 
  int aux; 
  
  msgInicial();

  printf("\n\n\nPrimeiro, informe o tamanho da fila que o estabelecimento suportará: ");
  scanf("%f", &tamfila);
  aux = tamfila;
  
  while (tamfila != aux || tamfila <= 0) {
    mensagemDeAlerta();
    scanf("%f", &tamfila);
    aux = tamfila;
  }
  printf("\n\nAgora, informe o valor de combustível (use ponto(.) no caso de valores quebrados): ");
  scanf("%f", &vcombustivel);
  while (vcombustivel <= 0){
    mensagemDeAlerta();
    scanf("%f", &vcombustivel);  
  }
  system("clear");
  
  int op;
  char op_relatorio;

  int fila = 0, abastecidos = 0, restantes = 0;
  int tanque = 200, lvendidos = 0;
  float vtotal = 0, vpagar = 0;
  FILE *file;

  struct Tcarro *FilaEspera, *CarrosAtendidos;
  FilaEspera = (int*)malloc(tamfila * sizeof(struct Tcarro));
  CarrosAtendidos = (int*)malloc(1 * sizeof(struct Tcarro));
  
  while (op != 5){
    //menu principal
    menuprincipal();

    printf("\nEscolha a opção desejada: \n");
    scanf("%d",&op);
  
    system("clear");

    //verificação se a opcao selecionada é válida
    if(op == 1 || op == 2 || op == 3 || op == 4 || op == 5){
      int litros = 0;
      //opcoes do menu
      switch(op){
        case 1:
          if (fila < tamfila){
            flush_in();
            printf("\nInforme o modelo do carro: ");
            fgets(FilaEspera[fila].modelo,10,stdin);
            FilaEspera[fila].modelo[strcspn(FilaEspera[fila].modelo, "\n")] = 0;
            
            printf("\nInforme a cor do carro: ");
            fgets(FilaEspera[fila].cor,20,stdin);
            FilaEspera[fila].cor[strcspn(FilaEspera[fila].cor, "\n")] = 0;
              
            printf("\nInforme  o ano do carro: ");
            scanf("%d", &FilaEspera[fila].ano);

            fila = fila + 1;
              
            printf(C_GREEN"\nCarro adicionado na fila.\n"NONE);
            printf(C_BLUE"\nHá %d carro(s) na fila.\n"NONE,fila);

          }
          else {
            msgFila();
          }
        break;
        case 2:
          if (fila != 0) {
            if (tanque <= 0) {
              msgTanqueVazio();
              fila = fila - 1;
              printf(C_BLUE"\n\nCarros na fila: %d"NONE, fila);
              
              break;
            }   
              else {
                printf("Quantos litros deseja abastecer? \n");
                scanf("%d", &litros);
                while (litros > tanque) {
                  printf(C_RED"\nQuantidade não disponivel.\n"NONE);
                  printf(C_YELLOW"\nNo momento temos apenas %d litros no tanque, informe uma quatidade menor, por favor: "NONE, tanque);
                  scanf("%d", &litros);
                }
                printf(C_GREEN"\nValor a pagar: R$%.2f\n"NONE,litros * vcombustivel);
                printf(C_GREEN"\nCarro abastecido.\n"NONE);
                
                tanque = tanque - litros;
                lvendidos = lvendidos + litros;
                vtotal = vtotal + (litros * vcombustivel);
                CarrosAtendidos = (int*)realloc(CarrosAtendidos,(abastecidos + 1) * sizeof(struct Tcarro));
                CarrosAtendidos[abastecidos] = FilaEspera[0];
                abastecidos = abastecidos + 1;
                fila = fila - 1;

                for(int i = 0; i < tamfila; i++) {
                  FilaEspera[i] = FilaEspera[i+1];
                }
                
              }         
          }
          else {
            printf(C_YELLOW"A fila está vazia, primeiro adicione um carro."NONE);
          }
          break;
        
        case 3:
          restantes = fila;
          printf(C_BLUE"Carros na fila de espera: %d\n"NONE, restantes);

          for (int i = 0; restantes > i; i++) {
            printf(C_BLUE"\nCarro %d \n"NONE, i+1);
            infoCarro(FilaEspera[i]);
          } 
  
          break;
  
        case 4:
          while(op_relatorio != 'f'){
            //menu relatórios
            menurelatorios();
            
            printf("\nEscolha a opção desejada: ");
            scanf(" %c", &op_relatorio);  
  
            system("clear");
            
            //verificação se a op_relatório é válida
            if(op_relatorio == 'a' || op_relatorio == 'b' || op_relatorio == 'c' || op_relatorio == 'd' || op_relatorio == 'e' || op_relatorio == 'f'){
              //opções do menu relatório
              switch(op_relatorio){
                case 'a':
                  printf(C_BLUE"\nQuantidade de litros vendido: %d\n"NONE,lvendidos);
  
                  break;
  
                case 'b':
                  printf(C_BLUE"\nValor total arrecadado com as vendas: R$ %.2f\n"NONE,vtotal);
  
                  break;
  
                case 'c':       
                  for (int i = 0; abastecidos > i; i++) {
                    printf(C_BLUE"\nCarro %d \n"NONE, i+1);
                    infoCarro(CarrosAtendidos[i]);
                  } 
                  
                  printf(C_BLUE"\nQuantidade de carros atendidios: %d\n\n"NONE,abastecidos);
  
                  break;
  
                case 'd':
                  printf(C_BLUE"\nRestam %d litros no tanque.\n"NONE,tanque);
  
                  break;
  
                case 'e':
                  printf(C_BLUE"Arquivo sendo gerado...\n"NONE);
                  
                  file  = fopen ("text.txt","w+");
                  fprintf(file,"\n- Quantidade de litros vendidos: %d\n",lvendidos);
                  fprintf(file,"\n- Valor total arrecadado: R$ %.2f\n",vtotal);
                  fprintf(file,"\n- Quantidade de carros atendidios: %d\n",abastecidos);
                  fprintf(file,"\n- Restam %d litros no tanque.\n",tanque);
                  fclose(file);
  
                  break;
  
                case 'f':
  
                  break;
              }
            }
            else{
              msgDeAlerta();
            }
          }
          op_relatorio = 'g';
          break;
        case 5:
          
          break;
      }
    }
    else{
      msgDeAlerta();
    }
  }
  printf(C_GREEN"\nOBRIGADO POR USAR ESTE SERVIÇO!"NONE);
  
  return 0;
  
}



void mensagemDeAlerta() {
    printf(C_RED"\nValor inválido.\n"NONE);
    printf("\nPor favor, insira um valor maior que zero: ");
 }

void msgTanqueVazio() {
  printf(C_RED"Infelizmente não temos mais combustivel."NONE);
  printf(C_RED"\nAté logo, volte sempre."NONE);
  printf(C_YELLOW"\n\nCarro retirado da fila."NONE);
}

void msgFila() {
  printf(C_RED"A fila já está com a sua capacidade máxima."NONE);
  printf(C_YELLOW"\nPrimeiro abasteça um dos carros que já está na fila, depois adicione outro. "NONE);
}

void msgDeAlerta() {
  printf(C_RED"Opção inválida.\n"NONE);
}

void menuprincipal() {
    printf("\n\nMENU PRINCIPAL\n");
    printf("\n1 - Adicionar um carro na fila\n");
    printf("\n2 - Abastecer\n");
    printf("\n3 - Exibir carros na fila de espera\n");
    printf("\n4 - Relatórios\n");
    printf("\n5 - Encerrar\n"); 
}

void menurelatorios() {
  printf("\nRELATÓRIOS\n");
  printf("\na - Quantidade de litros vendida\n");  
  printf("\nb - Valor total arrecadado com as vendas\n");
  printf("\nc - Quantidade de carros atendidos\n");
  printf("\nd - Quantidade de combustível restante no tanque\n");
  printf("\ne - Gerar arquivo para impressão (com todas as informações de A, B, C e D)\n");
  printf("\nf - Voltar ao menu anterior\n");
}

void msgInicial(){
  printf(C_BLUE"\nAutor: Giovane Aguirre"NONE);
  printf(C_BLUE"\n\n\nEste programa foi feito com o intuito de melhorar o processo de gerenciamento de um posto de combustíveis."NONE);
}
