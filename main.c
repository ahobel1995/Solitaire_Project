#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, moveYesNo, game, draw;
    int deck[53], hidden[19][7], play[22][7], dropDeck[4];
    int playerCardChoice[2], playerMoveChoice[2], i, j, moveCount = 0;

    time_t t;
    srand(time(&t));
    draw = 29;
    printf("Welcome to Solitaire! Would you like to play? (y=1, n=0) ");
    do {
        game = 0; // Used to start a new game.
        while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (yesNo == 0) {
            break;
        }

        // RESET FUNCTIONS:
        draw = deckResetShuffle(deck, draw);
        hiddenGen(hidden);
        playGen(play, deck);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while (game == 0) {
            frameGen(play, hidden, deck, dropDeck, draw);
            printf("Would you like to move a card? (y=1, n=0) ");
            while (scanf("%d", &moveYesNo) != 1 || (moveYesNo != 1 && moveYesNo != 0)) {
                while (getchar() != '\n');
                printf("Error. Please input a 1 or 0: ");
            }
            while (getchar() != '\n');
            if (moveYesNo == 0) {
                break;
            } else {
                draw = playerMoveDecision(play, hidden, dropDeck, deck, playerCardChoice, playerMoveChoice, draw);
                // printf("Draw Value After Exiting Function: %d\n", draw);
                draw = cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice, dropDeck, deck, draw, moveCount);
            }
            if (dropDeck[0] == 13 && dropDeck[1] == 26 && dropDeck[2] == 39 && dropDeck[3] == 52) {
                printf("\nCongratulations! You win! \nYou made %d moves to win!", moveCount);
                game = 1;
            }
        }
        printf("Would you like to play again?  (y=1, n=0) ");
    } while (yesNo == 1);
    system("clear");
    switch (game) {
        case 0:
            mikeDisappointed();
            break;
        case 1:
            gigaChad();
            break;
    }
    return 0;
}