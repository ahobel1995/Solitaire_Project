#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hiddenGen(int HIDDEN[19][7]) {
    int count=1, i, j;
    for (i=0; i<19; i++) {
        for (j=0; j<7; j++) {
            HIDDEN[i][j] = 0;
        }
    }
    for (i=0; i<6; i++) {
        for (j = 6; j>=count; j--) {
            HIDDEN[i][j] = 99;
        }
        count++;
    }
}

void playGen(int PLAY[19][7], int Deck[53]) {
    int count=0, i, j, a=1;
    for (i=0; i<19; i++) {
        for (j=0; j<7; j++) {
            PLAY[i][j] = 0;
        }
    }
    for (i=0; i<7; i++) {
        for (j=6; j>=count; j--) {
            PLAY[i][j] = Deck[a];
            a++;
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

void frameGen(int play[19][7], int hidden[19][7]){
    int i, j;
    // system("clear");
    for(i=0; i<19; i++){
        for(j=0; j<7; j++){
            if (hidden[i][j] == 99){
                printf("XX ");
            } else{
                printf("%2.d ", play[i][j]);
            }
        }
        printf("\n");
    }
}