#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5  // Tamanho fixo da fila de peças

// Estrutura que representa uma peça do Tetris Stack
typedef struct {
    char nome;  // Tipo da peça ('I', 'O', 'T', 'L')
    int id;     // Identificador único da peça
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca elementos[MAX_FILA]; // Array que guarda as peças
    int frente;               // Índice da primeira peça
    int tras;                 // Índice da última peça
    int tamanho;              // Quantidade atual de peças na fila
} Fila;

// Função que inicializa a fila
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// Função que gera automaticamente uma peça nova
Peca gerarPeca(int id) {
    // Tipos possíveis de peças
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; // Sorteia um tipo de peça
    Peca nova;
    nova.nome = tipos[indice];
    nova.id = id;
    return nova;
}

// Função para inserir uma peça no final da fila (enqueue)
void inserirPeca(Fila *fila, Peca peca) {
    if (fila->tamanho == MAX_FILA) {
        printf("⚠️ Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % MAX_FILA; // Movimento circular
    fila->elementos[fila->tras] = peca;
    fila->tamanho++;
}

// Função para remover a peça da frente da fila (dequeue)
void jogarPeca(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("⚠️ Fila vazia! Não há peça para jogar.\n");
        return;
    }
    Peca removida = fila->elementos[fila->frente];
    printf("🎮 Jogando peça: [%c %d]\n", removida.nome, removida.id);
    fila->frente = (fila->frente + 1) % MAX_FILA; // Movimento circular
    fila->tamanho--;
}

// Função para exibir o estado atual da fila
void exibirFila(Fila *fila) {
    if (fila->tamanho == 0) {
        printf("Fila de peças está vazia.\n");
        return;
    }
    printf("\nFila de peças:\n");
    int i;
    int indice = fila->frente;
    for (i = 0; i < fila->tamanho; i++) {
        Peca atual = fila->elementos[indice];
        printf("[%c %d] ", atual.nome, atual.id);
        indice = (indice + 1) % MAX_FILA; // Movimento circular
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    Fila fila;
    inicializarFila(&fila);

    int contadorId = 0; // Controla o ID único das peças

    // Inicializa a fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        inserirPeca(&fila, gerarPeca(contadorId++));
    }

    int opcao;
    do {
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, gerarPeca(contadorId++));
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf(" Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}