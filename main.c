#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, moveYesNo, game = 0, inc = 0;
    int deck[53], hidden[21][7], play[21][7];
    int dropDeck[4];
    int playerCardChoice[2], playerMoveChoice[2], i, j;
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
        hiddenGen(hidden);
        playGen(play, deck);
        dropDeckReset(dropDeck);
        int drawDeck = deck[inc + 30];

        // GAME GOES HERE:
        while (game == 0) {
            frameGen(play, hidden, deck, dropDeck, drawDeck);
            printf("Would you like to move a card? (y=1, n=0) ");
            while (scanf("%d", &moveYesNo) != 1 || (moveYesNo != 1 && moveYesNo != 0)) {
                while (getchar() != '\n');
                printf("Error. Please input a 1 or 0: ");
            }
            while (getchar() != '\n');
            if (moveYesNo == 0) {
                break;
            } else {
                playerMoveDecision(play, hidden, drawDeck, dropDeck, deck, playerCardChoice, playerMoveChoice, inc);
                cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice, dropDeck);
            }
        }
        printf("Would you like to play again?  (y=1, n=0) ");
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