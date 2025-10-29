#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Tipos possíveis de peças
const char* tipos[] = {"I", "O", "T", "L"};
#define NUM_TIPOS 4

// Estrutura da peça
typedef struct {
    int id;
    char nome[3];
} Peca;

// Função para gerar uma nova peça automaticamente
Peca gerarPeca(int id) {
    Peca p;
    p.id = id;
    strcpy(p.nome, tipos[rand() % NUM_TIPOS]);
    return p;
}

// Exibe o estado atual da fila
void exibirFila(Peca fila[], int ini, int fim, int qtd) {
    printf("\nFila de Peças (frente -> fim):\n");
    if (qtd == 0) {
        printf("(Fila vazia)\n");
        return;
    }
    int idx = ini;
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s  ", fila[idx].id, fila[idx].nome);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand((unsigned int)time(NULL));
    Peca fila[TAM_FILA];
    int ini = 0, fim = 0, qtd = 0, proxId = 1;
    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca(proxId++);
        fim = (fim + 1) % TAM_FILA;
        qtd++;
    }
    int opcao;
    do {
        exibirFila(fila, ini, fim, qtd);
        printf("\nMenu:\n1 - Jogar peça (dequeue)\n2 - Inserir nova peça (enqueue)\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1:
                if (qtd == 0) {
                    printf("Fila vazia!\n");
                } else {
                    printf("Peça jogada: [%d] %s\n", fila[ini].id, fila[ini].nome);
                    ini = (ini + 1) % TAM_FILA;
                    qtd--;
                }
                break;
            case 2:
                if (qtd == TAM_FILA) {
                    printf("Fila cheia!\n");
                } else {
                    fila[fim] = gerarPeca(proxId++);
                    fim = (fim + 1) % TAM_FILA;
                    qtd++;
                    printf("Nova peça inserida!\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}
