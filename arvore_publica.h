#ifndef ARVORE_PUBLICA_H
#define ARVORE_PUBLICA_H

typedef struct Arvore *pABB;

// criaABB cira a estrutura da arvore binária
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