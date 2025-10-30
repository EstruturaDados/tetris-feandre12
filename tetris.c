#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

const char* tipos[] = {"I", "O", "T", "L"};
#define NUM_TIPOS 4

typedef struct {
    int id;
    char nome[3];
} Peca;

Peca gerarPeca(int id) {
    Peca p;
    p.id = id;
    strcpy(p.nome, tipos[rand() % NUM_TIPOS]);
    return p;
}

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

void exibirPilha(Peca pilha[], int topo) {
    printf("Pilha de Reserva (topo -> base):\n");
    if (topo == 0) {
        printf("(Pilha vazia)\n");
        return;
    }
    for (int i = topo-1; i >= 0; i--) {
        printf("[%d] %s  ", pilha[i].id, pilha[i].nome);
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
    Peca pilha[TAM_PILHA];
    int topo = 0;
    int opcao;
    do {
        exibirFila(fila, ini, fim, qtd);
        exibirPilha(pilha, topo);
        printf("\nMenu:\n1 - Jogar peça\n2 - Reservar peça\n3 - Usar peça reservada\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1: // Jogar peça
                if (qtd == 0) {
                    printf("Fila vazia!\n");
                } else {
                    printf("Peça jogada: [%d] %s\n", fila[ini].id, fila[ini].nome);
                    ini = (ini + 1) % TAM_FILA;
                    qtd--;
                    // Insere nova peça automaticamente
                    fila[fim] = gerarPeca(proxId++);
                    fim = (fim + 1) % TAM_FILA;
                    qtd++;
                }
                break;
            case 2: // Reservar peça
                if (qtd == 0) {
                    printf("Fila vazia!\n");
                } else if (topo == TAM_PILHA) {
                    printf("Pilha cheia!\n");
                } else {
                    pilha[topo++] = fila[ini];
                    printf("Peça reservada: [%d] %s\n", fila[ini].id, fila[ini].nome);
                    ini = (ini + 1) % TAM_FILA;
                    qtd--;
                    // Insere nova peça automaticamente
                    fila[fim] = gerarPeca(proxId++);
                    fim = (fim + 1) % TAM_FILA;
                    qtd++;
                }
                break;
            case 3: // Usar peça reservada
                if (topo == 0) {
                    printf("Pilha vazia!\n");
                } else {
                    printf("Peça usada da reserva: [%d] %s\n", pilha[topo-1].id, pilha[topo-1].nome);
                    topo--;
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