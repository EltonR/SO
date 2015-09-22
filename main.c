#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "elevador.h"


int main(int argc, char *argv[]){
  pthread_t elevador;
  pessoas_t *pessoas = NULL;
  int qnt_pessoas;
  int i;

  if(argc > 1){
    pessoas = cria_pessoas(argv[1], &qnt_pessoas);
    if(pessoas == NULL){
      printf("Falha na leitura do arquivo!\n");
    }
  }else{
    printf("Execucao: ./elevador nome_arquivo.txt\n");
    exit(1);
  }

  pthread_create(&elevador, NULL, elevador_run, NULL);
  pthread_join(elevador, NULL);

  libera_pessoas(pessoas, qnt_pessoas);
  return 0;
}
