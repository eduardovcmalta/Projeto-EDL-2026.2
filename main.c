#include <stdio.h>
#include "lista.h"
#include "musica.h"

void adiciona_musica(Lista *playlist, const char *titulo, const char *artista, int duracao) {
    Musica *m = musica_criar(titulo, artista, duracao);
    if (m == NULL) {
        printf("Erro ao criar a musica '%s'.\n", titulo);
        return;
    }
    if (!lista_inserir_fim(playlist, m)) {
        musica_destruir(m); 
        printf("Erro ao inserir '%s'.\n", titulo);
    }
}


void adiciona_musica_posicao(Lista *playlist, const char *titulo, const char *artista,
    int duracao, int pos, int *proxima){
    Musica *m = musica_criar(titulo, artista, duracao);
    if (m == NULL) {
        printf("Erro ao criar a musica '%s'.\n", titulo);
        return;
    }
    if (!lista_inserir_posicao(playlist, m, pos)) {
        musica_destruir(m);
        printf("Posicao %d invalida para inserir '%s'.\n", pos, titulo);
        return;
    }
    
    if (pos < *proxima) {
        (*proxima)++;
    }
}

void remove_musica(Lista *playlist, int pos, int *proxima) {
    if (!lista_remover_posicao(playlist, pos)) {
        printf("Posicao %d invalida para remocao.\n", pos);
        return;
    }
    if (pos < *proxima) {
        (*proxima)--;
    }
}

void tempo_restante(const Lista *playlist, int proxima) {
    int total = 0;
    int qtd = lista_quantidade(playlist);
    for (int i = proxima; i < qtd; i++) {
        total += musica_get_duracao(lista_consultar_posicao(playlist, i));
    }
    printf("Tempo restante: %d:%02d (%d segundos)\n", total / 60, total % 60, total);
}


void play(const Lista *playlist, int *proxima) {
    Musica *m = lista_consultar_posicao(playlist, *proxima);
    if (m == NULL) {
        printf("Fim da playlist: nao ha mais musicas para tocar.\n");
        return;
    }
    printf("Tocando agora: ");
    musica_imprimir(m);
    (*proxima)++;
}


void musicas_reproduzidas(const Lista *playlist, int proxima) {
    int qtd = lista_quantidade(playlist);
    int tocadas = (proxima > qtd) ? qtd : proxima;
    printf("Musicas reproduzidas: %d\n", tocadas);
}

int main(void) {
    Lista *playlist = lista_criar();
    if (playlist == NULL) {
        printf("Erro ao criar a playlist.\n");
        return 1;
    }
    int proxima = 0;

    adiciona_musica(playlist, "Bohemian Rhapsody", "Queen", 355);
    adiciona_musica(playlist, "Billie Jean", "Michael Jackson", 294);
    adiciona_musica(playlist, "Hotel California", "Eagles", 391);
    adiciona_musica(playlist, "Smells Like Teen Spirit", "Nirvana", 301);
    adiciona_musica(playlist, "Imagine", "John Lennon", 183);
    adiciona_musica(playlist, "Garota de Ipanema", "Tom Jobim", 330);
    adiciona_musica(playlist, "Evidencias", "Chitaozinho e Xororo", 270);
    adiciona_musica(playlist, "Come Together", "The Beatles", 259);
    adiciona_musica_posicao(playlist, "Wonderwall", "Oasis", 258, 2, &proxima);
    adiciona_musica_posicao(playlist, "Asa Branca", "Luiz Gonzaga", 180, 0, &proxima);

    printf("Playlist criada com %d musicas.\n\n", lista_quantidade(playlist));
    tempo_restante(playlist, proxima);

    printf("\n--- Tocando 4 musicas ---\n");
    for (int i = 0; i < 4; i++) {
        play(playlist, &proxima);
    }
    musicas_reproduzidas(playlist, proxima);
    tempo_restante(playlist, proxima);

    printf("\n--- Removendo a posicao 1 (ja tocada) e a posicao 6 (ainda nao tocada) ---\n");
    remove_musica(playlist, 1, &proxima);
    remove_musica(playlist, 6, &proxima);
    remove_musica(playlist, 99, &proxima); 
    printf("Musicas na playlist: %d | proxima posicao: %d\n", lista_quantidade(playlist), proxima);
    tempo_restante(playlist, proxima);

    printf("\n--- Tocando ate o fim (e uma a mais) ---\n");
    while (proxima < lista_quantidade(playlist)) {
        play(playlist, &proxima);
    }
    play(playlist, &proxima); 
    musicas_reproduzidas(playlist, proxima);
    tempo_restante(playlist, proxima);

    printf("\n=== Resumo final ===\n");
    printf("Quantidade de musicas na playlist: %d\n", lista_quantidade(playlist));
    printf("Posicao da proxima musica a ser reproduzida: %d\n", proxima);

    lista_destruir(playlist);
    playlist = NULL;
    return 0;
}