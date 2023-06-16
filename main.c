#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_DISCS 5

// Definição da estrutura de pilha
typedef struct {
    int top;
    int discs[NUM_DISCS];
} Stack;

// Função para inicializar a pilha
void initialize(Stack* stack) {
    stack->top = -1;
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Função para verificar se a pilha está cheia
int isFull(Stack* stack) {
    return stack->top == NUM_DISCS - 1;
}

// Função para empilhar um disco na pilha
void push(Stack* stack, int disc) {
    if (!isFull(stack)) {
        stack->discs[++stack->top] = disc;
    }
}

// Função para desempilhar um disco da pilha
int pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->discs[stack->top--];
    }
    return -1;
}

// Função para mover um disco de uma haste para outra
void moveDisc(Stack* source, Stack* destination) {
    int disc = pop(source);
    push(destination, disc);
}

// Função para imprimir a configuração atual das hastes
void printConfiguration(Stack* A, Stack* B, Stack* C) {
    printf("\nConfiguração atual:\n");
    printf("A: ");
    for (int i = A->top; i >= 0; i--) {
        printf("%d ", A->discs[i]);
    }
    printf("\nB: ");
    for (int i = B->top; i >= 0; i--) {
        printf("%d ", B->discs[i]);
    }
    printf("\nC: ");
    for (int i = C->top; i >= 0; i--) {
        printf("%d ", C->discs[i]);
    }
    printf("\n");
}

// Função para resolver o problema da Torre de Hanoi recursivamente
void solveHanoi(Stack* source, Stack* auxiliary, Stack* destination, int numDiscs) {
    if (numDiscs == 1) {
        moveDisc(source, destination);
        printConfiguration(source, auxiliary, destination);
        return;
    }

    solveHanoi(source, destination, auxiliary, numDiscs - 1);
    moveDisc(source, destination);
    printConfiguration(source, auxiliary, destination);
    solveHanoi(auxiliary, source, destination, numDiscs - 1);
}

void playGame(Stack* A, Stack* B, Stack* C);

// Função para exibir o menu principal e iniciar o jogo
void showMainMenu() {
    Stack A, B, C;
    initialize(&A);
    initialize(&B);
    initialize(&C);

    int option;

    do {
        printf("\nMenu Principal:\n");
        printf("1. Iniciar jogo\n");
        printf("2. Sair do programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                playGame(&A, &B, &C);
                break;
            case 2:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (option != 2);
}

// Função para exibir o menu de jogo e processar a opção escolhida pelo usuário
void showGameMenu(Stack* A, Stack* B, Stack* C, clock_t start) {
    int option;
    clock_t end;
    double timeTaken;

    do {
        printf("\nMenu de Jogo:\n");
        printf("1. Mover disco do pino A para o pino B\n");
        printf("2. Mover disco do pino A para o pino C\n");
        printf("3. Mover disco do pino B para o pino A\n");
        printf("4. Mover disco do pino B para o pino C\n");
        printf("5. Mover disco do pino C para o pino A\n");
        printf("6. Mover disco do pino C para o pino B\n");
        printf("7. Jogar automaticamente\n");
        printf("8. Reiniciar jogo\n");
        printf("9. Sair do jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (!isEmpty(A) && (isEmpty(B) || A->discs[A->top] < B->discs[B->top])) {
                    moveDisc(A, B);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 2:
                if (!isEmpty(A) && (isEmpty(C) || A->discs[A->top] < C->discs[C->top])) {
                    moveDisc(A, C);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 3:
                if (!isEmpty(B) && (isEmpty(A) || B->discs[B->top] < A->discs[A->top])) {
                    moveDisc(B, A);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 4:
                if (!isEmpty(B) && (isEmpty(C) || B->discs[B->top] < C->discs[C->top])) {
                    moveDisc(B, C);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 5:
                if (!isEmpty(C) && (isEmpty(A) || C->discs[C->top] < A->discs[A->top])) {
                    moveDisc(C, A);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 6:
                if (!isEmpty(C) && (isEmpty(B) || C->discs[C->top] < B->discs[B->top])) {
                    moveDisc(C, B);
                    printConfiguration(A, B, C);
                } else {
                    printf("Movimento inválido!\n");
                }
                break;
            case 7:
                printf("\nJogando automaticamente...\n");
                start = clock();
                solveHanoi(A, B, C, NUM_DISCS);
                end = clock();
                timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
                printf("\nJogo automático concluído!\n");
                printf("Tempo decorrido: %.2lf segundos\n", timeTaken);
                break;
            case 8:
                initialize(A);
                for (int i = NUM_DISCS; i > 0; i--) {
                    push(A, i);
                }
                printConfiguration(A, B, C);
                start = clock();
                break;
            case 9:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (option != 9);

    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo decorrido: %.2lf segundos\n", timeTaken);
}

// Função para jogar o jogo da Torre de Hanoi
void playGame(Stack* A, Stack* B, Stack* C) {
    clock_t start = clock();
    initialize(A);
    for (int i = NUM_DISCS; i > 0; i--) {
        push(A, i);
    }
    printConfiguration(A, B, C);
    showGameMenu(A, B, C, start);
}

int main() {
    showMainMenu();
    return 0;
}
