#include <stdio.h>   // Funções de entrada e saída
#include <stdlib.h>  // Funções de alocação e números aleatórios
#include <time.h>    // Função time para srand()

// ====================== ESTRUTURAS ======================
typedef struct {
    char tipo;
    int id;
} peca;

#define MAX 5
#define PILHA_MAX 3

typedef struct {
    peca itens[MAX];
    int inicio;
    int fim;
    int total;
} fila;

typedef struct {
    peca itens[PILHA_MAX];
    int topo;
} Pilha;

// ====================== FILA ======================
void inicializarFila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(fila *f) {
    return f->total == MAX;
}

int filaVazia(fila *f) {
    return f->total == 0;
}

void inserir(fila *f, peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir [%c, %d]\n", p.tipo, p.id);
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(fila *f, peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível remover.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void exibirFila(fila *f) {
    if (filaVazia(f)) {
        printf("[fila vazia]\n");
        return;
    }

    printf("Fila (inicio -> fim): ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n");
}

// ====================== PILHA ======================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == PILHA_MAX - 1;
}

void push(Pilha *p, peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível inserir elementos.\n");
        return;
    }
    p->itens[++p->topo] = nova;
}

void pop(Pilha *p, peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não é possível remover.\n");
        return;
    }
    *removida = p->itens[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base) [%d/%d]:\n", p->topo + 1, PILHA_MAX);
    if (pilhaVazia(p)) {
        printf("[vazia]\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c, %d]\n", p->itens[i].tipo, p->itens[i].id);
    }
}

// ====================== OUTRAS FUNÇÕES ======================
void gerarPeca(peca *p, int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    p->tipo = tipos[rand() % 4];
    p->id = id;
}

void gerarENaFila(fila *f, int *contador) {
    peca nova;
    gerarPeca(&nova, (*contador)++);
    inserir(f, nova);
    printf("Nova peça [%c, %d] adicionada ao fim da fila.\n", nova.tipo, nova.id);
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n'); // limpa buffer
    getchar(); // espera ENTER
}

// ====================== MAIN ======================
int main() {
    fila filaPrincipal;
    Pilha pilhaReserva;

    inicializarFila(&filaPrincipal);
    inicializarPilha(&pilhaReserva);

    srand(time(NULL)); // semente aleatória

    int opcao;
    peca removida;
    int contador = 0;

    printf("\n=== JOGO TETRIS STACK ===\n");
    printf("\n--- Peças iniciais ---\n");

    for (int i = 0; i < MAX; i++) {
        peca nova;
        gerarPeca(&nova, contador++);
        inserir(&filaPrincipal, nova);
    }

    printf("Fila inicial gerada com %d peças:\n", filaPrincipal.total);
    exibirFila(&filaPrincipal);

    do {
        printf("\n==============================================\n");
        printf("                 MENU DE OPÇÕES               \n");
        printf("==============================================\n");
        printf("1 - Jogar peça (remover no início)\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("==============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: // Jogar peça
                if (filaVazia(&filaPrincipal)) {
                    printf("Fila vazia! Não é possível jogar mais peças.\n");
                    break;
                }

                remover(&filaPrincipal, &removida);
                printf("Peça [%c, %d] saiu do jogo!\n", removida.tipo, removida.id);
                gerarENaFila(&filaPrincipal, &contador);

                printf("\nEstado atual:\n");
                exibirFila(&filaPrincipal);
                pausar();
                break;

            case 2: // Enviar peça da fila para pilha
                if (filaVazia(&filaPrincipal)) {
                    printf("Fila vazia! Não é possível enviar peças.\n");
                    break;
                }
                if (pilhaCheia(&pilhaReserva)) {
                    printf("Pilha cheia! Não é possível enviar mais peças.\n");
                    break;
                }

                remover(&filaPrincipal, &removida);
                printf("Peça [%c, %d] removida da fila e enviada para a pilha de reserva.\n",
                       removida.tipo, removida.id);
                push(&pilhaReserva, removida);
                gerarENaFila(&filaPrincipal, &contador);

                printf("\nFila atual:\n");
                exibirFila(&filaPrincipal);
                printf("\nPilha de reserva:\n");
                mostrarPilha(&pilhaReserva);
                pausar();
                break;

            case 3: // Usar peça da pilha
                if (pilhaVazia(&pilhaReserva)) {
                    printf("Pilha vazia! Não é possível usar peças.\n");
                    break;
                }

                pop(&pilhaReserva, &removida);
                printf("Usou peça [%c, %d]\n", removida.tipo, removida.id);

                printf("\nFila atual:\n");
                exibirFila(&filaPrincipal);
                printf("\nPilha de reserva:\n");
                mostrarPilha(&pilhaReserva);
                pausar();
                break;

            case 4: // Trocar frente da fila com topo da pilha
                if (filaVazia(&filaPrincipal)) {
                    printf("Fila vazia! Não é possível trocar.\n");
                    break;
                }
                if (pilhaVazia(&pilhaReserva)) {
                    printf("Pilha vazia! Não é possível trocar.\n");
                    break;
                }

                {
                    peca temp = filaPrincipal.itens[filaPrincipal.inicio];
                    filaPrincipal.itens[filaPrincipal.inicio] = pilhaReserva.itens[pilhaReserva.topo];
                    pilhaReserva.itens[pilhaReserva.topo] = temp;
                }

                printf("Troca realizada entre frente da fila e topo da pilha.\n");

                printf("\nFila atual:\n");
                exibirFila(&filaPrincipal);
                printf("\nPilha de reserva:\n");
                mostrarPilha(&pilhaReserva);
                pausar();
                break;

            case 5: // Trocar 3 primeiros da fila com 3 da pilha
                if (filaPrincipal.total < 3 || pilhaReserva.topo < 2) {
                    printf("Não há peças suficientes para realizar a troca.\n");
                    break;
                }

                printf("\n--- Troca dos 3 primeiros da fila com as 3 peças da pilha ---\n");
                for (int i = 0; i < 3; i++) {
                    int idxFila = (filaPrincipal.inicio + i) % MAX;
                    int idxPilha = pilhaReserva.topo - i;

                    peca temp = filaPrincipal.itens[idxFila];
                    filaPrincipal.itens[idxFila] = pilhaReserva.itens[idxPilha];
                    pilhaReserva.itens[idxPilha] = temp;
                }

                printf("Troca realizada com sucesso!\n");
                printf("\nFila atual:\n");
                exibirFila(&filaPrincipal);
                printf("\nPilha de reserva:\n");
                mostrarPilha(&pilhaReserva);
                pausar();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                pausar();
        }

    } while (opcao != 0);

    return 0;
}