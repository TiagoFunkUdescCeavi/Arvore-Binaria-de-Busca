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

    return 0;
}