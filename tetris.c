#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char tipo[2];
    int id; // id da peca
} Peca;

#define MAX 5

Peca fila[MAX];
int frente = 0;
int tras = 0;
int contador = 0;
int proximo_id = 1;

Peca gerarPeca() {
    Peca novo;
    const char *tipo[] = {"I", "O", "T", "L"};
    int num_tipo =  sizeof(tipo) / sizeof(tipo[0]);

    novo.id = proximo_id++;

    int indice_aleatorio = rand () % num_tipo;
    strcpy(novo.tipo, tipo[indice_aleatorio]);

    return novo;
}

void inserirPeca(Peca nova_peca) {
    if (contador == MAX) {
        printf("\n[ERRO] Fila cheia! Não foi possível inserir.\n");
        return;
    }

    fila[tras] = nova_peca;
    tras = (tras + 1) % MAX;
    contador++;

    printf("\n[INFO] PEÇA INSERIDA: tipo %s (ID %d) no final da fila.\n", nova_peca.tipo, nova_peca.id);
}

Peca jogarPeca(){
    Peca peca_jogada;

    if (contador == 0) {
        printf("\n[ERRO] Fila vazia! Nao ha pecas para jogar.\n");
        peca_jogada.id = -1;
        return peca_jogada;
    }

    peca_jogada = fila[frente];
    frente = (frente + 1) % MAX;
    contador--;

    printf("\n[INFO] PECA JOGADA: Tipo %s (ID %d) foi removida da frente.\n", peca_jogada.tipo, peca_jogada.id);

    return peca_jogada;
}

void VisualizarFila() {
    if (contador == 0) {
       printf("\n--- FILA DE PECAS (0/%d) ---\n", MAX_PECA);
        printf("A fila esta vazia.\n");
        printf("---------------------------\n");
        return; 
    }

    printf("\n--- FILA DE PECAS (%d/%d) ---\n", contador, MAX);
}
int main() {

    

    return 0;
}

