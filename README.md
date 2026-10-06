# Playlist de Músicas (Lista Encadeada em C)

Atividade 1º GQ de Estruturas de Dados Lineares.

Aplicação que organiza as músicas de uma playlist usando uma **lista unicamente encadeada**. Os TADs `Musica` e `Lista` são implementados como **tipos opacos**: as structs são definidas apenas nos arquivos `.c`, e o `main.c` só manipula ponteiros por meio das funções declaradas nos `.h`.

## Estrutura do projeto

| Arquivo    | Descrição                                                                 |
|------------|---------------------------------------------------------------------------|
| `musica.h` | Interface do TAD Musica (tipo opaco e protótipos)                         |
| `musica.c` | Implementação do TAD Musica (struct e funções)                            |
| `lista.h`  | Interface do TAD Lista (tipo opaco e protótipos)                          |
| `lista.c`  | Implementação da lista unicamente encadeada (nó, struct e funções)        |
| `main.c`   | Programa principal: funções da playlist e simulação com 10 músicas        |

## Como compilar e executar

```bash
gcc main.c musica.c lista.c -o playlist -Wall -Wextra -pedantic
./playlist
```

No Windows, execute `playlist.exe`.

Para verificar vazamentos de memória (opcional):

```bash
valgrind --leak-check=full ./playlist
```

## TAD Musica

Cada música possui **título**, **artista** e **duração** (em segundos).

| Função                                  | Descrição                                              |
|-----------------------------------------|--------------------------------------------------------|
| `musica_criar(titulo, artista, duracao)`| Cria a música com cópia própria das strings            |
| `musica_get_titulo(m)`                  | Retorna o título (`NULL` se `m` for `NULL`)            |
| `musica_get_artista(m)`                 | Retorna o artista (`NULL` se `m` for `NULL`)           |
| `musica_get_duracao(m)`                 | Retorna a duração em segundos (`-1` se `m` for `NULL`) |
| `musica_imprimir(m)`                    | Imprime os dados da música                             |
| `musica_destruir(m)`                    | Libera título, artista e a própria música              |

## TAD Lista

Lista unicamente encadeada com ponteiros para o **início** e o **fim** e um contador de elementos. Posições começam em **0**.

| Operação                                | Função                                  |
|-----------------------------------------|-----------------------------------------|
| Criar a lista                           | `lista_criar`                           |
| Inserir no início                       | `lista_inserir_inicio`                  |
| Inserir no final                        | `lista_inserir_fim`                     |
| Inserir por posição                     | `lista_inserir_posicao`                 |
| Remover a primeira                      | `lista_remover_primeira`                |
| Remover a última                        | `lista_remover_ultima`                  |
| Remover por posição                     | `lista_remover_posicao`                 |
| Consultar a primeira                    | `lista_consultar_primeira`              |
| Consultar por posição                   | `lista_consultar_posicao`               |
| Consultar a quantidade de músicas       | `lista_quantidade`                      |
| Liberar/destruir a lista                | `lista_destruir`                        |

Convenções:

- Inserções e remoções retornam `1` em caso de sucesso e `0` em caso de falha (posição inválida, lista vazia, ponteiro `NULL` ou falha de alocação).
- Consultas retornam `NULL` quando a lista é vazia ou a posição é inválida.
- A lista é **dona das músicas** inseridas: as remoções e o `lista_destruir` liberam a música junto com o nó.

## Programa principal (`main.c`)

| Função                                                      | Descrição                                                        |
|-------------------------------------------------------------|------------------------------------------------------------------|
| `adiciona_musica`                                           | Adiciona uma música ao final da playlist                         |
| `adiciona_musica_posicao`                                   | Adiciona uma música em uma posição específica                    |
| `remove_musica`                                             | Remove a música de uma posição específica                        |
| `tempo_restante`                                            | Calcula e informa o tempo total restante até o fim da playlist   |
| `play`                                                      | "Toca" a próxima música, exibe seus dados e avança a posição     |
| `musicas_reproduzidas`                                      | Informa quantas músicas já foram "tocadas"                       |

A posição da próxima música a ser reproduzida é controlada pela variável `proxima`, declarada no `main` e passada por ponteiro para as funções que a alteram. Ela é ajustada automaticamente quando uma música é inserida ou removida **antes** da posição atual, para que a playlist não pule nem repita faixas.

## Simulação

O `main` cria 10 músicas diretamente no código (8 no final e 2 por posição) e simula o uso da playlist: toca algumas músicas, consulta o tempo restante, remove uma música já tocada e outra ainda não tocada, tenta uma remoção inválida e toca até o fim (incluindo uma chamada de `play` após o término).

Ao final, o programa imprime:

- a quantidade de músicas presentes na playlist;
- a posição da próxima música a ser reproduzida.

## Autor

Eduardo Veloso Chaves Malta
