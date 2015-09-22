#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //Sleep

#include "elevador.h"

pessoas_t* cria_pessoas(char *nomeArquivo, int *qnt){
  pessoas_t *p = NULL;
  FILE *arq = NULL;
  int tam;
  int andar;
  int tempo;
  int i = 0;
  int j;

  arq = fopen(nomeArquivo, "r");
  if(arq != NULL){
    fscanf(arq, "%d", &tam);
    *qnt = tam;
    p = (pessoas_t*) malloc(tam * sizeof(pessoas_t));

    while(!feof(arq)){
      fscanf(arq, "%d", &tam);
      p[i].numero_andares = tam;
      p[i].andar = (int*) malloc(tam * sizeof(int));
      p[i].tempo = (int*) malloc(tam * sizeof(int));
      for(j = 0; j < tam; j++){
        fscanf(arq, "%d", &andar);
        fscanf(arq, "%d", &tempo);
        p[i].andar[j] = andar;
        p[i].tempo[j] = tempo;
      }
      i++;
    }
  }

  fclose(arq);
  return p;
}

pessoas_t* libera_pessoas(pessoas_t *p, int qnt){
    int i;

    for(i = 0; i < qnt; i++){
      free(p[i].andar);
      free(p[i].tempo);
    }
    free(p);

    return NULL;
}

void* elevador_run(void* arg){
  elevador_t elevador;

  //Inicia os parametros do elevador
  elevador.lotacao = 0;
  elevador.andar_atual = 0;
  elevador.estado = PARADO;
  elevador.botao_apertado = BOTAO_NAO_APERTADO;

  printf("Elevador criado!\n");
  printf("Movimentando Elevador\n");
  movimenta_elevador(&elevador);
  pthread_exit(NULL);
}

void movimenta_elevador(elevador_t *elevador){
  //Variáveis para teste -> Elevador linear (0 -> 4; 4 -> 0)
  //Nao implementa a parada do elevador
  int num_movimento = 12;
  int i = 0;

  //DEBUG
  printf("0 -> PARADO\n");
  printf("1 -> SUBINDO\n");
  printf("2 -> DESCENDO\n");
  //FIM_DEBUG

  while(i < num_movimento){
    printf("Estou no andar: %d e ", elevador->andar_atual);
    printf("Estou: %u \n", elevador->estado);
    if(elevador->estado == PARADO && elevador->andar_atual == 0){
      elevador->estado = SUBINDO; //Comeca a subir se estiver parado
    }
    if(elevador->estado == PARADO && elevador->andar_atual == 4){
      elevador->estado = DESCENDO; //Comeca a descer se estiver parado no ultimo andar
    }
    if(elevador->estado == DESCENDO && elevador->andar_atual == 0){
      elevador->estado = SUBINDO; //Comeca a subir de novo quando chega no primeiro andar
    }
    if(elevador->estado == SUBINDO && elevador->andar_atual == 4){
      elevador->estado = DESCENDO; //Comeca a descer
    }

    if(elevador->estado == SUBINDO){
      elevador->andar_atual += 1;
    }
    if(elevador->estado == DESCENDO){
      elevador->andar_atual -= 1;
    }

    i++;
    sleep(1);
  }
}
