#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 50
typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    int topo;
    REGISTRO A[MAX];
} PILHA;

void inicializarPilha(PILHA* p);
int tamanhoPilha(PILHA* p);
void exibirPilha(PILHA* p);
int tamanhoEmBytesPilha(PILHA* p);
int buscaTopoDaPilha(PILHA* p);
void reinicializarPilha(PILHA* p);
bool inserirElementoPilha(PILHA* p, REGISTRO reg);
bool excluirElementoPilha(PILHA* p, REGISTRO* reg);
int retornarPrimeiroPilha(PILHA* p, TIPOCHAVE* ch);
REGISTRO* excluirElementoPilha2(PILHA* p);
int buscaSequencial(PILHA* p, TIPOCHAVE ch);

void inicializarPilha(PILHA* p) {
    p->topo = -1;
}

int tamanhoPilha(PILHA* p) {
    return p->topo + 1;
}

void exibirPilha(PILHA* p) {
    printf("Pilha: \" ");
    for (int i = p->topo; i >= 0; i--) {
        printf("%i ", p->A[i].chave);
    }
    printf("\"\n");
}

int tamanhoEmBytesPilha(PILHA* p) {
    return sizeof(PILHA);
}

int buscaTopoDaPilha(PILHA* p) {
    return p->topo;
}

void reinicializarPilha(PILHA* p) {
    p->topo = -1;
}

bool inserirElementoPilha(PILHA* p, REGISTRO reg) {
    if (p->topo + 1 >= MAX) return false;
    p->A[++p->topo] = reg;
    return true;
}

bool excluirElementoPilha(PILHA* p, REGISTRO* reg) {
    if (p->topo == -1) return false;
    *reg = p->A[p->topo--];
    return true;
}

int retornarPrimeiroPilha(PILHA* p, TIPOCHAVE* ch) {
    if (p->topo == -1) return -1;
    *ch = p->A[p->topo].chave;
    return p->topo;
}

REGISTRO* excluirElementoPilha2(PILHA* p) {
    if (p->topo == -1) return NULL;
    REGISTRO* res = (REGISTRO*)malloc(sizeof(REGISTRO));
    *res = p->A[p->topo--];
    return res;
}

int buscaSequencial(PILHA* p, TIPOCHAVE ch) {
    for (int i = p->topo; i >= 0; i--) {
        if (p->A[i].chave == ch) return i;
    }
    return -1;
}

void inserir(PILHA* p) {
    TIPOCHAVE ch;
    scanf("%i", &ch);
    REGISTRO reg;
    reg.chave = ch;
    if (inserirElementoPilha(p, reg))
        printf("Elemento %i inserido corretamente.\n", ch);
    else
        printf("Nao foi possivel inserir elemento %i.\n", ch);
}

void exibirPrimeiroPilha(PILHA* p) {
    TIPOCHAVE ch;
    int posicao = retornarPrimeiroPilha(p, &ch);
    if (posicao != -1)
        printf("Primeiro elemento %i encontrado na posicao %i.\n", ch, posicao);
    else
        printf("Nao foi possivel encontrar o primeiro elemento (pilha vazia).\n");
}

void excluir(PILHA* p) {
    REGISTRO reg;
    if (excluirElementoPilha(p, &reg))
        printf("Elemento %i excluido corretamente.\n", reg.chave);
    else
        printf("Nao foi possivel excluir elemento - pilha vazia.\n");
}

void exibir(PILHA* p) {
    exibirPilha(p);
}

void meuLog(PILHA* p) {
    printf("Numero de elementos na pilha: %i.\n", tamanhoPilha(p));
    printf("Tamanho da pilha (em bytes): %i.\n", tamanhoEmBytesPilha(p));
}

void help() {
    printf("Comandos validos: \n");
    printf("   i <chave1>: inserir elemento com chave=chave1 no topo da pilha\n");
    printf("   e : excluir o topo da pilha\n");
    printf("   p : imprimir pilha\n");
    printf("   d : destruir (zerar) pilha\n");
    printf("   l : exibir log de utilizacao da pilha\n");
    printf("   h : exibir esta mensagem de ajuda\n");
    printf("   0 : exibir a chave e o endereco do topo da pilha\n");
}

void destruir(PILHA* p) {
    reinicializarPilha(p);
    printf("Pilha zerada.\n");
}

int main() {
    PILHA pilha;
    inicializarPilha(&pilha);
    help();
    char comando = ' ';
    scanf("%c", &comando);
    while (comando != 'q') {
        switch (comando) {
            case 'i':
                inserir(&pilha);
                break;
            case 'e':
                excluir(&pilha);
                break;
            case 'p':
                exibir(&pilha);
                break;
            case 'd':
                destruir(&pilha);
                break;
            case 'l':
                meuLog(&pilha);
                break;
            case 'h':
                help();
                break;
            case '0':
                exibirPrimeiroPilha(&pilha);
                break;
            default:
                while (comando != '\n') scanf("%c", &comando);
        }
        scanf("%c", &comando);
    }

    return 0;
}