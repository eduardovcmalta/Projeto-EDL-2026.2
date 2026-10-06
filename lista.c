#include <stdlib.h>
#include "lista.h"

struct elem {
    Musica *musica;
    struct elem *prox;
};
typedef struct elem Elem;

struct lista {
    Elem *inicio;
    Elem *fim; 
    int qtd;
};

Lista *lista_criar() {
    Lista *l = malloc(sizeof(Lista));
    if (l == NULL) {
        return NULL;
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->qtd = 0;
    return l;
}

int lista_inserir_inicio(Lista *l, Musica *m) {
    if (l == NULL || m == NULL) {
        return 0;
    }
    Elem *e = malloc(sizeof(Elem));
    if (e == NULL) {
        return 0;
    }
    e->musica = m;
    e->prox = l->inicio;
    l->inicio = e;
    if (l->fim == NULL) { 
        l->fim = e;
    }
    l->qtd++;
    return 1;
}

int lista_inserir_fim(Lista *l, Musica *m) {
    if (l == NULL || m == NULL) {
        return 0;
    }
    Elem *e = malloc(sizeof(Elem));
    if (e == NULL) {
        return 0;
    }
    e->musica = m;
    e->prox = NULL;
    if (l->fim == NULL) { 
        l->inicio = e;
    } else {
        l->fim->prox = e;
    }
    l->fim = e;
    l->qtd++;
    return 1;
}

int lista_inserir_posicao(Lista *l, Musica *m, int pos) {
    if (l == NULL || m == NULL || pos < 0 || pos > l->qtd) {
        return 0;
    }
    
    if (pos == 0) {
        return lista_inserir_inicio(l, m);
    }
    if (pos == l->qtd) {
        return lista_inserir_fim(l, m);
    }

    Elem *e = malloc(sizeof(Elem));
    if (e == NULL) {
        return 0;
    }
    Elem *ant = l->inicio;
    for (int i = 0; i < pos - 1; i++) {
        ant = ant->prox;
    }
    e->musica = m;
    e->prox = ant->prox;
    ant->prox = e;
    l->qtd++;
    return 1;
}

int lista_remover_primeira(Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return 0;
    }
    Elem *rem = l->inicio;
    l->inicio = rem->prox;
    if (l->inicio == NULL) { 
        l->fim = NULL;
    }
    musica_destruir(rem->musica);
    free(rem);
    l->qtd--;
    return 1;
}

int lista_remover_ultima(Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return 0;
    }
    if (l->qtd == 1) {
        return lista_remover_primeira(l);
    }
    
    Elem *ant = l->inicio;
    while (ant->prox != l->fim) {
        ant = ant->prox;
    }
    musica_destruir(l->fim->musica);
    free(l->fim);
    ant->prox = NULL;
    l->fim = ant;
    l->qtd--;
    return 1;
}

int lista_remover_posicao(Lista *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->qtd) {
        return 0;
    }
    if (pos == 0) {
        return lista_remover_primeira(l);
    }
    if (pos == l->qtd - 1) {
        return lista_remover_ultima(l);
    }
    Elem *ant = l->inicio;
    for (int i = 0; i < pos - 1; i++) {
        ant = ant->prox;
    }
    Elem *rem = ant->prox;
    ant->prox = rem->prox; 
    musica_destruir(rem->musica);
    free(rem);
    l->qtd--;
    return 1;
}

Musica *lista_consultar_primeira(const Lista *l) {
    if (l == NULL || l->inicio == NULL) {
        return NULL;
    }
    return l->inicio->musica;
}

Musica *lista_consultar_posicao(const Lista *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->qtd) {
        return NULL;
    }
    Elem *aux = l->inicio;
    for (int i = 0; i < pos; i++) {
        aux = aux->prox;
    }
    return aux->musica;
}

int lista_quantidade(const Lista *l) {
    if (l == NULL) {
        return -1;
    }
    return l->qtd;
}

void lista_destruir(Lista *l) {
    if (l == NULL) {
        return;
    }
    Elem *aux = l->inicio;
    while (aux != NULL) {
        Elem *prox = aux->prox; 
        musica_destruir(aux->musica);
        free(aux);
        aux = prox;
    }
    free(l);
}