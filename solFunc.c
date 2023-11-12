#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hiddenGen(int HIDDEN[19][7]) {
    int count = 1, i, j;
    for (i=0; i<19; i++) {
        for (j=0; j<7; j++) {
            HIDDEN[i][j] = 0;
        }
    }
    for (i=0; i<6; i++) {
        for (j = 6; j>=count; j--) {
            HIDDEN[i][j] = 1;
        }
        count++;
    }
}

void deckResetShuffle(int Deck[53]){
    int x, count;
    for(x=0; x<53; x++){
        Deck[x] = x;
    }
    for (count = 0; count <= 2; count++){
        for(x=51; x>0; x--) {
            int r = rand() % x + 1;
            int temp = Deck[x];
            Deck[x] = Deck[r];
            Deck[r] = temp;
        }
    }
}