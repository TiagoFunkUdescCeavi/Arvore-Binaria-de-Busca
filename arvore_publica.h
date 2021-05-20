#ifndef ARVORE_PUBLICA_H
#define ARVORE_PUBLICA_H

typedef struct Arvore *pABB;

// Copiei no slide que o professor passou
// Fiquem a vontade para mudar
pABB criaABB(int tamInfo); // ok
int destroiABB(pABB pp);
int reiniciaABB(pABB p);
int insereABB(pABB p, void *novo, int (* cmp)(void *p1, void *p2)); // ok
int removeABB(pABB p, void *item, int (* cmp)(void *p1, void *p2));
int buscaABB(pABB p, void *item, int (* cmp)(void *p1, void *p2), int (* cmpI)(void *p1, void *p2)); //ok 
int percursoEmOrdem(pABB pa, void (* processa)(void *p)); // ok
int percursoPreOrdem(pABB pa, void (* processa)(void *p)); // ok
int percursoPosOrdem(pABB pa, void (* processa)(void *p)); // ok

#endif