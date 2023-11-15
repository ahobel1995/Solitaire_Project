#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "debugFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, game=0, inc=0;
    int Deck[53], Hidden[19][7], Play[19][7];
    int dropDeck[4];
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
        // RESET FUNCTIONS:

        deckResetShuffle(Deck);
        // deckPrint(Deck);
        hiddenGen(Hidden);
        // hiddenPrint(Hidden);
        playGen(Play, Deck);
        // hiddenPrint(Play);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while(game == 0){
            frameGen(Play, Hidden, Deck, dropDeck, inc);

            // DEBUGGING:
            game = 1;
        }

        printf("Would you like to play again? (y=1,n=0) ");
    } while (yesNo == 1);
    system("clear");
    printf("Thanks for playing!\n");
    return 0;
}