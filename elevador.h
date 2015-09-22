#define MAX_LOTACAO         3
#define BOTAO_NAO_APERTADO -1
#define BOTAO_APERTADO      1

enum sentido{
    PARADO,
    SUBINDO,
    DESCENDO
};

typedef enum sentido estado_t;

struct pessoa{
  int numero_andares;
  int *andar;
  int *tempo;
  int andar_atual;
};

typedef struct pessoa pessoas_t;

struct elevador{
  int lotacao;
  int andar_atual;
  int botao_apertado;
  int botoes[5];
  estado_t estado;
};

typedef struct elevador elevador_t;

pessoas_t* cria_pessoas(char *nomeArquivo, int *qnt);
pessoas_t* libera_pessoas(pessoas_t *p, int qnt);

void* elevador_run(void* arg);
void movimenta_elevador(elevador_t *elevador);

void* pessoas_run();
