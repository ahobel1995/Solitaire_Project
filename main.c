#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "debugFunc.h"

int main() {
    int yesNo, Deck[53], Hidden[19][7], Play[19][7];
    time_t t;
    srand(time(&t));
    printf("Welcome to Solitaire! Would you like to play? (y=1, n=0) ");
    do {
        while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (yesNo == 0) {
            break;
        }
        deckResetShuffle(Deck);
        // deckPrint(Deck);
        hiddenGen(Hidden);
        // hiddenPrint(Hidden);
        playGen(Play, Deck);
        // hiddenPrint(Play);
        frameGen(Play, Hidden);


        printf("Would you like to play again? (y=1,n=0) ");
    } while (yesNo == 1);
    return 0;
}