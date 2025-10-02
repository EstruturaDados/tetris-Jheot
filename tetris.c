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
       printf("\n--- FILA DE PECAS (0/%d) ---\n", MAX);
        printf("A fila esta vazia.\n");
        printf("---------------------------\n");
        return; 
    }

    printf("\n--- FILA DE PECAS (%d/%d) ---\n", contador, MAX);

    // Itera a partir da 'frente' até o número de elementos no contador
    for (int i = 0; i < contador; i++) {
        int indice = (frente + i) % MAX;
        printf("[%d] | Tipo: %s | ID: %d | %s\n",
        fila[indice].tipo,
        fila[indice].id,
        i = 0 ? "<- PROXIMO A JOGAR" : "");
    }

    printf("----\n");
}

void inicializarFila() {
    for (int i = 0; i < MAX; i++) {
        Peca nova = gerarPeca();
        fila[i] = nova;
    }
    frente = 0;
    tras = 0; // Depois de inicializar 5, o 'tras' aponta para 0 (circular)
    contador = MAX;
    printf("Fila iniciazada com 4 peças aleatórias.\n");
    visualizarFila();
}
// -- Função principal --
int main() {
    int opcao;
    
    // Inicializa o gerador de números alatoórios
    srand((unsigned int)time(NULL));

    // Inicializa a arfila com 5 peças
    inicializarFila();

    do {
        printf("\n===== MENU DE CONTROLE DE PECAS =====\n");
        printf("1. Jogar Proxima Peca (Dequeue)\n");
        printf("2. Inserir Nova Peca (Enqueue automatico)\n");
        printf("3. Visualizar Fila Atual\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        // Garante que a entrada seja limpa se houver erro
        if (scanf("%d", &opcao) !=1) {
            while (getchar() != '\n'); // Limpa o buffer de entrada
            opcao = -1; // Define uma opção inválida
        }

        switch (opcao) {
            case 1:
                // 1. jogar (Remove a peça da frente)
                JogarPeca();
                VisualizarFila();
                break;
            case 2: {
                //2. Inserir (Gera e insere uma nova peça no final)
                Peca nova = gerarPeca();
                inserirPeca(nova);
                visualizarFila();
                break;
            }
            case 3:
                // 3. visualizar
                visualizarFila();
                break;
            case 0:
                printf("\nEncerrando o sistema de controle de pecas.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

