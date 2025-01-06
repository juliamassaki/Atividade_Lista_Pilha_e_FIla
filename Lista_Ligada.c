#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct tempRegistro {
    REGISTRO reg;
    struct tempRegistro* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA;

void inicializarLista(LISTA* l);
void exibirLista(LISTA* l);
int tamanho(LISTA* l);
int tamanhoEmBytes(LISTA* l);
PONT buscaSequencial(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant);
bool excluirElemLista(LISTA* l, TIPOCHAVE ch);
void reinicializarLista(LISTA* l);
bool inserirElemListaOrd(LISTA* l, REGISTRO reg);
PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch);
PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch);

void inicializarLista(LISTA* l) {
  l->inicio = NULL;
}

void exibirLista(LISTA* l) {
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

int tamanho(LISTA* l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

int tamanhoEmBytes(LISTA* l) {
  return (tamanho(l) * sizeof(ELEMENTO)) + sizeof(LISTA);
}

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL) {
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave < ch) {
    *ant = atual;
    atual = atual->prox;
  }
  if (atual != NULL && atual->reg.chave == ch) return atual;
  return NULL;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  PONT ant, i;
  i = buscaSeqExc(l, ch, &ant);
  if (i == NULL) return false;
  if (ant == NULL) l->inicio = i->prox;
  else ant->prox = i->prox;
  free(i);
  return true;
}

void reinicializarLista(LISTA* l) {
  PONT end = l->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(l, ch, &ant);
  if (i != NULL) return false;
  i = (PONT)malloc(sizeof(ELEMENTO));
  i->reg = reg;
  if (ant == NULL) {
    i->prox = l->inicio;
    l->inicio = i;
  } else {
    i->prox = ant->prox;
    ant->prox = i;
  }
  return true;
}

PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch) {
  if (l->inicio != NULL) *ch = l->inicio->reg.chave;
  return l->inicio;
}

PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch) {
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
}

int main() {
    LISTA lista;
    inicializarLista(&lista);

    REGISTRO reg1 = {10};
    REGISTRO reg2 = {20};
    REGISTRO reg3 = {15};

    printf("Inserindo elementos...\n");
    inserirElemListaOrd(&lista, reg1);
    inserirElemListaOrd(&lista, reg2);
    inserirElemListaOrd(&lista, reg3);

    printf("Lista após inserções:\n");
    exibirLista(&lista);

    printf("Tamanho da lista: %d\n", tamanho(&lista));
    printf("Tamanho em bytes: %d\n", tamanhoEmBytes(&lista));

    printf("Removendo elemento com chave 15...\n");
    excluirElemLista(&lista, 15);

    printf("Lista após remoção:\n");
    exibirLista(&lista);

    reinicializarLista(&lista);
    printf("Lista após reinicialização:\n");
    exibirLista(&lista);

    return 0;
}