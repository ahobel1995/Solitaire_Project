#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, moveYesNo, game = 0, inc = 0;
    int deck[53], hidden[31][7], play[31][7];
    int dropDeck[4];
    int playerCardChoice[2], playerMoveChoice[2], i;
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

        deckResetShuffle(deck);
        for (i = 0; i < 52; i++) {
            printf("%d ", deck[i]);
        }
        sleep(10);
        hiddenGen(hidden);
        playGen(play, deck);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while (game == 0) {
            frameGen(play, hidden, deck, dropDeck, inc);
            printf("Would you like to move a card? (y=1, n=0) ");
            while (scanf("%d", &moveYesNo) != 1 || (moveYesNo != 1 && moveYesNo != 0)) {
                while (getchar() != '\n');
                printf("Error. Please input a 1 or 0: ");
            }
            if (moveYesNo == 0) {
                break;
            } else {
                playerMoveDecision(play, playerCardChoice, playerMoveChoice);
                cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice);
            }
        }
        printf("Would you like to play again? (y=1,n=0) ");
    } while (yesNo == 1);
    system("clear");
    switch (rand() % 2) {
        case 0:
            gigaChad();
            break;
        case 1:
            mikeDisappointed();
            break;
    }
    return 0;
}