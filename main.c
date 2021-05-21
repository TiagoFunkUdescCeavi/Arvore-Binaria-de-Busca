#include <stdlib.h>
#include <stdio.h>

#include "arvore_publica.h"

// Acredito que a comparação seja mostrar qual é o maior dos números.
// Assim, no caso de int, é apenas fazer a diferença entre eles.
// Em strings e structs lógica tem que ser adaptada.
int comparaNumeros(void *p1, void *p2){
    int * a = p1;
    int * b = p2;
    return *a - *b;
}

int comparaIgualdade(void *p1, void *p2){
    int * a = p1;
    int * b = p2;
    if  (*a == *b)
        return 1;
    else
        return 0;
}

void processaInt(void *p){
    int * a = p;
    printf("%d ", *a );
}

int main( int argc, char * argv[] ){
    int a[12] = {42,51,19,37,42,86,71,10,75,22,31,41};
    pABB arv = criaABB( sizeof( int ) );

    for( int i = 0; i < 12; i++ ){
        insereABB( arv, &a[i], comparaNumeros );
    }

    percursoPreOrdem( arv, processaInt ); printf("\n");
    percursoEmOrdem( arv, processaInt ); printf("\n");
    percursoPosOrdem( arv, processaInt ); printf("\n");

    int resultadoBusca = buscaABB(arv, &a[5], comparaNumeros, comparaIgualdade );
    if(resultadoBusca)
        printf("Elemento encontrado!\n");
    else
        printf("Elemento não encontrado!\n");

    int naoExiste = 4324;
    resultadoBusca = buscaABB(arv, &naoExiste, comparaNumeros, comparaIgualdade );
    if(resultadoBusca)
        printf("Elemento encontrado!\n");
    else
        printf("Elemento não encontrado!\n");

    reiniciaABB(arv);
    reiniciaABB(arv);
    for( int i = 0; i < 12; i++ ){
        insereABB( arv, &a[i], comparaNumeros );
    }
    printf("INSERIU TUDO!\n");
    percursoEmOrdem( arv, processaInt ); printf("\n");

    printf("\n REMOVENDO O VALOR %d \n", a[0]);
    removeABB(arv, &a[0], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[5]);
    removeABB(arv, &a[5], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[10]);
    removeABB(arv, &a[10], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[11]);
    removeABB(arv, &a[11], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[3]);
    removeABB(arv, &a[3], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[7]);
    removeABB(arv, &a[7], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[2]);
    removeABB(arv, &a[2], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[9]);
    removeABB(arv, &a[9], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[1]);
    removeABB(arv, &a[1], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[6]);
    removeABB(arv, &a[6], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[0]);
    removeABB(arv, &a[0], comparaNumeros, comparaIgualdade );

    printf("\n REMOVENDO O VALOR %d \n", a[8]);
    removeABB(arv, &a[8], comparaNumeros, comparaIgualdade );

    percursoEmOrdem( arv, processaInt ); printf("\n");
    // printf("\n REMOVENDO O VALOR %d \n", a[5]);
    // removeABB(arv, &a[5], comparaNumeros, comparaIgualdade );
    // printf("\n REMOVENDO O VALOR %d \n", a[3]);
    // removeABB(arv, &a[3], comparaNumeros, comparaIgualdade );


    // int v68 = 68;
    // insereABB( arv, &v68, comparaNumeros );

    // int v70 = 70;
    // insereABB( arv, &v70, comparaNumeros );

    // int v65 = 65;
    // insereABB( arv, &v65, comparaNumeros );

    // printf("\n REMOVENDO O VALOR %d \n", a[6]);
    // removeABB(arv, &a[6], comparaNumeros, comparaIgualdade );
    // printf("\n REMOVENDO O VALOR %d \n", v68);
    // removeABB(arv, &v68, comparaNumeros, comparaIgualdade );
    // removeABB(arv, &a[1], comparaNumeros, comparaIgualdade );
    // percursoEmOrdem( arv, processaInt ); printf("\n");
    // percursoEmOrdem( arv, processaInt ); printf("\n");

    // printf("\n REMOVENDO O VALOR %d \n", a[0]);
    // removeABB(arv, &a[0], comparaNumeros, comparaIgualdade );

    // printf("\n REMOVENDO O VALOR %d \n", a[2]);
    // removeABB(arv, &a[2], comparaNumeros, comparaIgualdade );

    // printf("\n REMOVENDO O VALOR %d \n", a[7]);
    // removeABB(arv, &a[7], comparaNumeros, comparaIgualdade );

    // printf("\n REMOVENDO O VALOR %d \n", a[11]);
    // removeABB(arv, &a[11], comparaNumeros, comparaIgualdade );

    // percursoEmOrdem( arv, processaInt ); printf("\n");
    // percursoPosOrdem( arv, processaInt ); printf("\n");

    int resultadoDestruicao = destroiABB(arv);
    if(resultadoDestruicao)
        printf("\nArvore destruida!\n");
    else
        printf("Arvore não destruida!\n");

    return 0;
}