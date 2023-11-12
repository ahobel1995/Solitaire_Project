#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hiddenPrint(int HIDDEN[19][7]){
    int i, j;
    for(i=0; i<19; i++){
        for(j=0; j<7; j++){
            printf("%d ", HIDDEN[i][j]);
        }
        printf("\n");
    }
}

void deckPrint(int Deck[53]){
    int i;
    for(i=0; i<53; i++){
        printf("%d ", Deck[i]);
    }
    printf("\n");
}