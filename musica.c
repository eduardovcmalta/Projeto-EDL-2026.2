#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "musica.h"

struct musica {
    char *titulo;
    char *artista;
    int duracao;     // em segundos
};

Musica *musica_criar(const char *titulo, const char *artista, int duracao) {
    if (titulo == NULL || artista == NULL || duracao < 0) {
        return NULL;
    }

    Musica *m = malloc(sizeof(Musica));
    if (m == NULL) {
        return NULL;
    }

    m->titulo = malloc(strlen(titulo) + 1);
    if (m->titulo == NULL) {
        free(m);
        return NULL;
    }
    strcpy(m->titulo, titulo);

    m->artista = malloc(strlen(artista) + 1);
    if (m->artista == NULL) {
        free(m->titulo);
        free(m);
        return NULL;
    }
    strcpy(m->artista, artista);

    m->duracao = duracao;
    return m;
}
//Consultar
const char *musica_get_titulo(const Musica *m){
    if(m == NULL){
        return NULL;
    }
    return m->titulo;
}
const char *musica_get_artista(const Musica *m){
    if(m == NULL){
        return NULL;
    }
    return m->artista;
}
int musica_get_duracao(const Musica *m){
    if(m == NULL){
        return -1;
    }
    return m->duracao;
}
void musica_imprimir(const Musica* m){
   if (m == NULL){
    return;
   }
   printf("| Titulo: %s | Artista: %s | Duracao: %d segundos |\n",m->titulo, m->artista, m->duracao);
}
void musica_destruir(Musica* m){
    if(m == NULL){
        return;
    }
    free(m->titulo);
    free(m->artista);
    free(m);
}