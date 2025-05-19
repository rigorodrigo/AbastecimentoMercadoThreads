// Componenentes: Pedro Rafael Domenighi e Rodrigo Rigo

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct areadeCarga{

    int caixas_atuais;
    int caixas_entregues;
    int maximo_caixas;
    pthread_mutex_t mutex;
    pthread_cond_t cond_caminhao;                   // variável de condição para os caminhões
    pthread_cond_t cond_funcionario;                       // variável de condição para os funcionários
};

void* f_funcionario (void *arg);
void* f_caminhao (void *arg);


int main (int argc, char *argv) {

    if (argc!= 7){
        fprintf(stderr,"Uso: %s <N>, <B>, <C>, <F>, <T> e <L> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]), f = atoi(argv[4]), t = atoi(argv[5]), l = atoi(argv[6]);

    if (n <= 1 || n >= 100){
        fprintf(stderr, "ERRO: <N> deve ser (1 < N < 100): ");
        exit(EXIT_FAILURE);
    }

    if (b <= 1 || b >= 10) {
        fprintf(stderr, "ERRO: <B> deve ser (1 < B < 10): ");
        exit(EXIT_FAILURE);
    }

    if (c <= 1 || c >= 5) {
        fprintf(stderr, "ERRO: <C> deve ser (1 < C < 5): ");
        exit(EXIT_FAILURE);
    }

    if (f <= 1 || f >= 3){
        fprintf(stderr, "ERRO: <F> deve ser (1 < F < 3): ");
        exit(EXIT_FAILURE);
    }

    if (t <= 1 || t >= 20) {
        fprintf(stderr, "ERRO: <T> deve ser (1 < T < 20): ");
        exit(EXIT_FAILURE);
    }

    if (l <= 1 || l >= 15) {
        fprintf(stderr, "ERRO: <L> deve ser (1 < L < 15): ");
        exit(EXIT_FAILURE);
    }

    struct areadeCarga aux;         // variável auxiliar do tipo da struct

    pthread_mutex_init(&aux.mutex,NULL);               // inicializando mutex
    pthread_cond_init(&aux.cond_caminhao,NULL);           // inicialziando condição
    pthread_cond_init(&aux.cond_funcionario,NULL);       // inicializando condição

    pthread_t funcionarios[f];
    pthread_t caminhao;

    for (int i = 0; i < f; i++){
        //criando as threads dos funcionários
        pthread_create(&funcionarios[i],NULL,f_funcionario,&aux);   
    }

    // criando a thread para o caminhão com a carga
    pthread_create(&caminhao,NULL,f_caminhao,&aux);

    for(int i = 0; i < f ;i++){
        // Aguarda todas as threads de funcionários terminarem
        pthread_join(funcionarios[i],NULL);
    }

     // Espera a thread do caminhão terminar
    pthread_join(caminhao,NULL);

    return 0;
}

void* f_funcionario (void *arg){

}

void* f_caminhao (void *arg){}