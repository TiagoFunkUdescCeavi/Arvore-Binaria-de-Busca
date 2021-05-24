# Arvore Binária de Busca

- A arvore é dinámica em tamanho, pode inserir vários dados
- Contudo, é Homogênea então todos os dados inseridos devem ser do mesmo tamanho como `sizeof(int)`

### Dependencias
- [linux](https://www.linux.org/pages/download/)
- [GCC](https://gcc.gnu.org/install/index.html)
- [make](https://www.unixmen.com/install-ubuntu-make-on-ubuntu-15-04/)

### Métodos Publicos
- Os `ifndef` e `endif` são apenas para facilitar em casos que multiplos arquivos importam `arvore_publica.h`. Entretando, detro do TDA os includes são respeitados
```c
// arvore_publica.h
#ifndef ARVORE_PUBLICA_H
#define ARVORE_PUBLICA_H

typedef struct Arvore *pABB;

// criaABB cira a estrutura da arvore binária passando o tamanho da informação por parâmetro
pABB criaABB(int tamInfo);

// destroiABB destroi a arvore binária liberando os dados
int destroiABB(pABB pp);

// reiniciaABB reinicia os dados da arvore binária
int reiniciaABB(pABB p);

// insereABB insere novos dados na arvore cmp é a função de comparar >= 0 vai para direita, < 0 vai para esquerda
int insereABB(pABB p, void *novo, int (* cmp)(void *p1, void *p2));

// removeABB remove dado da arvore
// cmp é a função de comparar >= 0 vai para direita, < 0 vai para esquerda
// cmpI retorna 1 se é igual e retorna 0 se é diferente
int removeABB(pABB p, void *item, int (* cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2));

// buscaABB retorna o dado no *item
// cmp é a função de comparar >= 0 vai para direita, < 0 vai para esquerda
// cmpI retorna 1 se é igual e retorna 0 se é diferente
int buscaABB(pABB p, void *item, int (* cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2));

// percursoEmOrdem printa o percurso em ordem
// processa imprime o valor do dado
int percursoEmOrdem(pABB pa, void (* processa)(void *p));

// percursoPreOrdem printa o percurso em Pre ordem
// processa imprime o valor do dado
int percursoPreOrdem(pABB pa, void (* processa)(void *p));

// percursoPosOrdem printa o percurso em Pós ordem
// processa imprime o valor do dado
int percursoPosOrdem(pABB pa, void (* processa)(void *p));

#endif
```

### Estrutura da Arvore
```c
// arvore_privada.h
#ifndef ARVORE_PRIVADA_H
#define ARVORE_PRIVADA_H

#include "arvore_publica.h"

/**
 * Fiz com as duas structs para evitar que o aplicativo opere os nós.
 * Ele opera apenas a árvore.
 **/
typedef struct No{
    void * dado;
    struct No * pai;
    struct No * esquerdo;
    struct No * direito;
} No;

typedef struct Arvore{
    No * raiz;
    int tamInfo;
} Arvore;
....


```
### Como buildar
- Para buildar você deve criar ou modificar o `main.c` no root do projeto

- Execute o comando `make`
__Resultado Esperado__
- ![](https://i.imgur.com/49EbX1S.png)

- Deve gerar o arquivo executável `main`

### Como Executar
- Após realizar o build do executável com `make`
- Rode o arquivo com a seguinte linha de comando
```shell
./main
```

> Para limpar, realizar o build e executar o main use `make run`

### Como Limpar
- Limpa todos os `.out` e o `main`
- Execute o comando `make clean`

### Como Testar com simulação
- Acesse o [Binary Search Tree](https://www.cs.usfca.edu/~galles/visualization/BST.html)
- Insira os dados na ordem informada tanto no `main.c` quanto no `cs.usfca` e teste inserções e remoções variadas